# Smart Dustbin – Industry-Oriented Embedded IoT System

## 1. Introduction

The Smart Dustbin is an ESP32-based embedded IoT system designed to provide touchless lid operation, waste-level monitoring, local alerts, and remote monitoring through Blynk IoT.

The system uses two HC-SR04 ultrasonic sensors:

* One sensor detects a nearby hand or object.
* The second sensor measures the waste level inside the dustbin.

The ESP32 processes the sensor readings and controls the servo motor, LEDs, buzzer, and Blynk IoT communication.

---

## 2. Problem Statement

Traditional dustbins generally require users to manually touch the lid and do not provide information about the current waste level.

The Smart Dustbin addresses these problems by providing:

* Touchless lid operation
* Automatic lid control
* Waste-level monitoring
* Full-bin detection
* Local LED and buzzer alerts
* Real-time IoT monitoring
* Full-bin notification through Blynk

---

## 3. Objectives

The main objectives of the project are:

* Detect a nearby hand or object using an ultrasonic sensor.
* Automatically open the dustbin lid.
* Automatically close the lid when the object leaves the detection range.
* Measure the distance between the waste and the top of the bin.
* Calculate the approximate waste fill percentage.
* Detect a full-bin condition.
* Activate the red LED and buzzer when the bin is full.
* Show real-time sensor and status information on Blynk.
* Send a Blynk notification when the bin becomes full.
* Test the complete system using Wokwi simulation.

---

## 4. System Requirements

### 4.1 Hardware Requirements

* ESP32 development board
* HC-SR04 ultrasonic sensor ×2
* SG90 servo motor
* Green LED
* Red LED
* Buzzer
* Breadboard
* Jumper wires
* Suitable power supply

### 4.2 Software Requirements

* Arduino IDE
* ESP32 board package
* ESP32Servo library
* Blynk IoT library
* Wokwi simulator
* VS Code
* Git
* GitHub

---

## 5. Hardware Components and Functions

| Component                 |    Quantity | Function                                          |
| ------------------------- | ----------: | ------------------------------------------------- |
| ESP32                     |           1 | Main controller and Wi-Fi communication           |
| HC-SR04 Ultrasonic Sensor |           2 | Hand/object detection and waste-level measurement |
| SG90 Servo Motor          |           1 | Automatic lid control                             |
| Green LED                 |           1 | Normal-bin indication                             |
| Red LED                   |           1 | Full-bin indication                               |
| Buzzer                    |           1 | Audible full-bin alert                            |
| Breadboard                |           1 | Circuit prototyping                               |
| Jumper Wires              | As required | Electrical connections                            |
| Power Supply              |           1 | Provides system power                             |

---

## 6. Pin Configuration

| Component         | ESP32 GPIO |
| ----------------- | ---------: |
| Hand Sensor TRIG  |     GPIO 5 |
| Hand Sensor ECHO  |    GPIO 18 |
| Waste Sensor TRIG |    GPIO 12 |
| Waste Sensor ECHO |    GPIO 14 |
| Servo Motor       |    GPIO 19 |
| Green LED         |    GPIO 23 |
| Buzzer            |    GPIO 25 |
| Red LED           |    GPIO 26 |

---

## 7. System Architecture

```text
             Hand/Object
                  |
                  v
       Hand Ultrasonic Sensor
                  |
                  v
                ESP32
                  |
                  v
            Servo Motor
                  |
                  v
           Automatic Lid
                  
       Waste Ultrasonic Sensor
                  |
                  v
            Waste Distance
                  |
                  v
          Fill Percentage
                  |
          +-------+-------+
          |               |
          v               v
       NORMAL          BIN FULL
          |               |
          v               v
     Green LED       Red LED + Buzzer
                          |
                          v
                   Blynk Notification
                          |
                          v
                  Remote Monitoring
```

---

## 8. Working Principle

The system operates using two independent ultrasonic sensors.

### 8.1 Hand/Object Detection

The first HC-SR04 ultrasonic sensor is connected to GPIO 5 and GPIO 18.

It continuously measures the distance between the sensor and a nearby hand or object.

The configured detection threshold is:

```text
Hand/Object Detection Threshold = 20 cm
```

When the measured distance is less than or equal to 20 cm:

