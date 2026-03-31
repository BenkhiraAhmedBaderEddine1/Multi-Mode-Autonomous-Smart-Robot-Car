/**
 * @file SmartRobotMain.ino
 * @author Ahmed Bader Eddine Benkhira
 * @institution Institute of Electrical and Electronics Engineering (IGEE)
 * @date March 17, 2024
 * @brief Multi-Mode Control System for a 4WD Autonomous Robotic Platform.
 */

// --- PIN CONFIGURATION ---
// L298N Motor Driver Pins
const int IN1 = 5; 
const int IN2 = 6;
const int IN3 = 10;
const int IN4 = 11;

// HC-SR04 Ultrasonic Sensor Pins
const int TRIG_PIN = A4;
const int ECHO_PIN = A5;

// IR Line Tracking Sensor Pins
const int IR_LEFT = 2;
const int IR_RIGHT = 3;

// --- OPERATIONAL CONSTANTS ---
const int OBSTACLE_DISTANCE = 20; // Detection threshold in cm
char bluetoothCommand;

void setup() {
  // Initialize Motor Control Pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialize Sensor Interface
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  // Establish Serial Communication (Baud rate 9600 for HC-05)
  Serial.begin(9600);
  
  // Safety: Ensure motors are off on startup
  stopMotors();
}

void loop() {
  /**
   * PRIMARY CONTROL LOGIC:
   * 1. Check for Manual override via Bluetooth.
   * 2. If no command, proceed with autonomous navigation.
   */
  if (Serial.available() > 0) {
    bluetoothCommand = Serial.read();
    handleManualControl(bluetoothCommand);
  } else {
    runAutonomousMode();
  }
}

// --- NAVIGATION MODULES ---

/**
 * @brief Reads distance from Ultrasonic sensor using pulse-width calculation.
 * @return Distance in centimeters.
 */
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

/**
 * @brief Logic for autonomous obstacle avoidance and line following.
 */
void runAutonomousMode() {
  long currentDistance = getDistance();

  if (currentDistance > 0 && currentDistance < OBSTACLE_DISTANCE) {
    performEvasiveManeuver();
  } else {
    followLineLogic();
  }
}

void followLineLogic() {
  int leftSense = digitalRead(IR_LEFT);
  int rightSense = digitalRead(IR_RIGHT);

  if (leftSense == LOW && rightSense == LOW) {
    moveForward();
  } else if (leftSense == HIGH && rightSense == LOW) {
    turnLeft();
  } else if (leftSense == LOW && rightSense == HIGH) {
    turnRight();
  } else {
    stopMotors();
  }
}

void performEvasiveManeuver() {
  stopMotors();
  delay(200);
  moveBackward();
  delay(400);
  turnRight();
  delay(600);
  stopMotors();
}

// --- LOW-LEVEL ACTUATOR CONTROL ---

void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void handleManualControl(char cmd) {
  switch (cmd) {
    case 'F': moveForward(); break;
    case 'B': moveBackward(); break;
    case 'L': turnLeft(); break;
    case 'R': turnRight(); break;
    case 'S': stopMotors(); break;
  }
}
