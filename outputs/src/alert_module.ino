// ============================================================
// Smart Dustbin - Alert Module
// ============================================================
// Purpose:
// Controls LED and buzzer when the dustbin reaches the
// full-bin threshold.
//
// LED    -> GPIO 23
// Buzzer -> GPIO 25
// ============================================================

#define LED_PIN 23
#define BUZZER_PIN 25


// ------------------------------------------------------------
// Initialize alert devices
// ------------------------------------------------------------
void setupAlertModule() {

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Start with alerts OFF
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}


// ------------------------------------------------------------
// Turn ON full-bin alert
// ------------------------------------------------------------
void activateFullBinAlert() {

  digitalWrite(LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);

  Serial.println("LED: ON");
  Serial.println("Buzzer: ON");
}


// ------------------------------------------------------------
// Turn OFF full-bin alert
// ------------------------------------------------------------
void deactivateFullBinAlert() {

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("LED: OFF");
  Serial.println("Buzzer: OFF");
}