```text
Hand/Object Detected
        |
        v
      ESP32
        |
        v
   Servo Opens Lid
```

When the object leaves the detection range, the ESP32 commands the servo to close the lid.

---

## 9. Automatic Lid Control

The SG90 servo motor is connected to GPIO 19.

The configured servo positions are:

```text
Closed Angle = 0°
Open Angle   = 90°
```

When an object is detected within the configured hand-detection range, the servo moves to the open position.

When no object is detected, the servo returns to the closed position.

```text
Object Detected
      |
      v
Lid Opens
      |
      v
Object Leaves
      |
      v
Lid Closes
```

---

## 10. Waste-Level Detection

The second HC-SR04 ultrasonic sensor is connected to:

```text
TRIG = GPIO 12
ECHO = GPIO 14
```

This sensor is positioned at the top of the dustbin.

It measures the distance between the sensor and the waste surface.

As the amount of waste increases:

```text
Waste Amount ↑
      |
      v
Distance to Waste ↓
```

Therefore, a smaller measured distance indicates a higher waste level.

---

## 11. Fill Percentage Calculation

The project uses the following calculation:

```text
Fill Level = Bin Height - Measured Distance

Fill Percentage =
(Fill Level / Bin Height) × 100
```

The configured bin height is:

```text
Bin Height = 20 cm
```

For example:

```text
Measured Distance = 8 cm

Fill Level = 20 - 8
           = 12 cm

Fill Percentage = (12 / 20) × 100
                 = 60%
```

The calculated value is limited between 0% and 100%.

---

## 12. Full-Bin Detection

The configured full-bin threshold is:

```text
Full-Bin Threshold = 10 cm
```

The logic is:

```text
Waste Distance <= 10 cm
          |
          v
      BIN FULL
          |
      +---+---+
      |       |
      v       v
  Red LED   Buzzer
      |
      v
Blynk Notification
```

When the waste distance is greater than 10 cm:

```text
Bin Status = NORMAL
```

When the waste distance is less than or equal to 10 cm:

```text
Bin Status = BIN FULL
Bin Full   = 1
```

---

## 13. Alert System

### 13.1 Normal Condition

```text
Green LED = ON
Red LED   = OFF
Buzzer    = OFF
```

### 13.2 Full-Bin Condition

```text
Green LED = OFF
Red LED   = ON
Buzzer    = ON
Bin Status = BIN FULL
Bin Full   = 1
```

The system also sends a Blynk event notification when the bin changes from a normal state to a full state.

The notification is not repeatedly triggered while the bin remains continuously full.

---

## 14. Blynk IoT Integration

The ESP32 connects to the configured Wi-Fi network and Blynk Cloud.

The following virtual pins are used:

| Virtual Pin | Function           | Data Type |
| ----------- | ------------------ | --------- |
| V0          | Waste Distance     | Double    |
| V1          | Bin Status         | String    |
| V2          | Lid Status         | String    |
| V3          | Bin Full Indicator | Integer   |

### V0 – Waste Distance

Displays the measured distance between the waste sensor and the waste surface.

Example:

```text
V0 = 8.01 cm
```

### V1 – Bin Status

Displays:

```text
NORMAL
```

or:

```text
BIN FULL
```

### V2 – Lid Status

Displays:

```text
OPEN
```

or:

```text
CLOSED
```

### V3 – Bin Full Indicator

The value is:

```text
0 = Normal
1 = Bin Full
```

---

## 15. Blynk Notification

The system uses the Blynk event:

```text
bin_full
```

When the waste distance reaches the full-bin threshold, the ESP32 triggers the Blynk event.

Notification message:

```text
Smart Dustbin is FULL! Please empty the dustbin.
```

The notification is triggered only when the system changes from a normal state to a full state.

When the bin returns to a normal state, the notification state is reset so that a future full-bin condition can generate another notification.

---

## 16. Wokwi Virtual Simulation

The project is tested using the Wokwi virtual simulation environment.

The simulation contains:

* ESP32
* Hand-detection HC-SR04 sensor
* Waste-level HC-SR04 sensor
* SG90 servo motor
* Green LED
* Red LED
* Buzzer

The simulation verifies sensor readings, servo movement, LED/buzzer operation, Serial Monitor output, and Blynk integration.

