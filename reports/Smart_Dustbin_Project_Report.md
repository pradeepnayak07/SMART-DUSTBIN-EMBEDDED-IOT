# SMART DUSTBIN – EMBEDDED IoT SYSTEM

## 1. Introduction

The Smart Dustbin is an IoT-based embedded system designed to automate dustbin lid operation and monitor the waste level. The system uses an ESP32, ultrasonic sensor, servo motor, LED, and buzzer. Blynk IoT is used for real-time monitoring and notifications.

## 2. Problem Statement

Traditional dustbins require users to touch the lid and do not provide information about the amount of waste inside the bin. This project provides automatic lid operation and real-time waste-level monitoring.

## 3. Proposed Solution

The Smart Dustbin detects a nearby hand or object using an ultrasonic sensor and automatically opens the lid using a servo motor. The ultrasonic sensor also monitors the waste level. When the measured distance reaches the full-bin threshold, the LED and buzzer are activated and Blynk sends notifications.

## 4. Hardware Components

1. ESP32
2. HC-SR04 Ultrasonic Sensor
3. Servo Motor
4. LED
5. Buzzer
6. Connecting wires

## 5. Software and Platforms

- Arduino/C++ programming
- Wokwi Simulator
- Blynk IoT
- ESP32 Arduino libraries
- ESP32Servo library

## 6. Pin Configuration

| Component | ESP32 Pin |
|---|---|
| HC-SR04 TRIG | GPIO 5 |
| HC-SR04 ECHO | GPIO 18 |
| Servo | GPIO 19 |
| LED | GPIO 23 |
| Buzzer | GPIO 25 |

## 7. System Working

### Hand Detection

When an object or hand is detected within approximately 20 cm, the servo motor rotates to open the lid.

### Automatic Lid Closing

The lid remains open for approximately 2 seconds and then automatically closes.

### Waste-Level Monitoring

The ultrasonic sensor continuously measures the distance to the waste.

### Full Bin Detection

When the distance is 10 cm or less, the system considers the bin full.

The LED and buzzer turn ON and the Blynk dashboard updates the bin status.

## 8. Blynk IoT Integration

The system uses the following virtual datastreams:

| Virtual Pin | Function | Data Type |
|---|---|---|
| V0 | Waste Distance | Double |
| V1 | Bin Status | String |
| V2 | Lid Status | String |
| V3 | Bin Full | Integer |

## 9. Blynk Automation

Automation condition:

**Bin Full → Is equal to → 1**

Actions:

- In-app notification
- Email notification

## 10. Testing Results

### Normal Condition

Distance: 15.08 cm

Bin Status: NORMAL

Bin Full: 0

### Full Condition

Distance: 4.94 cm

Bin Status: BIN FULL

Bin Full: 1

LED: ON

Buzzer: ON

### Notification Test

Mobile notification: SUCCESS

Email notification: SUCCESS

## 11. Advantages

- Touchless operation
- Automatic lid control
- Real-time monitoring
- Full-bin alert
- Mobile notification
- Email notification
- IoT-enabled system
- Easy to simulate and demonstrate

## 12. Future Enhancements

- Add waste-level percentage calculation
- Add multiple ultrasonic sensors
- Add a rechargeable battery system
- Add solar charging
- Add physical hardware implementation
- Add cloud-based historical analytics

## 13. Conclusion

The Smart Dustbin successfully demonstrates an IoT-based automated waste management system. The ESP32 controls the ultrasonic sensor, servo motor, LED, and buzzer, while Blynk IoT provides real-time monitoring and notification functionality. The system was successfully tested in Wokwi and integrated with Blynk.