// ============================================================
// Smart Dustbin - Sensor Module
// ============================================================
// Purpose:
// Reads distance from the HC-SR04 ultrasonic sensor.
//
// Hardware:
// ESP32 + HC-SR04
//
// Pins:
// TRIG -> GPIO 5
// ECHO -> GPIO 18
// ============================================================

#define TRIG_PIN 5
#define ECHO_PIN 18

// Reads distance from HC-SR04 in centimeters.
// Returns -1 when no valid echo is received.
float getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  float distance = duration * 0.0343 / 2;

  return distance;
}

// Initializes ultrasonic sensor pins.
void setupSensorModule() {

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);
}