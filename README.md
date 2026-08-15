# Smart Dustbin – Industry-Oriented Embedded IoT System

An ESP32-based Smart Dustbin project that provides touchless lid control, waste-level monitoring, automatic full-bin detection, LED/buzzer alerts, and real-time IoT monitoring through Blynk. The project is developed and tested using Wokwi simulation.

## 1. Project Overview

The Smart Dustbin is an embedded IoT system designed to automate dustbin operation and monitor the waste level.

The system uses **two HC-SR04 ultrasonic sensors**:

* One sensor detects a hand/object near the dustbin.
* The second sensor measures the distance between the top of the bin and the waste.

The ESP32 processes these sensor readings and:

* Opens the lid automatically when a hand/object is detected.
* Automatically closes the lid after the configured open duration.
* Calculates the waste fill percentage.
* Detects a full-bin condition.
* Activates the red LED and buzzer when the bin is full.
* Shows real-time information on the Blynk dashboard.
* Sends a Blynk full-bin notification.

---

## 2. Problem Statement

Traditional dustbins require users to touch the lid and do not provide information about the current waste level.

This project addresses these problems through:

* Touchless lid operation.
* Automatic waste-level monitoring.
* Full-bin detection.
* Local LED and buzzer alerts.
* Remote IoT monitoring.

---

## 3. Objectives

* Implement automatic dustbin lid control.
* Detect nearby hand/object movement using an ultrasonic sensor.
* Monitor waste level using a dedicated ultrasonic sensor.
* Calculate the approximate waste fill percentage.
* Detect the full-bin condition using a configurable threshold.
* Provide visual and audible alerts.
* Display real-time data through Blynk IoT.
* Send a notification when the bin becomes full.
* Demonstrate the complete system through Wokwi simulation.

---

## 4. Industry Relevance

The Smart Dustbin concept can be adapted for:

* Smart cities
* Offices
* Educational campuses
* Hospitals
* Airports
* Shopping malls
* Public areas
* Industrial facilities

Real-time monitoring can help identify full bins and support more efficient waste collection.

---

## 5. Main Features

* ESP32-based controller
* Two ultrasonic sensors
* Touchless hand/object detection
* Automatic servo-based lid opening
* Automatic lid closing
* Waste-distance monitoring
* Fill-percentage calculation
* Full-bin detection
* Green LED for normal condition
* Red LED for full condition
* Buzzer alert
* Blynk IoT integration
* Real-time Blynk dashboard
* Full-bin Blynk notification
* Wokwi virtual simulation
* Serial Monitor diagnostics

---

## 6. Hardware Components

| Component                 |    Quantity | Purpose                                           |
| ------------------------- | ----------: | ------------------------------------------------- |
| ESP32                     |           1 | Main microcontroller and Wi-Fi connectivity       |
| HC-SR04 Ultrasonic Sensor |           2 | Hand/object detection and waste-level measurement |
| SG90 Servo Motor          |           1 | Automatic lid control                             |
| Green LED                 |           1 | Normal-bin indication                             |
| Red LED                   |           1 | Full-bin indication                               |
| Buzzer                    |           1 | Audible full-bin alert                            |
| Breadboard                |           1 | Circuit prototyping                               |
| Jumper Wires              | As required | Component connections                             |
| Power Supply              |           1 | System power                                      |

---

## 7. Software and Tools

* Arduino/C++
* Arduino IDE
* ESP32 Board Package
* ESP32Servo Library
* Blynk IoT
* Wokwi
* Git
* GitHub
* VS Code

---

## 8. Pin Configuration

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

## 9. System Architecture

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
            +-----+-----+
            |           |
            v           v
         NORMAL      BIN FULL
            |           |
            v           v
       Green LED    Red LED + Buzzer
                        |
                        v
                 Blynk Notification
                        |
                        v
                 Remote Monitoring
