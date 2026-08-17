#define BLYNK_TEMPLATE_ID "TMPL3ReLJEQBg"
#define BLYNK_TEMPLATE_NAME "Smart Dustbin"
#define BLYNK_AUTH_TOKEN ""
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>


// =====================================================
// WIFI
// =====================================================

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// =====================================================
// PIN CONFIGURATION
// =====================================================

// Hand/Object Detection Sensor
#define HAND_TRIG_PIN 5
#define HAND_ECHO_PIN 18

// Waste Level Sensor
#define WASTE_TRIG_PIN 12
#define WASTE_ECHO_PIN 14

// Servo
#define SERVO_PIN 19

// Indicators
#define GREEN_LED_PIN 23
#define BUZZER_PIN 25
#define RED_LED_PIN 26

// =====================================================
// SYSTEM SETTINGS
// =====================================================

const float HAND_DETECTION_DISTANCE = 20.0;
const float FULL_BIN_THRESHOLD = 10.0;
const float BIN_HEIGHT = 20.0;

// Lid angles
const int LID_CLOSED_ANGLE = 0;
const int LID_OPEN_ANGLE = 90;

// Lid stays open for 2 seconds
const unsigned long LID_OPEN_TIME = 2000;

// =====================================================
// OBJECTS
// =====================================================

Servo lidServo;
BlynkTimer timer;

// =====================================================
// VARIABLES
// =====================================================

float handDistance = 0.0;
float wasteDistance = 0.0;
float fillPercentage = 0.0;

bool lidOpen = false;
bool binFull = false;

unsigned long lidOpenedTime = 0;

// Notification state
bool previousFullState = false;

// =====================================================
// READ ULTRASONIC DISTANCE
// =====================================================

float readDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0)
  {
    return 999.0;
  }

  float distance = duration * 0.0343 / 2.0;

  return distance;
}

// =====================================================
// CALCULATE FILL PERCENTAGE
// =====================================================

float calculateFillPercentage(float distance)
{
  float percentage =
      ((BIN_HEIGHT - distance) / BIN_HEIGHT) * 100.0;

  if (percentage < 0)
  {
    percentage = 0;
  }

  if (percentage > 100)
  {
    percentage = 100;
  }

  return percentage;
}

// =====================================================
// OPEN LID
// =====================================================

void openLid()
{
  if (!lidOpen)
  {
    lidServo.write(LID_OPEN_ANGLE);

    lidOpen = true;

    lidOpenedTime = millis();

    Serial.println("Lid: OPEN");
  }
}

// =====================================================
// CLOSE LID
// =====================================================

void closeLid()
{
  if (lidOpen)
  {
    lidServo.write(LID_CLOSED_ANGLE);

    lidOpen = false;

    Serial.println("Lid: CLOSED");
  }
}

// =====================================================
// AUTOMATIC LID TIMER
// =====================================================

void handleLidTimer()
{
  if (lidOpen)
  {
    if (millis() - lidOpenedTime >= LID_OPEN_TIME)
    {
      closeLid();
    }
  }
}

// =====================================================
// UPDATE BLYNK
// =====================================================

void updateBlynk()
{
  // V0 = Waste Distance
  Blynk.virtualWrite(V0, wasteDistance);

  // V1 = Bin Status
  if (binFull)
  {
    Blynk.virtualWrite(V1, "BIN FULL");
  }
  else
  {
    Blynk.virtualWrite(V1, "NORMAL");
  }

  // V2 = Lid Status
  if (lidOpen)
  {
    Blynk.virtualWrite(V2, "OPEN");
  }
  else
  {
    Blynk.virtualWrite(V2, "CLOSED");
  }

  // V3 = Bin Full Indicator
  Blynk.virtualWrite(V3, binFull ? 1 : 0);
}

// =====================================================
// PROCESS DUSTBIN
// =====================================================

