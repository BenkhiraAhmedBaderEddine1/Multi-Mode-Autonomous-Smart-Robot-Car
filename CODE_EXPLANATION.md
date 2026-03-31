# Technical Code Explanation

This document breaks down the firmware architecture for the Multi-Mode Autonomous Smart Robot Car. The software is designed using a **modular approach**, ensuring high maintainability and ease of debugging.

## 1. System Constants & Hardware Mapping
The firmware begins by defining global constants for all hardware interfaces. 
* **Pin Mapping:** Using `const int` instead of hardcoded numbers allows for rapid hardware reconfiguration without searching through the logic.
* **Control Thresholds:** The `OBSTACLE_DISTANCE` is set to 20cm, providing a safety buffer for the 4WD chassis's inertia during emergency stops.

## 2. Initialization Protocol (`setup`)
The `setup()` function configures the hardware environment:
* **Baud Rate:** Set to **9600 bps** for stable asynchronous communication with the HC-05 Bluetooth module.
* **I/O States:** Explicitly defines `INPUT` (Sensors) and `OUTPUT` (Actuators) to prevent floating pin states.
* **Initial Safety State:** Calls `stopMotors()` immediately to ensure the robot does not move upon power-up until a valid signal is received.

## 3. The Control Engine (`loop`)
The `loop()` function implements a **Priority-Based Logic**:
1. **Interrupt-like Manual Check:** The system first queries the `Serial` buffer. If a Bluetooth command exists, manual control takes precedence.
2. **Autonomous Execution:** If no user input is detected, the robot defaults to its autonomous navigation logic, processing environmental data in real-time.

## 4. Navigation & Logic Algorithms
### A. Ultrasonic Distance Sensing
The `getDistance()` function utilizes a non-blocking trigger sequence:
* It emits a 10-microsecond high pulse.
* It calculates the travel time of the sound wave.
* **Physics Integration:** It applies the formula $D = \frac{T \times 0.034}{2}$ to convert time into distance, accounting for the speed of sound and the two-way travel path.

### B. Path-Tracking Logic (IR Sensors)
The `followLineLogic()` uses a simple but effective binary state machine:
* **Center Alignment:** Both sensors see the path (Forward).
* **Drift Correction:** If one sensor leaves the path, differential steering is applied to rotate the chassis back toward the center line.

### C. Obstacle Avoidance Routine
When an object is detected within the 20cm threshold, a multi-step sequence is triggered:
1. **Stop:** Immediate halt to prevent collision.
2. **Reverse:** Creates space for a turn.
3. **Pivot:** Rotates 90 degrees to find a clear path.

## 5. Movement Functions (H-Bridge Control)
Low-level functions manage the L298N Motor Driver. Each movement (Forward, Backward, Left, Right) is mapped to specific high/low combinations of the four input pins, controlling the internal MOSFET bridges of the driver.