---

## 17. Simulation Workflow

```text
Open Wokwi Project
        |
        v
Verify Circuit
        |
        v
Run Simulation
        |
        v
Change Hand Sensor Distance
        |
        v
Verify Lid Opening/Closing
        |
        v
Change Waste Sensor Distance
        |
        v
Verify Fill Percentage
        |
        v
Verify Full-Bin Detection
        |
        v
Verify Red LED + Buzzer
        |
        v
Verify Blynk Dashboard
        |
        v
Verify Notification
```

---

## 18. Testing Plan

| Test Case | Input/Condition               | Expected Result                |
| --------- | ----------------------------- | ------------------------------ |
| Test 1    | No nearby object              | Lid remains closed             |
| Test 2    | Hand/object ≤ 20 cm           | Lid opens                      |
| Test 3    | Object leaves detection range | Lid closes                     |
| Test 4    | Waste distance > 10 cm        | Bin status NORMAL              |
| Test 5    | Waste distance ≤ 10 cm        | Bin status BIN FULL            |
| Test 6    | Full-bin condition            | Red LED ON                     |
| Test 7    | Full-bin condition            | Buzzer ON                      |
| Test 8    | Full-bin condition            | Blynk V3 becomes 1             |
| Test 9    | Normal condition              | Blynk V3 becomes 0             |
| Test 10   | Blynk connected               | Dashboard receives data        |
| Test 11   | Normal → Full transition      | Blynk full-bin event triggered |
| Test 12   | Full → Normal transition      | Notification state resets      |

---

## 19. Serial Monitor Diagnostics

The system outputs sensor and status information through the Serial Monitor at:

```text
115200 baud
```

Example output:

```text
=================================
 Smart Dustbin - IoT System
=================================
Hand Sensor: GPIO 5 / 18
Waste Sensor: GPIO 12 / 14
Servo: GPIO 19
Green LED: GPIO 23
Buzzer: GPIO 25
Red LED: GPIO 26
---------------------------------
Hand detection: <= 20.00 cm
Full-bin threshold: <= 10.00 cm
Bin height: 20.00 cm
---------------------------------
Connecting to Blynk...
Blynk connection initialized
System Ready
---------------------------------
```

During operation, the Serial Monitor displays:

```text
Hand Distance: 15.07 cm
Hand/Object detected!
Lid: OPEN
Waste Distance: 8.01 cm
Fill Percentage: 59.95%
Bin Status: BIN FULL
---------------------------------
```

---

## 20. Project Folder Structure

```text
SMART_DUSTBIN_EMBEDDED_SYSTEM/
│
├── arduino_code/
│   └── Smart_Dustbin_Blynk.ino
│
├── circuit_diagram/
│   └── Smart_Dustbin_Circuit1.png
│
├── data/
│   └── Sensor_Test_Results.txt
│
├── docs/
│   ├── Project_Documentation.md
│   └── Final_Project_Summary.md
│
├── outputs/
│   └── src/
│       ├── main.ino
│       ├── main_backup.ino
│       ├── sensor_module.ino
│       ├── lid_control.ino
│       ├── bin_level_module.ino
│       └── alert_module.ino
│
├── reports/
│   └── Smart_Dustbin_Project_Report.md
│
├── screenshots/
│   ├── S1_esp32_initial_test.png
│   ├── S2_ultrasonic_circuit.png
│   ├── S3_ultrasonic_distance_test.png
│   ├── S4_Servo_Wiring.png
│   ├── S5_Servo_Wiring_Test.png
│   ├── S6_Servo_Object_Detection.png
│   ├── S7_Normal_Distance_Detection.png
│   ├── S8_Hand_Detection_Servo_Open.png
│   ├── S9_Blynk_Live_Dashboard_Bin_Full_Test.png
│   ├── S10_Blynk_Live_Dashboard_Normal_Bin.png
│   ├── S11_Blynk_V3_Bin_Full.png
│   ├── S12_Blynk_Automation.png
│   ├── S13_Blynk_Bin_Full_Alert.png
│   ├── S14_Blynk_Mobile_Notification.png
│   ├── S15_Blynk_Email_Notification.png
│   ├── S16_Blynk_Dashboard.png
│   └── S17_Final_Working_Smart_Dustbin.png
│
├── simulation/
│   ├── README.md
│   └── Wokwi_Project_Link.txt
│
└── README.md
```

