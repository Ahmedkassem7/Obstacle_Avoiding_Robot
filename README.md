# Obstacle Avoiding Robot (Embedded System using Arduino Uno)

## Project Overview

This project involves designing and building an obstacle-avoiding robot using Arduino Uno (ATmega328P) as the microcontroller. The robot is equipped with ultrasonic sensors to detect obstacles and navigate through an environment autonomously.

## Features

- Automatic obstacle avoidance using ultrasonic sensors.
- Real-time decision-making based on sensor data.
- Motor control for movement and direction adjustments.

## Hardware Components

- Arduino Uno (ATmega328P).
- Motors for movement.
- Wheels for mobility.
- Chassis to hold components.
- Ultrasonic sensors (trig and echo) for obstacle detection.

## Pin Configuration

- Ultrasonic Sensor Pins:
  - Trig (Pin 8)
  - Echo (Pin 9, 10, 11, 12, 13)

- Motor Driver Pins:
  - ENA, IN1, IN2, IN3, IN4, ENB (defined constants)

## Arduino Sketch Explanation

- **`avoidObstacle` Function:**
  - Stops the car, delays for 100 milliseconds.
  - Checks sensor data and performs appropriate actions:
    - If obstacles detected on all sides, move backward.
    - If obstacle in the forward direction, move backward or turn.
    - If no obstacles, move forward.

- **Other Functions:**
  - `moveForward`, `moveBackward`, `turnRight`, `turnLeft`, `stopCar`: Control the movement of the robot.

- **`measureDistance` Function:**
  - Ultrasonic distance measurement using pulseIn.

## Usage

1. Upload the provided Arduino sketch to the Arduino Uno.
2. Connect the hardware components as specified in the pin configuration.
3. Power on the robot and observe its obstacle-avoidance behavior.

## Used Algorithm
```
void avoidObstacle(int leftDist, int middleDist, int rightDist) {
  stopCar();
  delay(100);
  if (middleDist <= DISTANCE_THRESHOLD_FORWARD && rightDist <= DISTANCE_THRESHOLD_SIDE && leftDist <= DISTANCE_THRESHOLD_SIDE) {
    stopCar();
    delay(150);
    moveBackward();
    delay(70);
  }
  else {
    if (middleDist <= DISTANCE_THRESHOLD_FORWARD) {
      stopCar();
      delay(100);
      moveBackward();
      delay(50);
      if (rightDist <= DISTANCE_THRESHOLD_SIDE ) {
        moveBackward();
        delay(20);
        turnLeft();
        delay(750);
      }
       else {
        turnRight();
        delay(700);
      }

    }
    else {
      stopCar();
      delay(150);
      moveForward();
      delay(100);

    }
  }
}
```

