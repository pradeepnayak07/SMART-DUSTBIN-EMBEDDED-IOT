# Smart Dustbin – Wokwi Virtual Simulation

## 1. Simulation Platform

The Smart Dustbin is virtually tested using **Wokwi** with an ESP32-based circuit.

Wokwi is used to verify the sensor readings, servo operation, LED/buzzer alerts, waste-level detection, and Blynk IoT integration before physical hardware implementation.

---

## 2. Simulated Components

* ESP32
* HC-SR04 Ultrasonic Sensor ×2
* SG90 Servo Motor
* Green LED
* Red LED
* Buzzer
* Jumper Wires

---

## 3. Sensor Configuration

### Hand/Object Detection Sensor

* TRIG: GPIO 5
* ECHO: GPIO 18
* Detection threshold: ≤ 20 cm

### Waste-Level Sensor

* TRIG: GPIO 12
* ECHO: GPIO 14
* Full-bin threshold: ≤ 10 cm
* Bin height: 20 cm

---

## 4. Actuator Configuration

| Component |    GPIO |
| --------- | ------: |
| Servo     | GPIO 19 |
| Green LED | GPIO 23 |
| Buzzer    | GPIO 25 |
| Red LED   | GPIO 26 |

---

## 5. Simulation Features

The Wokwi simulation demonstrates:

1. Hand/object detection
2. Automatic lid opening
3. Automatic lid closing
4. Waste-level distance measurement
5. Fill-percentage calculation
6. Full-bin detection
7. Green LED normal indication
8. Red LED full-bin indication
9. Buzzer alert
10. Serial Monitor diagnostics
11. Blynk IoT integration
12. Blynk dashboard updates
13. Full-bin notification

---

## 6. Fill Percentage Calculation

The system calculates the approximate fill level using:

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
Waste Distance = 8 cm

Fill Level = 20 - 8
           = 12 cm

Fill Percentage = (12 / 20) × 100
                = 60%
```

The calculated value is limited between 0% and 100%.

---

## 7. Full-Bin Detection

The configured full-bin threshold is:

```text
Waste Distance ≤ 10 cm
```

When the waste distance is 10 cm or less:

```text
Bin Status = BIN FULL
Bin Full   = 1
Red LED    = ON
Green LED  = OFF
Buzzer     = ON
Lid        = CLOSED
```

The system also triggers the configured Blynk full-bin event.

---

## 8. Normal Condition

When the waste distance is greater than 10 cm:

```text
Bin Status = NORMAL
Bin Full   = 0
Green LED  = ON
Red LED    = OFF
Buzzer     = OFF
```

The lid operates normally according to hand/object detection.

---

## 9. Automatic Lid Operation

The hand-detection sensor checks for an object within:

```text
≤ 20 cm
```

When an object is detected:

```text
Hand/Object
     ↓
Ultrasonic Sensor
     ↓
ESP32
     ↓
Servo Motor
     ↓
Lid OPEN
```

The configured lid open duration is approximately:

```text
2 seconds
```

After the configured duration, the servo returns the lid to the closed position.

If the bin is full, the system keeps the lid closed.

---

## 10. Blynk IoT Integration

The ESP32 sends the following information to Blynk:

| Virtual Pin | Function       |
| ----------- | -------------- |
| V0          | Waste Distance |
| V1          | Bin Status     |
| V2          | Lid Status     |
| V3          | Bin Full       |

Example:

```text
Waste Distance : 8.01 cm
Bin Status     : BIN FULL
Lid Status     : CLOSED
Bin Full       : 1
```

---

## 11. Simulation Testing

### Test 1 – Normal Condition

Example:

```text
Waste Distance : 15.08 cm
Bin Status     : NORMAL
Bin Full       : 0
```

Expected:

```text
Green LED = ON
Red LED   = OFF
Buzzer    = OFF
```

**Result: PASS**

### Test 2 – Full Bin Condition

Example:

```text
Waste Distance : 4.94 cm
Bin Status     : BIN FULL
Bin Full       : 1
```

Expected:

```text
Red LED = ON
Buzzer  = ON
Lid     = CLOSED
```

**Result: PASS**

### Test 3 – Hand/Object Detection

```text
Detection Range : ≤ 20 cm
Lid             : OPEN
Automatic Close : Approximately 2 seconds
```

**Result: PASS**

### Test 4 – Blynk Integration

```text
V0 = Waste Distance
V1 = Bin Status
V2 = Lid Status
V3 = Bin Full
```

**Result: PASS**

---

## 12. Blynk Notification Testing

The full-bin notification functionality was tested successfully.

```text
Mobile Notification : SUCCESS
Email Notification  : SUCCESS
```

The notification is triggered when the bin changes from a normal state to a full state.

---

## 13. Simulation Workflow

```text
Open Wokwi
    ↓
Open Smart Dustbin Project
    ↓
Verify Circuit
    ↓
Run Simulation
    ↓
Test Hand/Object Distance
    ↓
Verify Servo Lid
    ↓
Test Waste Distance
    ↓
Verify Fill Percentage
    ↓
Test Full-Bin Threshold
    ↓
Verify LED + Buzzer
    ↓
Verify Blynk Dashboard
    ↓
Verify Notification
```

---

## 14. Wokwi Project Link

**Wokwi Project:**

https://wokwi.com/projects/472076620747237377

---

## 15. Final Simulation Result

The Wokwi simulation successfully demonstrates the major Smart Dustbin functions:

* Dual ultrasonic sensing
* Hand/object detection
* Automatic lid control
* Waste-level monitoring
* Fill-percentage calculation
* Full-bin detection
* Green LED indication
* Red LED alert
* Buzzer alert
* Blynk dashboard monitoring
* Full-bin notification
* Serial Monitor diagnostics

**Simulation Status: COMPLETED**
