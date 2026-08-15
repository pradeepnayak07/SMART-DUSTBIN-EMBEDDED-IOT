#define BLYNK_TEMPLATE_ID "TMPL3ReLJEQBg"
#define BLYNK_TEMPLATE_NAME "Smart Dustbin"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

// ============================================================
// BLYNK / WIFI
// ============================================================

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// Keep your existing Blynk auth token here.
// Do NOT share it publicly.
char auth[] = BLYNK_AUTH_TOKEN;

// ============================================================
// PIN CONFIGURATION
// ============================================================

// Sensor 1: Hand/Object Detection
#define HAND_TRIG_PIN 5
#define HAND_ECHO_PIN 18

// Sensor 2: Waste-Level Detection
#define WASTE_TRIG_PIN 12
#define WASTE_ECHO_PIN 14

// Actuators
#define SERVO_PIN 19
#define GREEN_LED_PIN 23
#define BUZZER_PIN 25
#define RED_LED_PIN 26

// ============================================================
// BLYNK VIRTUAL PINS
// ============================================================

#define VPIN_DISTANCE V0
#define VPIN_BIN_STATUS V1
#define VPIN_LID_STATUS V2
#define VPIN_BIN_FULL V3

// ============================================================
// THRESHOLDS
// ============================================================

const float HAND_DISTANCE = 20.0;

// Physical bin height used for percentage calculation.
// Change this value if your actual simulated bin height is different.
const float BIN_HEIGHT = 20.0;

// Full-bin threshold
const float FULL_DISTANCE = 10.0;

// ============================================================
// SERVO CONFIGURATION
// ============================================================

const int LID_CLOSED = 0;
const int LID_OPEN = 90;

const unsigned long LID_OPEN_TIME = 2000;

// ============================================================
// OBJECTS / VARIABLES
// ============================================================

Servo lidServo;
BlynkTimer timer;

bool lidIsOpen = false;
bool binIsFull = false;

unsigned long lidOpenedAt = 0;

// ============================================================
// READ ULTRASONIC DISTANCE
// ============================================================

float readDistance(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  float distance = duration * 0.0343 / 2.0;

  return distance;
}

// ============================================================
// CALCULATE FILL PERCENTAGE
// ============================================================

float calculateFillPercentage(float wasteDistance) {

  if (wasteDistance < 0) {
    return -1;
  }

  float fillLevel = BIN_HEIGHT - wasteDistance;

  if (fillLevel < 0) {
    fillLevel = 0;
  }

  if (fillLevel > BIN_HEIGHT) {
    fillLevel = BIN_HEIGHT;
  }

  float percentage = (fillLevel / BIN_HEIGHT) * 100.0;

  return percentage;
}

// ============================================================
// GET BIN STATUS
// ============================================================

String getBinStatus(float fillPercentage, float wasteDistance) {

  if (wasteDistance < 0) {
    return "SENSOR ERROR";
  }

  if (wasteDistance <= FULL_DISTANCE) {
    return "BIN FULL";
  }

  if (fillPercentage >= 90) {
    return "90% FULL";
  }

  if (fillPercentage >= 75) {
    return "75% FULL";
  }

  if (fillPercentage >= 50) {
    return "50% FULL";
  }

  if (fillPercentage >= 25) {
    return "25% FULL";
  }

  return "NORMAL";
}

// ============================================================
// UPDATE LOCAL ALERTS
// ============================================================

void updateAlerts(float wasteDistance) {

  if (wasteDistance < 0) {

    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    return;
  }

  if (wasteDistance <= FULL_DISTANCE) {

    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    if (!binIsFull) {

      Serial.println("=================================");
      Serial.println("!!! BIN FULL !!!");
      Serial.println("Red LED: ON");
      Serial.println("Buzzer: ON");
      Serial.println("=================================");

      binIsFull = true;
    }

  } else {

    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    if (binIsFull) {

      Serial.println("Bin status: NORMAL");
      binIsFull = false;
    }
  }
}

// ============================================================
// SEND DATA TO BLYNK
// ============================================================

