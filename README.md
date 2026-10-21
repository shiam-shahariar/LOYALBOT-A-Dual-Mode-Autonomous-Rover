# LOYALBOT - A Dual Mode Autonomous Rover

**An Arduino-Based Dual-Mode Rover for Object Following and Obstacle Avoidance**

## Overview

LOYALBOT is a low cost autonomous robotic rover developed as a capstone project for the **Microprocessor and Embedded Systems (EEE 4103)** course at American International University-Bangladesh (AIUB). Using an Arduino Uno, ultrasonic and infrared sensors, and DC motors, the rover can follow nearby objects and autonomously avoid obstacles. It features two operating modes controlled by a push button.

## Team Members

|         Name          | Student ID | Department |
|-----------------------|------------|------------|
| Md. Shahariar Shiam   | 23-50496-1 |    CSE     |
| Md. Shakib All Hassan | 23-51407-1 |    CSE     |
| Md. Ashiqur Rahman    | 23-54596-3 |    CSE     |
| Adiba Akram           | 23-53572-3 |    CSE     |

**Institution:** American International University-Bangladesh (AIUB)  
**Course:** Microprocessor and Embedded Systems
**Faculty:** Dr. Md. Rukonuzzaman  
**Semester:** Spring 2025–2026
**Section:** O
**Group:** 8

## Achievements

- **Object Following:** Detects nearby objects and adjusts movement according to their direction and distance.
- **Obstacle Avoidance:** Detects obstacles, scans left and right using a servo-mounted ultrasonic sensor, and selects a direction with more available space.
- **Dual-Mode Operation:** Switches between object-following and obstacle-avoidance modes using a push button.
- **Sensor Integration:** Integrates ultrasonic and infrared sensors for real-time detection.
- **Power Management:** Uses a buck converter to regulate the nominal 7.4V battery supply to 5V.
- **Line Following:** Partially implemented; stable tracking was not achieved.
- **Omnidirectional Movement:** Mecanum wheels were installed, but full omnidirectional movement was not achieved.

## Hardware Components

- Arduino Uno
- L298N Motor Driver
- HC-SR04 Ultrasonic Sensor
- Infrared (IR) Sensors
- SG90 Servo Motor
- 4 × TT Geared DC Motors
- 4 × Mecanum Wheels
- 2 × 18650 Rechargeable Batteries
- Buck Converter (7.4V to 5V)
- Battery Holder
- Push Button and Rocker Switch
- Wooden Chassis
- Jumper Wires, Nuts, and Bolts

**Estimated Project Cost:** BDT 9,056

## Technologies Used

- Arduino C/C++
- Arduino IDE
- `Servo.h`
- `NewPing.h`
- Embedded Systems and Robotics

## Future Improvements

- Stable omnidirectional movement with improved motor control
- Wireless control and monitoring
- Camera based object detection and intelligent navigation