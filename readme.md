# Self-Driving Car Project

## Overview

This project is part of an embedded systems course and focuses on building a self-driving car using Arduino and various sensors. The car is equipped with functionalities such as motor control, distance measurement, and orientation sensing through an accelerometer and a compass module.

## Components Used

- Arduino UNO
- Motor Driver (L298N)
- Motors for driving and steering
- Joystick for manual control
- Ultrasonic Sensor for distance measurement
- Rotary Encoder for wheel rotation counting
- Compass Module for orientation sensing
- LiquidCrystal Display for information output
- Buttons and LEDs for additional controls

## Project Structure

The project is divided into multiple code sections:

1. **Motor Control and Joystick Input (`motor_control.ino`):**
   - Controls the movement of the car using motor drivers.
   - Reads input from a joystick to control speed and direction.

2. **Wheel Rotation Counting (`wheel_rotation_counter.ino`):**
   - Uses rotary encoders to count wheel rotations.
   - Provides information on distance traveled and average speed.

3. **LED and Button Control (`led_button_control.ino`):**
   - Controls the state of LEDs based on user input.
   - Utilizes buttons for resetting counters or activating specific features.

4. **Compass Module Integration (`compass_integration.ino`):**
   - Integrates a compass module to determine the car's orientation.
   - Displays cardinal direction based on the compass reading.

5. **Distance Measurement (`distance_measurement.ino`):**
   - Utilizes ultrasonic sensors to measure the distance between the car and obstacles.
   - Displays the distance on a LiquidCrystal Display.

## Usage

1. Upload each code section to the Arduino board separately.
2. Ensure all components are correctly connected.
3. Power on the self-driving car.
4. Interact with the joystick, buttons, and other controls as needed.
5. Observe information on the LCD regarding distance, wheel rotations, and orientation.

## Notes

- The project includes features for manual control and data monitoring for testing purposes.
- Adjust the control logic and integrate additional sensors for autonomous navigation.

## Contributors

- [Your Name]
- [Other contributors, if any]

## License

This project is open-source under the [MIT License](LICENSE).
