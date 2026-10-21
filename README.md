<div align="center">

<img src="assets/robot-car-hero.gif"
     width="100%"
     alt="Multi-Mode Autonomous Smart Robotic Car"/>

<br/>

<img src="https://img.shields.io/badge/ARDUINO-UNO-FF5B69?style=for-the-badge&logo=arduino&logoColor=white&labelColor=160D20"/>
<img src="https://img.shields.io/badge/DRIVE-4WD-FFAD48?style=for-the-badge&labelColor=160D20"/>
<img src="https://img.shields.io/badge/CONTROL-3%20MODES-B777FF?style=for-the-badge&labelColor=160D20"/>
<img src="https://img.shields.io/badge/LANGUAGE-EMBEDDED%20C%2B%2B-F4EFFF?style=for-the-badge&logo=cplusplus&logoColor=white&labelColor=160D20"/>

<br/><br/>

<img src="https://readme-typing-svg.demolab.com?font=Orbitron&weight=700&size=18&duration=2400&pause=700&color=FFAD48&center=true&vCenter=true&width=900&lines=AUTONOMY+IN+MOTION.;SENSE+THE+WORLD.+MAKE+DECISIONS.+MOVE.;BLUETOOTH+%7C+OBSTACLE+AVOIDANCE+%7C+LINE+FOLLOWING."
     alt="Animated robotics tagline"/>

<h1>MULTI-MODE AUTONOMOUS SMART ROBOTIC CAR</h1>

<p>
<strong>
A FOUR-WHEEL-DRIVE ROBOTIC PLATFORM
</strong>
</p>

<p>
Wireless Teleoperation · Autonomous Navigation · Embedded Intelligence
</p>

<p>
<a href="#project-overview">PROJECT OVERVIEW</a>
&nbsp; ◆ &nbsp;
<a href="#three-operating-modes">THREE MODES</a>
&nbsp; ◆ &nbsp;
<a href="#hardware-architecture">HARDWARE</a>
&nbsp; ◆ &nbsp;
<a href="#getting-started">GET STARTED</a>
</p>

<img src="https://capsule-render.vercel.app/api?type=rect&height=5&color=0:FF5B69,45:FFAD48,100:B777FF"
     width="100%" alt="Design divider"/>


<div align="center">
  <img src="robot-car-hero.gif"
       width="100%"
       alt="Animated autonomous robotic car">
</div>






<div align="center">

## 🔴🟠 ABSTRACT 🟠🔴

**PROJECT OVERVIEW · SYSTEM DESIGN · ENGINEERING PRINCIPLES**

</div>

This project presents the design, development, programming, and evaluation framework of a Multi-Mode Autonomous Smart Robot Car, a four-wheel-drive (4WD) robotic platform developed around the Arduino Uno microcontroller. The system combines embedded electronics, real-time sensing, wireless communication, motor control, and autonomous decision-making to demonstrate how an inexpensive robotic vehicle can navigate its environment and respond to external commands.

The proposed platform integrates an Arduino Uno based on the ATmega328P microcontroller, an L298N dual H-bridge motor driver, four geared DC motors, an HC-SR04 ultrasonic distance sensor, infrared (IR) line-tracking sensors, and an HC-05 Bluetooth communication module. An optional SG90 servo motor is added to rotate the ultrasonic sensor, allowing the robot to inspect the left and right sides before selecting a direction.

The robot is designed to operate in three primary modes. In manual mode, the user controls movement wirelessly through a Bluetooth-enabled application. In autonomous obstacle-avoidance mode, the robot measures the distance to objects, evaluates available directions, and adjusts its movement accordingly. In line-following mode, the vehicle uses infrared sensors to detect a marked path and continuously correct its direction.

The software is organized around a modular, event-driven control architecture. Pulse-width modulation (PWM) is used to regulate motor speed, while directional motor commands implement differential steering. A state-machine approach separates obstacle scanning, turning, reversing, manual control, and line tracking, reducing unnecessary blocking operations and making the firmware easier to understand and extend.

Beyond describing the hardware and source code, this report explains the mathematical principles behind distance measurement, PWM, and differential-drive motion. It also presents the circuit connections, control algorithms, construction procedure, calibration methodology, testing framework, advantages, limitations, safety considerations, and potential future improvements.

The resulting platform serves as an educational and experimental foundation for autonomous robotics. Although it does not provide the mapping, localization, or safety guarantees of an industrial autonomous vehicle, it demonstrates the essential interaction between sensing, computation, communication, and actuation in a practical embedded system.

### 🧠 Keywords

`Autonomous Robotics` · `Arduino Uno` · `ATmega328P` · `Embedded C++` · `Obstacle Avoidance` · `Line Following` · `Bluetooth` · `Ultrasonic Sensing` · `Infrared Sensors` · `PWM` · `Differential Drive` · `Robotic Vehicle`

---

<div align="center">

## 🔴🟠 01 · INTRODUCTION 🟠🔴

