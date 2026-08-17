SMART DUSTBIN – SENSOR TEST RESULTS

========================================
TEST 1 – NORMAL BIN CONDITION
========================================

Waste Distance: 15.08 cm
Bin Status: NORMAL
Bin Full: 0
Green LED: ON
Red LED: OFF
Buzzer: OFF

Result: PASS


========================================
TEST 2 – FULL BIN CONDITION
========================================

Waste Distance: 4.94 cm
Bin Status: BIN FULL
Bin Full: 1
Green LED: OFF
Red LED: ON
Buzzer: ON

Result: PASS


========================================
TEST 3 – HAND/OBJECT DETECTION
========================================

Detection Threshold: <= 20 cm
Hand/Object Detected: YES
Lid: OPEN

When object leaves detection range:
Lid: CLOSED

Result: PASS


========================================
TEST 4 – WASTE LEVEL MONITORING
========================================

Bin Height: 20 cm

Example Waste Distance: 7.99 cm
Approximate Fill Percentage: 60.04%

Bin Status: BIN FULL
Bin Full: 1

Result: PASS


========================================
TEST 5 – BLYNK DASHBOARD
========================================

V0 – Waste Distance
V1 – Bin Status
V2 – Lid Status
V3 – Bin Full

Example Full-Bin State:

V0: 7.99 cm
V1: BIN FULL
V2: CLOSED
V3: 1

Result: PASS


========================================
TEST 6 – BLYNK NOTIFICATION
========================================

Full-Bin Event: bin_full

Mobile/In-App Notification: SUCCESS
Email Notification: SUCCESS

Result: PASS


========================================
FINAL TEST RESULT
========================================

Hand/Object Detection: PASS
Automatic Lid Control: PASS
Waste-Level Detection: PASS
Fill Percentage Calculation: PASS
Full-Bin Detection: PASS
Green LED Alert: PASS
Red LED Alert: PASS
Buzzer Alert: PASS
Blynk Dashboard: PASS
Blynk Notification: PASS
Wokwi Simulation: PASS

Overall Project Test Status: PASS