---

## 21. How to Run on Real Hardware

1. Install Arduino IDE.
2. Install ESP32 board support.
3. Install the required libraries.
4. Connect the ESP32 board.
5. Select the appropriate ESP32 board.
6. Select the correct COM port.
7. Open `Smart_Dustbin_Blynk.ino`.
8. Enter the required Blynk credentials.
9. Configure the Wi-Fi credentials.
10. Verify the pin configuration.
11. Upload the program to the ESP32.
12. Open Serial Monitor.
13. Set the baud rate to 115200.
14. Test hand/object detection.
15. Verify automatic lid operation.
16. Test waste-level measurement.
17. Test full-bin detection.
18. Verify LED and buzzer alerts.
19. Verify Blynk dashboard updates.
20. Verify the Blynk full-bin notification.

---

## 22. How to Run in Wokwi

1. Open the Wokwi project.
2. Verify the ESP32 circuit.
3. Verify both ultrasonic sensors.
4. Verify the servo motor.
5. Verify the LEDs and buzzer.
6. Open the Arduino sketch.
7. Verify Blynk credentials and configuration.
8. Start the simulation.
9. Change the hand sensor distance.
10. Verify lid opening and closing.
11. Change the waste sensor distance.
12. Verify the calculated fill percentage.
13. Test the full-bin threshold.
14. Verify the red LED and buzzer.
15. Verify the Blynk dashboard.
16. Verify the full-bin notification.
17. Capture the required screenshots.

---

## 23. Evidence and Screenshots

The project contains evidence for:

* ESP32 initialization
* Ultrasonic sensor circuit
* Ultrasonic distance measurement
* Servo wiring
* Servo testing
* Object detection
* Automatic lid operation
* Normal-bin condition
* Full-bin condition
* Blynk dashboard
* Blynk automation
* Blynk mobile notification
* Blynk email notification
* Serial Monitor output
* Final working system

The screenshots are stored inside the `screenshots` directory.

---

## 24. Industry Relevance

The Smart Dustbin concept can be adapted for:

* Smart cities
* Educational campuses
* Offices
* Hospitals
* Airports
* Shopping malls
* Public areas
* Industrial facilities

Remote waste-level monitoring can help organizations identify bins that require attention and support more efficient waste collection.

---

## 25. Future Enhancements

Possible future improvements include:

* LCD or OLED display
* Rechargeable battery operation
* Solar charging
* More accurate distance sensors
* Multiple-bin monitoring
* Historical cloud analytics
* Waste classification using AI/computer vision
* GPS-based bin tracking
* Collection-route optimization
* Advanced notification management

---

## 26. Learning Outcomes

This project demonstrates practical knowledge of:

* ESP32 programming
* Embedded C/C++
* GPIO interfacing
* Ultrasonic sensor interfacing
* Servo motor control
* Sensor-based decision making
* LED and buzzer control
* Wi-Fi connectivity
* IoT communication
* Blynk integration
* Wokwi virtual simulation
* Embedded-system testing
* Technical documentation
* Git and GitHub project management

---

## 27. Conclusion

The Smart Dustbin successfully demonstrates an ESP32-based embedded IoT waste-management prototype.

The system combines:

```text
ESP32
   +
Two Ultrasonic Sensors
   +
Servo Motor
   +
Green/Red LEDs
   +
Buzzer
   +
Wi-Fi
   +
Blynk IoT
   +
Wokwi Simulation
```

to provide:

* Touchless hand/object detection
* Automatic lid opening
* Automatic lid closing
* Waste-level monitoring
* Fill-percentage calculation
* Full-bin detection
* LED and buzzer alerts
* Blynk real-time monitoring
* Full-bin notification
* Virtual simulation and testing

The implementation is designed to be executable, beginner-friendly, GitHub-ready, and suitable for project demonstration and placement discussion.

---

## 28. Author

**Pradeep Nayak**

B.Tech – Computer Science and Engineering

Nalanda Institute of Technology, Bhubaneswar

**Project:** Smart Dustbin – Industry-Oriented Embedded IoT System
