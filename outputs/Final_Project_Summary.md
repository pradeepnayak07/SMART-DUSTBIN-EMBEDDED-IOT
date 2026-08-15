# Smart Dustbin – Industry-Oriented Embedded IoT System

## Project Status

COMPLETED

## Project Type

Embedded IoT System

## Main Controller

ESP32

## Sensors

* HC-SR04 Ultrasonic Sensor ×2

  * Hand/Object Detection Sensor
  * Waste-Level Detection Sensor

## Actuators and Indicators

* SG90 Servo Motor
* Green LED
* Red LED
* Buzzer

## IoT Platform

Blynk IoT

## Simulation Platform

Wokwi

## Programming

Embedded C/C++ using Arduino framework

## Main Features

* Touchless hand/object detection
* Automatic dustbin lid opening
* Automatic lid closing
* Waste-level distance measurement
* Fill percentage calculation
* Full-bin detection
* Green LED normal indication
* Red LED full-bin indication
* Buzzer full-bin alert
* Blynk real-time dashboard
* Blynk virtual datastreams
* Blynk full-bin notification
* Wokwi virtual simulation
* Serial Monitor diagnostics

## System Working

The system uses two ultrasonic sensors connected to the ESP32.

### Hand/Object Detection

The first HC-SR04 sensor detects a nearby hand or object.

Configured detection threshold:

```text
≤ 20 cm
```

When an object is detected within this range, the ESP32 commands the SG90 servo motor to open the dustbin lid.

When the object leaves the detection range, the lid returns to the closed position.

### Waste-Level Detection

The second HC-SR04 sensor measures the distance between the top of the dustbin and the waste surface.

As the amount of waste increases, the measured distance decreases.

Configured bin height:

```text
20 cm
```

### Fill Percentage

The system calculates the approximate fill percentage using:

```text
Fill Level = Bin Height - Waste Distance

Fill Percentage =
(Fill Level / Bin Height) × 100
```

The calculated percentage is limited between 0% and 100%.

Example:

```text
Bin Height = 20 cm
Waste Distance = 8 cm

Fill Level = 20 - 8
           = 12 cm

Fill Percentage = (12 / 20) × 100
                 = 60%
```

## Full-Bin Detection

Configured full-bin threshold:

```text
≤ 10 cm
```

When the waste sensor measures a distance of 10 cm or less:

```text
Bin Status = BIN FULL
Bin Full = 1
Red LED = ON
Buzzer = ON
Green LED = OFF
```

When the waste distance is greater than 10 cm:

```text
Bin Status = NORMAL
Bin Full = 0
Red LED = OFF
Buzzer = OFF
Green LED = ON
```

## Blynk Integration

The ESP32 sends real-time information to the Blynk dashboard.

| Virtual Pin | Function           | Data Type |
| ----------- | ------------------ | --------- |
| V0          | Waste Distance     | Double    |
| V1          | Bin Status         | String    |
| V2          | Lid Status         | String    |
| V3          | Bin Full Indicator | Integer   |

### Virtual Pin Values

```text
V0 → Waste distance in cm
V1 → NORMAL / BIN FULL
V2 → OPEN / CLOSED
V3 → 0 / 1
```

Where:

```text
V3 = 0 → Normal
V3 = 1 → Bin Full
```

## Blynk Notification

The system uses the Blynk event:

```text
bin_full
```

When the system changes from a normal condition to a full-bin condition, the event is triggered.

Notification message:

```text
Smart Dustbin is FULL! Please empty the dustbin.
```

The notification state is controlled so that repeated notifications are not continuously generated while the bin remains full.

When the bin returns to normal, the notification state is reset.

## Pin Configuration

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

## Testing Summary

### Test 1 – Normal Condition

```text
Waste Distance: > 10 cm
Bin Status: NORMAL
Bin Full: 0
Green LED: ON
Red LED: OFF
Buzzer: OFF
```

### Test 2 – Full-Bin Condition

```text
Waste Distance: ≤ 10 cm
Bin Status: BIN FULL
Bin Full: 1
Green LED: OFF
Red LED: ON
Buzzer: ON
```

### Test 3 – Hand/Object Detection

```text
Detection Range: ≤ 20 cm
Lid: OPEN
```

When the object leaves the detection range:

```text
Lid: CLOSED
```

### Test 4 – Blynk Integration

```text
V0 → Waste Distance
V1 → Bin Status
V2 → Lid Status
V3 → Bin Full
```

### Test 5 – Full-Bin Notification

```text
Blynk Full-Bin Event: CONFIGURED
```

The notification is triggered when the bin changes from normal to full.

## Wokwi Simulation

The project is simulated using Wokwi.

The simulation verifies:

* ESP32 operation
* Two ultrasonic sensors
* Hand/object detection
* Waste-level measurement
* Servo motor control
* Automatic lid operation
* Fill percentage calculation
* Full-bin detection
* Green LED operation
* Red LED operation
* Buzzer operation
* Serial Monitor output
* Blynk integration

## Project Evidence

The repository contains screenshots covering:

* ESP32 initialization
* Ultrasonic sensor testing
* Circuit configuration
* Servo wiring
* Servo testing
* Object detection
* Lid opening
* Normal-bin condition
* Full-bin condition
* Blynk dashboard
* Blynk automation
* Blynk notification configuration
* Mobile notification
* Email notification
* Serial Monitor
* Final working system

## Final Result

The Smart Dustbin successfully demonstrates an ESP32-based embedded IoT system capable of:

* Detecting nearby objects without physical contact
* Automatically controlling the dustbin lid
* Measuring waste level
* Calculating approximate fill percentage
* Detecting a full-bin condition
* Providing local LED and buzzer alerts
* Sending real-time information to Blynk
* Triggering a full-bin notification
* Operating through a Wokwi virtual simulation

## Project Outcome

The completed prototype provides a practical foundation for an IoT-enabled smart waste-management system and demonstrates embedded programming, sensor interfacing, actuator control, Wi-Fi connectivity, IoT integration, simulation, testing, and technical documentation.

## Author

**Pradeep Nayak**

B.Tech – Computer Science and Engineering

Nalanda Institute of Technology, Bhubaneswar

**Project:** Smart Dustbin – Industry-Oriented Embedded IoT System