void sendDataToBlynk() {

  float wasteDistance =
    readDistance(WASTE_TRIG_PIN, WASTE_ECHO_PIN);

  if (wasteDistance < 0) {

    Serial.println("Blynk: No valid waste-level reading");

    return;
  }

  float fillPercentage =
    calculateFillPercentage(wasteDistance);

  String binStatus =
    getBinStatus(fillPercentage, wasteDistance);

  // V0 = Waste distance
  Blynk.virtualWrite(VPIN_DISTANCE, wasteDistance);

  // V1 = Bin status
  Blynk.virtualWrite(VPIN_BIN_STATUS, binStatus);

  // V2 = Lid status
  if (lidIsOpen) {
    Blynk.virtualWrite(VPIN_LID_STATUS, "OPEN");
  } else {
    Blynk.virtualWrite(VPIN_LID_STATUS, "CLOSED");
  }

  // V3 = Full flag
  if (wasteDistance <= FULL_DISTANCE) {
    Blynk.virtualWrite(VPIN_BIN_FULL, 1);
  } else {
    Blynk.virtualWrite(VPIN_BIN_FULL, 0);
  }

  Serial.println("---------------------------------");
  Serial.print("Waste Distance: ");
  Serial.print(wasteDistance);
  Serial.println(" cm");

  Serial.print("Fill Percentage: ");
  Serial.print(fillPercentage);
  Serial.println("%");

  Serial.print("Bin Status: ");
  Serial.println(binStatus);

  Serial.print("Lid Status: ");
  Serial.println(lidIsOpen ? "OPEN" : "CLOSED");

  Serial.println("---------------------------------");
}

// ============================================================
// SETUP
// ============================================================

void setup() {

  Serial.begin(115200);

  // -----------------------------
  // Sensor pins
  // -----------------------------

  pinMode(HAND_TRIG_PIN, OUTPUT);
  pinMode(HAND_ECHO_PIN, INPUT);

  pinMode(WASTE_TRIG_PIN, OUTPUT);
  pinMode(WASTE_ECHO_PIN, INPUT);

  digitalWrite(HAND_TRIG_PIN, LOW);
  digitalWrite(WASTE_TRIG_PIN, LOW);

  // -----------------------------
  // Output pins
  // -----------------------------

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // -----------------------------
  // Servo
  // -----------------------------

  lidServo.attach(SERVO_PIN);

  lidServo.write(LID_CLOSED);

  // -----------------------------
  // Startup messages
  // -----------------------------

  Serial.println();
  Serial.println("=================================");
  Serial.println(" Smart Dustbin - IoT System");
  Serial.println("=================================");

  Serial.println("Hand Sensor: GPIO 5 / 18");
  Serial.println("Waste Sensor: GPIO 12 / 14");
  Serial.println("Servo: GPIO 19");
  Serial.println("Green LED: GPIO 23");
  Serial.println("Buzzer: GPIO 25");
  Serial.println("Red LED: GPIO 26");

  Serial.println("---------------------------------");
  Serial.println("Hand detection: <= 20 cm");
  Serial.println("Full-bin threshold: <= 10 cm");
  Serial.print("Bin height: ");
  Serial.print(BIN_HEIGHT);
  Serial.println(" cm");
  Serial.println("---------------------------------");

  // -----------------------------
  // Blynk
  // -----------------------------

  Serial.println("Connecting to Blynk...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Blynk connection initialized");
  Serial.println("System Ready");

  // Send Blynk data every second
  timer.setInterval(1000L, sendDataToBlynk);
}

// ============================================================
// LOOP
// ============================================================

void loop() {

  Blynk.run();
  timer.run();

  // ==========================================================
  // SENSOR 1: HAND / OBJECT DETECTION
  // ==========================================================

  float handDistance =
    readDistance(HAND_TRIG_PIN, HAND_ECHO_PIN);

  if (handDistance < 0) {

    Serial.println("Hand sensor: No valid reading");

  } else {

    Serial.print("Hand Distance: ");
    Serial.print(handDistance);
    Serial.println(" cm");

    // Open lid only when object is detected
    // and the bin is not currently full.
    if (handDistance <= HAND_DISTANCE &&
        !lidIsOpen &&
        !binIsFull) {

      lidServo.write(LID_OPEN);

      lidIsOpen = true;
      lidOpenedAt = millis();

      Serial.println("Hand/Object detected!");
      Serial.println("Lid: OPEN");
    }
  }

  // ==========================================================
  // AUTOMATIC LID CLOSING
  // ==========================================================

  if (lidIsOpen &&
      millis() - lidOpenedAt >= LID_OPEN_TIME) {

    lidServo.write(LID_CLOSED);

    lidIsOpen = false;

    Serial.println("Lid: CLOSED");
  }

  // ==========================================================
  // SENSOR 2: WASTE LEVEL
  // ==========================================================

  float wasteDistance =
    readDistance(WASTE_TRIG_PIN, WASTE_ECHO_PIN);

  if (wasteDistance < 0) {

    Serial.println("Waste sensor: No valid reading");

    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

  } else {

    float fillPercentage =
      calculateFillPercentage(wasteDistance);

    String binStatus =
      getBinStatus(fillPercentage, wasteDistance);

    Serial.print("Waste Distance: ");
    Serial.print(wasteDistance);
    Serial.println(" cm");

    Serial.print("Fill Percentage: ");
    Serial.print(fillPercentage);
    Serial.println("%");

    Serial.print("Bin Status: ");
    Serial.println(binStatus);

    // Local LED + buzzer alert
    updateAlerts(wasteDistance);
  }

  delay(200);
}