```

---

## 10. System Working

### 10.1 Hand/Object Detection

The hand-detection ultrasonic sensor measures the distance from the sensor to a nearby object.

The configured detection threshold is:

```text
Hand/Object Detection <= 20 cm
```

When the measured distance is within this range, the ESP32 detects a hand/object and commands the servo to open the lid.

### 10.2 Automatic Lid Control

The servo opens the lid to the configured open angle.

The current implementation keeps the lid open for approximately:

```text
2 seconds
```

After the configured duration, the servo returns the lid to the closed position.

If the bin is detected as full, the system keeps the lid closed.

### 10.3 Waste-Level Detection

The second ultrasonic sensor is used specifically for waste-level measurement.

It measures the distance between the top of the bin and the waste surface.

As the waste level increases, the measured distance decreases.

---

## 11. Fill Percentage Calculation

The system uses the following calculation:

```text
Fill Level = Bin Height - Waste Distance

Fill Percentage =
((Bin Height - Waste Distance) / Bin Height) × 100
```

Configured bin height:

```text
20 cm
```

Example:

```text
Waste Distance = 10 cm

Fill Level = 20 - 10
           = 10 cm

Fill Percentage = (10 / 20) × 100
                = 50%
```

The calculated percentage is limited to a range of 0% to 100%.

---

## 12. Full-Bin Detection

The configured full-bin threshold is:

```text
Waste Distance <= 10 cm
```

When the waste distance reaches or falls below this threshold:

```text
BIN FULL
```

The system then:

```text
Red LED  = ON
Green LED = OFF
Buzzer   = ON
Lid      = CLOSED
Bin Full = 1
```

A Blynk full-bin event is triggered when the system changes from a normal condition to a full condition.

---

## 13. Normal Condition

When the waste distance is above the full-bin threshold:

```text
Bin Status = NORMAL
Bin Full   = 0
Green LED  = ON
Red LED    = OFF
Buzzer     = OFF
```

The lid can operate normally based on hand/object detection.

---

## 14. Blynk IoT Integration

The ESP32 connects to Wi-Fi and Blynk Cloud.

The following virtual datastreams are used:

| Virtual Pin | Function       | Data              |
| ----------- | -------------- | ----------------- |
| V0          | Waste Distance | Distance in cm    |
| V1          | Bin Status     | NORMAL / BIN FULL |
| V2          | Lid Status     | OPEN / CLOSED     |
| V3          | Bin Full       | 0 / 1             |

Example full-bin dashboard state:

```text
Waste Distance : 8.01 cm
Bin Status     : BIN FULL
Lid Status     : CLOSED
Bin Full       : 1
```

Example normal dashboard state:

```text
Waste Distance : >10 cm
Bin Status     : NORMAL
Lid Status     : CLOSED
Bin Full       : 0
```

---

## 15. Blynk Notification

The project uses a Blynk event:

```text
bin_full
```

The event is triggered when the bin changes from:

```text
NORMAL → BIN FULL
```

This prevents repeated event notifications while the bin remains continuously full.

The notification message is:

```text
Smart Dustbin is FULL! Please empty the dustbin.
```

The Blynk notification functionality was tested successfully.

---

## 16. Wokwi Virtual Simulation

The project was developed and tested using Wokwi.

### Simulated Components

* ESP32
* Two HC-SR04 ultrasonic sensors
* SG90 servo motor
* Green LED
* Red LED
* Buzzer

### Simulation Workflow

```text
Open Wokwi
    ↓
Open Smart Dustbin Project
    ↓
Verify Circuit
    ↓
Run Simulation
    ↓
Change Hand Sensor Distance
    ↓
Verify Lid Operation
    ↓
Change Waste Sensor Distance
    ↓
Verify Fill Percentage
    ↓
Verify BIN FULL Condition
    ↓
Verify LED + Buzzer
    ↓
Verify Blynk Dashboard
    ↓
