# Multi-Mode-Autonomous-Smart-Robot-Car
An Arduino-based 4WD robotic platform integrating real-time sensor fusion for autonomous navigation (Obstacle Avoidance &amp; Line Following) and Bluetooth-enabled teleoperation


**Author:** Ahmed Bader Eddine Benkhira  
**Institution:** University of Boumerdes (IGEE)  
**Date:** March 17, 2024  

---


# Multi-Mode Autonomous Smart Robot Car

### 🛠 System Overview

```text
          _||_  <-- Ultrasonic Sensor
         |____|
      __ /____\ __
     |[]|      |[]|
     |__|======|__|
         | ARD |
   |=====| UIN |=====|
   |  W  |  O  |  W  |
   |  H  |_____|  H  |
   |  E  |     |  E  |
   |  E  |_____|  E  |
   |  L  |     |  L  |
   |=====|=====|=====|
     |[]|      |[]|
     |__|======|__|
```





## Project Overview
This project presents the design and implementation of a 4WD autonomous robotic platform based on the ATmega328P microcontroller (Arduino Uno). The system is engineered to switch between three distinct operational modes, demonstrating proficiency in embedded C++ programming, sensor fusion, and hardware-software integration.

### Key Capabilities
* **Manual Teleoperation:** Wireless control via HC-05 Bluetooth module and custom command mapping.
* **Autonomous Obstacle Avoidance:** Real-time spatial navigation using HC-SR04 ultrasonic sensors with non-blocking logic.
* **Precision Path Tracking:** Line-following functionality utilizing infrared (IR) sensor arrays.

## Hardware Architecture
The system utilizes a modular hardware stack designed for stability and efficiency:
* **Microcontroller:** Arduino Uno
* **Motor Driver:** L298N Dual H-Bridge
* **Actuators:** 4x DC Geared Motors (4WD Chassis)
* **Sensors:** HC-SR04 Ultrasonic, IR Sensors (Line Tracking)
* **Communication:** HC-05 Bluetooth Module
* **Power:** Dual 18650 Lithium-Ion Battery Configuration

##  Software Design
The firmware is developed with a focus on modularity. Key engineering concepts implemented include:
* **PWM Speed Control:** Pulse Width Modulation used to achieve differential steering and variable velocity.
* **State Logic:** A robust conditional architecture to manage mode-switching between autonomous and manual tasks.
* **Sensor Filtering:** Logic-based thresholding to minimize sensor noise during high-speed navigation.

##  Repository Structure
* `/src`: Contains the primary `.ino` source code.
* `/hardware`: High-resolution circuit diagrams and pin connection tables.
* `/docs`: The full technical lab report in PDF format.

##  How to Use
1.  Clone the repository: `git clone https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git`
2.  Open `/src/SmartRobotMain.ino` in the Arduino IDE.
3.  Ensure required libraries (if any) are installed.
4.  Upload to the Arduino Uno and select the desired mode via the Bluetooth application or hardware toggle.

##  Future Enhancements
* Implementation of **PID Control** for smoother line-following transitions.
* Integration of **ROS (Robot Operating System)** for advanced mapping.
* Computer Vision integration via Raspberry Pi for object recognition.

##  License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
