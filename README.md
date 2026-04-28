# 🤖 Arduino-Based Smart Vacuum Cleaner Robot

## 📌 Project Overview

This project presents a **low-cost, Arduino-based smart vacuum cleaner robot** capable of autonomous movement and obstacle avoidance. The robot is designed to clean floor surfaces with minimal human intervention using simple and affordable components.

It uses an ultrasonic sensor to detect obstacles and intelligently navigates around them while operating a vacuum mechanism.

---

## 🎯 Features

* Autonomous obstacle avoidance
* Ultrasonic distance sensing (HC-SR04)
* Servo-based directional scanning
* Motor control using Arduino Motor Shield
* Manual control support (optional via Bluetooth)
* Low-cost and easy to build

---

## ⚙️ Components Used

* Arduino Uno
* Arduino Motor Shield (L293D)
* Ultrasonic Sensor (HC-SR04)
* Servo Motor (MG90S)
* DC Motors + Wheels
* Gear Motors
* Battery (3.7V × 2 or equivalent)
* Plastic Fan (vacuum system)
* IR Sensor (optional)
* Switch, wires, chassis materials

---

## 🔌 Circuit Connections

### Ultrasonic Sensor

* TRIG → A0
* ECHO → A1

### Servo Motor

* Signal → Pin 10
* VCC → 5V
* GND → GND

### Motor Shield

* Mounted directly on Arduino Uno
* Controls DC motors for movement

---

## 🧠 Working Principle

1. The robot continuously moves forward.
2. The ultrasonic sensor measures distance to obstacles.
3. If an obstacle is detected:

   * Robot stops
   * Moves backward slightly
   * Servo rotates to scan left and right
4. The robot chooses the direction with more space.
5. Movement continues until the area is cleaned.





## ▶️ How to Run

1. Install Arduino IDE
2. Install required libraries:

   * **NewPing**
   * **Adafruit Motor Shield Library**
3. Connect components as per circuit diagram
4. Upload the `.ino` file to Arduino Uno
5. Power the robot using batteries
6. Turn on the switch → Robot starts cleaning automatically

---

## 📚 Libraries Required

* NewPing → https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
* Adafruit Motor Shield Library

---

## 💰 Cost Analysis

The total cost of the project is approximately **3740 BDT**, making it a budget-friendly alternative to commercial robotic vacuum cleaners.


---

## 📜 License

This project is for educational purposes.