void processDustbin()
{
  // ---------------------------------------------------
  // Read Sensors
  // ---------------------------------------------------

  handDistance = readDistance(
      HAND_TRIG_PIN,
      HAND_ECHO_PIN);

  wasteDistance = readDistance(
      WASTE_TRIG_PIN,
      WASTE_ECHO_PIN);

  // ---------------------------------------------------
  // Calculate Fill Percentage
  // ---------------------------------------------------

  fillPercentage =
      calculateFillPercentage(wasteDistance);

  // ---------------------------------------------------
  // Detect Full Bin
  // ---------------------------------------------------

  if (wasteDistance <= FULL_BIN_THRESHOLD)
  {
    binFull = true;
  }
  else
  {
    binFull = false;
  }

  // ---------------------------------------------------
  // Hand/Object Detection
  // ---------------------------------------------------

  Serial.print("Hand Distance: ");
  Serial.print(handDistance);
  Serial.println(" cm");

  /*
   * If bin is FULL, keep the lid closed.
   * Otherwise detect hand/object.
   */

  if (!binFull)
  {
    if (handDistance <= HAND_DETECTION_DISTANCE)
    {
      Serial.println("Hand/Object detected!");

      openLid();
    }
  }
  else
  {
    closeLid();
  }

  // ---------------------------------------------------
  // Lid Timer
  // ---------------------------------------------------

  handleLidTimer();

  // ---------------------------------------------------
  // LED + BUZZER
  // ---------------------------------------------------

  if (binFull)
  {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);

    // Send notification only once
    if (!previousFullState)
    {
      Blynk.logEvent(
          "bin_full",
          "Smart Dustbin is FULL! Please empty the dustbin.");

      previousFullState = true;

      Serial.println("=================================");
      Serial.println("!!! BIN FULL !!!");
      Serial.println("Red LED: ON");
      Serial.println("Buzzer: ON");
      Serial.println("Blynk Notification Sent");
      Serial.println("=================================");
    }
  }
  else
  {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);

    previousFullState = false;
  }

  // ---------------------------------------------------
  // Serial Monitor
  // ---------------------------------------------------

  Serial.print("Waste Distance: ");
  Serial.print(wasteDistance);
  Serial.println(" cm");

  Serial.print("Fill Percentage: ");
  Serial.print(fillPercentage);
  Serial.println("%");

  Serial.print("Bin Status: ");

  if (binFull)
  {
    Serial.println("BIN FULL");
  }
  else
  {
    Serial.println("NORMAL");
  }

  Serial.print("Lid Status: ");

  if (lidOpen)
  {
    Serial.println("OPEN");
  }
  else
  {
    Serial.println("CLOSED");
  }

  Serial.println("---------------------------------");
}

// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(115200);

  // ---------------------------------------------------
  // Pin Modes
  // ---------------------------------------------------

  pinMode(HAND_TRIG_PIN, OUTPUT);
  pinMode(HAND_ECHO_PIN, INPUT);

  pinMode(WASTE_TRIG_PIN, OUTPUT);
  pinMode(WASTE_ECHO_PIN, INPUT);

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // ---------------------------------------------------
  // Initial State
  // ---------------------------------------------------

  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // ---------------------------------------------------
  // Servo
  // ---------------------------------------------------

  lidServo.setPeriodHertz(50);

  lidServo.attach(
      SERVO_PIN,
      500,
      2400);

  lidServo.write(LID_CLOSED_ANGLE);

  lidOpen = false;

  // ---------------------------------------------------
  // Startup Information
  // ---------------------------------------------------

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

  Serial.print("Hand detection: <= ");
  Serial.print(HAND_DETECTION_DISTANCE);
  Serial.println(" cm");

  Serial.print("Full-bin threshold: <= ");
  Serial.print(FULL_BIN_THRESHOLD);
  Serial.println(" cm");

  Serial.print("Bin height: ");
  Serial.print(BIN_HEIGHT);
  Serial.println(" cm");

  Serial.print("Lid open duration: ");
  Serial.print(LID_OPEN_TIME / 1000);
  Serial.println(" seconds");

  Serial.println("---------------------------------");

  // ---------------------------------------------------
  // Blynk
  // ---------------------------------------------------

  Serial.println("Connecting to Blynk...");

Blynk.begin(
    BLYNK_AUTH_TOKEN,
    ssid,
    pass
);

  Serial.println("Blynk connection initialized");

  // ---------------------------------------------------
  // Blynk Timer
  // ---------------------------------------------------

  timer.setInterval(
      1000L,
      updateBlynk);

  Serial.println("System Ready");
  Serial.println("---------------------------------");
}

// =====================================================
// LOOP
// =====================================================

void loop()
{
  Blynk.run();

  timer.run();

  processDustbin();

  delay(500);
}