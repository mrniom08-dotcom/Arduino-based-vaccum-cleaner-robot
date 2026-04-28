#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 150 // sets speed of DC motors
#define MAX_SPEED_OFFSET 20
#define DETECTION_THRESHOLD 30 // Reduce detection threshold for earlier obstacle detection

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
Servo myservo;   

boolean goesForward = false;
boolean systemEnabled = true; // Bluetooth-controlled system state
boolean isManualMode = false; // Mode state: false = automatic, true = manual
int distance = 100;
int speedSet = 0;

void setup() {
  myservo.attach(10);  
  myservo.write(90); // Center the servo initially
  delay(2000);
  distance = readPing();
  delay(100);

  Serial.begin(9600); // Initialize hardware serial for HC-05 communication
}

void loop() {
  // Check Bluetooth commands
  if (Serial.available()) {
    char command = Serial.read();
    Serial.print("Received Command: "); // Debugging
    Serial.println(command);

    if (command == '1') { // Enable system
      systemEnabled = true;
      Serial.println("System Enabled");
    } else if (command == '0') { // Disable system
      systemEnabled = false;
      Serial.println("System Disabled");
      moveStop();
    } else if (command == 'm') { // Switch to manual mode
      isManualMode = true;
      Serial.println("Manual Mode Enabled");
    } else if (command == 'a') { // Switch to automatic mode
      isManualMode = false;
      Serial.println("Automatic Mode Enabled");
    } else if (isManualMode && systemEnabled) { // Manual mode controls
      handleManualControl(command);
    }
  }

  // Automatic mode behavior
  if (systemEnabled && !isManualMode) {
    int distanceR = 0;
    int distanceL = 0;
    delay(40);
   
    distance = readPing(); // Read sensor before making a decision

    if (distance <= DETECTION_THRESHOLD) { // Obstacle detected
      moveStop();
      delay(100);
      moveBackward();
      delay(300);
      moveStop();
      delay(200);
      
      distanceR = lookRight();
      delay(200);
      distanceL = lookLeft();
      delay(200);

      if (distanceR > DETECTION_THRESHOLD || distanceL > DETECTION_THRESHOLD) {
        if (distanceR > distanceL) {
          turnSlightRight();
        } else {
          turnSlightLeft();
        }
      } else {
        // If neither side is free, move backward and reevaluate
        moveBackward();
        delay(500);
      }
    } else {
      moveForward();
    }
  }
}

void handleManualControl(char command) {
  switch (command) {
    case 'F': // Up Arrow - Forward
      moveForward();
      break;
    case 'B': // Down Arrow - Backward
      moveBackward();
      break;
    case 'L': // Left Arrow - Turn Left
      turnSlightLeft();
      break;
    case 'R': // Right Arrow - Turn Right
      turnSlightRight();
      break;
    case 'S': // Stop
      moveStop();
      break;
    default:
      Serial.println("Unknown Manual Command");
      break;
  }
}

int lookRight() {
  myservo.write(45); // Turn servo to the right
  delay(300); // Reduced stabilization time
  int distance = readPing();
  delay(100);
  myservo.write(90); // Reset servo to center
  return distance;
}

int lookLeft() {
  myservo.write(135); // Turn servo to the left
  delay(300); // Reduced stabilization time
  int distance = readPing();
  delay(100);
  myservo.write(90); // Reset servo to center
  return distance;
}

int readPing() { 
  delay(50); // Reduced delay for faster response
  int cm = sonar.ping_cm();
  return (cm == 0) ? 250 : cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  goesForward = false; // Ensure movement can restart
} 
  
void moveForward() {
  if (!goesForward) {
    goesForward = true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    
    int min_speed = 50;  // Increase this value if needed
    for (speedSet = min_speed; speedSet < MAX_SPEED; speedSet += 2) {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);      
  motor2.run(BACKWARD);
  
  int min_speed = 50;  // Increase this value if needed
  for (speedSet = min_speed; speedSet < MAX_SPEED; speedSet += 2) {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    delay(5);
  }
}  

void turnSlightRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);     
  delay(200); // Reduced turn duration
  moveForward();      
} 

void turnSlightLeft() {
  motor1.run(BACKWARD);     
  motor2.run(FORWARD);  
  delay(200); // Reduced turn duration
  moveForward();
}
