// ============================================================
// Smart Dustbin - Lid Control Module
// ============================================================
// Purpose:
// Controls the servo motor for automatic dustbin lid operation.
//
// Hardware:
// ESP32 + SG90 Servo Motor
//
// Servo Pin:
// GPIO 19
//
// Behavior:
// Object detected -> Lid OPEN
// After 2 seconds -> Lid CLOSED
// ============================================================

#include <ESP32Servo.h>

#define SERVO_PIN 19

const int LID_CLOSED = 0;
const int LID_OPEN = 90;

const unsigned long LID_OPEN_TIME = 2000;

Servo lidServo;

bool lidIsOpen = false;
unsigned long lidOpenedAt = 0;


// ------------------------------------------------------------
// Initialize Servo
// ------------------------------------------------------------
void setupLidControl() {

  lidServo.attach(SERVO_PIN);

  // Start with lid closed
  lidServo.write(LID_CLOSED);

  lidIsOpen = false;
}


// ------------------------------------------------------------
// Open the dustbin lid
// ------------------------------------------------------------
void openLid() {

  if (!lidIsOpen) {

    lidServo.write(LID_OPEN);

    lidIsOpen = true;
    lidOpenedAt = millis();

    Serial.println("Lid: OPEN");
  }
}


// ------------------------------------------------------------
// Close the dustbin lid
// ------------------------------------------------------------
void closeLid() {

  if (lidIsOpen) {

    lidServo.write(LID_CLOSED);

    lidIsOpen = false;

    Serial.println("Lid: CLOSED");
  }
}


// ------------------------------------------------------------
// Automatically close lid after configured delay
// ------------------------------------------------------------
void updateLidControl() {

  if (lidIsOpen &&
      millis() - lidOpenedAt >= LID_OPEN_TIME) {

    closeLid();
  }
}