Verify Notification
```

### Wokwi Project

Wokwi Project:

https://wokwi.com/projects/472076620747237377

---

## 17. Testing

### Test 1 – Normal Condition

```text
Waste Distance : 15.08 cm
Bin Status     : NORMAL
Bin Full       : 0
```

Expected result:

```text
Green LED = ON
Red LED   = OFF
Buzzer    = OFF
```

**Status: PASS**

### Test 2 – Full Bin Condition

```text
Waste Distance : 4.94 cm
Bin Status     : BIN FULL
Bin Full       : 1
LED            : ON
Buzzer         : ON
Lid Status     : CLOSED
```

**Status: PASS**

### Test 3 – Hand/Object Detection

```text
Detection Range : <= 20 cm
Lid             : OPEN
Automatic Close : Approximately 2 seconds
```

**Status: PASS**

### Test 4 – Blynk Integration

```text
V0 – Waste Distance
V1 – Bin Status
V2 – Lid Status
V3 – Bin Full
```

**Status: PASS**

### Notification Testing

```text
Mobile Notification : SUCCESS
Email Notification  : SUCCESS
```

**Status: PASS**

---

## 18. Final Test Result

The major system functions were successfully tested:

| Function                    | Result |
| --------------------------- | ------ |
| Hand/Object Detection       | PASS   |
| Automatic Lid Opening       | PASS   |
| Automatic Lid Closing       | PASS   |
| Waste-Level Detection       | PASS   |
| Fill Percentage Calculation | PASS   |
| Full-Bin Detection          | PASS   |
| Green LED Alert             | PASS   |
| Red LED Alert               | PASS   |
| Buzzer Alert                | PASS   |
| Blynk Dashboard             | PASS   |
| Bin Full Indicator          | PASS   |
| Blynk Notification          | PASS   |
| Wokwi Simulation            | PASS   |

---

## 19. Project Folder Structure

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
│   └── Final_Project_Documentation.md
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
├── reports/
│   └── Smart_Dustbin_Project_Report.md
│
└── README.md
```

---

## 20. How to Run

### Wokwi Simulation

1. Open the Wokwi project.
2. Verify the circuit connections.
3. Open the Arduino sketch.
4. Configure the required Blynk credentials.
5. Start the simulation.
6. Open the Serial Monitor.
7. Change the hand sensor distance to test lid operation.
8. Change the waste sensor distance to test waste-level detection.
9. Set the waste distance to 10 cm or less to test the full-bin condition.
10. Verify the LEDs and buzzer.
11. Verify the Blynk dashboard.
12. Verify the full-bin notification.

### Real Hardware

1. Install Arduino IDE.
2. Install ESP32 board support.
3. Install the required libraries.
4. Connect the ESP32.
5. Select the appropriate ESP32 board.
6. Select the correct COM port.
7. Connect the two ultrasonic sensors.
8. Connect the servo, LEDs and buzzer.
9. Configure Blynk credentials.
10. Upload the Arduino code.
11. Open Serial Monitor at 115200 baud.
12. Test hand detection.
13. Test automatic lid operation.
14. Test waste-level detection.
15. Test full-bin alerts.
16. Verify Blynk monitoring and notifications.

---

## 21. Evidence and Documentation

The project documentation includes evidence for:

* ESP32 initialization
* Ultrasonic sensor testing
* Servo wiring
* Object detection
* Automatic lid operation
* Normal-bin condition
* Full-bin condition
* Blynk dashboard
* Blynk datastreams
* Blynk automation
* Mobile notification
* Email notification
* Serial Monitor output
* Final working simulation

---

## 22. Future Enhancements

Possible future improvements include:

* LCD/OLED display
* More accurate distance sensors
* Battery-powered operation
* Solar charging
* Multiple-bin monitoring
* Cloud-based historical analytics
* GPS-based bin tracking
* AI-based waste classification
* Collection-route optimization
* Physical enclosure and industrial-grade hardware

---

## 23. Learning Outcomes

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
* Wokwi simulation
* Embedded-system testing
* Technical documentation
* Git and GitHub project management

---

## 24. Conclusion

The Smart Dustbin successfully demonstrates an embedded IoT-based waste-management prototype.

The system combines:

```text
ESP32
   +
Two Ultrasonic Sensors
   +
Servo Motor
   +
LEDs + Buzzer
   +
Wi-Fi
   +
Blynk IoT
   +
Wokwi Simulation
```

to provide:

* Touchless automatic lid operation
* Waste-level monitoring
* Fill-percentage calculation
* Full-bin detection
* Local LED and buzzer alerts
* Real-time Blynk monitoring
* Full-bin notification
* Virtual simulation and testing

The completed prototype demonstrates the practical integration of embedded systems, sensors, actuators, Wi-Fi connectivity and IoT cloud monitoring.

---

## 25. Author

**Pradeep Nayak**

B.Tech – Computer Science and Engineering
Nalanda Institute of Technology, Bhubaneswar

**Project:** Smart Dustbin – Industry-Oriented Embedded IoT System