**FOUNDATIONS · ENGINEERING CHALLENGES · PROJECT OBJECTIVES**

</div>

### 1.1 Background

Robotics combines mechanical design, electronic circuits, sensing technologies, control theory, and computer programming to create machines that can interact with their surroundings. Autonomous mobile robots are especially interesting because they must continuously interpret environmental information and convert it into suitable movement decisions.

A conventional remote-controlled car relies entirely on commands sent by a human operator. An autonomous robot, on the other hand, must obtain information from sensors, process that information using a controller, and determine an appropriate action without requiring a new command for every movement.

This project bridges these two approaches by combining manual remote control with two autonomous navigation techniques. The operator can intervene when required, while the robot can also follow a line or react to obstacles automatically.

The Arduino Uno is suitable for this educational application because it offers digital input/output pins, PWM outputs, analog inputs, and a widely supported programming environment. Its ATmega328P microcontroller runs at 16 MHz and provides 32 KB of flash memory, making it adequate for a compact control program of this type.

**Technical reference:** [Official Arduino Documentation](https://docs.arduino.cc/)

### 1.2 Problem Statement

Designing a mobile robot that can move reliably through an environment presents several practical challenges:

- **Obstacle detection:** The robot must detect objects in front of it before a collision occurs.
- **Path tracking:** The robot must recognize a line on the floor and correct its direction when it deviates from the path.
- **Wireless control:** The operator must be able to issue movement and mode-selection commands without a physical cable.
- **Motor coordination:** Four wheels must work together to produce forward movement, reverse movement, and turning.
- **Real-time response:** Sensor acquisition, communication, and motor control must coexist without unnecessary delays.
- **Power management:** The battery must supply the motors while providing stable power to the controller and sensors.

The central problem is therefore to design an affordable embedded system capable of switching between multiple operating modes while maintaining clear separation between sensing, decision-making, and actuation.

### 1.3 Aim of the Project

The main aim is to design and implement a four-wheel-drive robotic vehicle that supports manual Bluetooth control, autonomous obstacle avoidance, and infrared line following through a unified Arduino-based control system.

### 1.4 Specific Objectives

The project objectives are to:

1. Construct a stable 4WD robotic platform.
2. Interface four DC geared motors with an Arduino Uno through an L298N motor driver.
3. Measure obstacle distance using an HC-SR04 ultrasonic sensor.
4. Implement infrared-based line detection and path correction.
5. Establish serial communication between the Arduino and an HC-05 Bluetooth module.
6. Develop a mode-selection mechanism that allows the operator to switch between manual and autonomous functions.
7. Apply PWM to vary motor speed and improve directional control.
8. Organize the firmware into reusable functions and explicit operating states.
9. Test each subsystem separately before testing the complete robot.
10. identify the strengths, weaknesses, safety requirements, and possible future improvements of the design.

### 1.5 Project Scope

The proposed design addresses small-scale educational and laboratory robotics. It is intended for controlled indoor environments, particularly flat surfaces with sufficiently visible lines and obstacles that can be detected by an ultrasonic sensor.

The project does not claim to provide industrial-grade collision prevention, map-based navigation, artificial intelligence, or guaranteed operation on arbitrary terrain. Those capabilities require additional hardware, more advanced algorithms, or both.

### 1.6 Main Contribution

The main contribution is not simply the assembly of a robot car. It is the integration of three control modes into one embedded platform, together with a modular software design that makes the system easier to test, understand, and upgrade.

The design also demonstrates an important engineering principle: a robot should not be treated as a collection of independent components, but as a coordinated system in which sensors, algorithms, actuators, and power electronics must work together.

---

<div align="center">

## 🔴🟠 02 · SYSTEM ARCHITECTURE 🟠🔴

**HARDWARE INTEGRATION · CONTROL STRUCTURE · SUBSYSTEM INTERACTION**

</div>

### 2.1 General System Description

The robot consists of five interacting subsystems:

**01 — Processing Subsystem**

The Arduino Uno reads sensor values, interprets Bluetooth commands, and executes the selected control algorithm.

**02 — Sensing Subsystem**

The ultrasonic sensor detects obstacles, while the IR sensors detect a line on the floor.

**03 — Communication Subsystem**

The HC-05 module transfers commands between the robot and a Bluetooth-enabled device.

**04 — Actuation Subsystem**

The L298N drives the left and right motor groups, while an optional SG90 servo positions the ultrasonic sensor.

**05 — Power Subsystem**

A battery pack supplies the motors, and a regulated supply powers the controller, sensors, communication module, and servo.

The Arduino Uno supports this role through its digital I/O, analog input, and PWM capabilities.

---

<div align="center">

### ⚙️ SYSTEM DESIGN PHILOSOPHY

*Sense → Process → Decide → Act → Evaluate*

🔴━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━🟠

**END OF PART I · ABSTRACT & SYSTEM ARCHITECTURE**

</div>
