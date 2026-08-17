#define BLYNK_TEMPLATE_ID "TMPL3ReLJEQBg"
#define BLYNK_TEMPLATE_NAME "Smart Dustbin"
#define BLYNK_AUTH_TOKEN "fgxQp6IZfHVV2noZDSjg3eanF4j6ScR2"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Blynk credentials
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// Blynk Virtual Pins
#define VPIN_DISTANCE   V0
#define VPIN_BIN_STATUS V1
#define VPIN_LID_STATUS V2
#define VPIN_BIN_FULL   V3

// Hand/object detection threshold
const float HAND_DISTANCE = 20.0;

BlynkTimer timer;


// ============================================================
// Send Smart Dustbin data to Blynk
// ============================================================

void sendDataToBlynk() {

  float distance = getDistance();

  if (distance < 0) {
    Serial.println("Blynk: No valid ultrasonic reading");
    return;
  }

  // V0 - Distance
  Blynk.virtualWrite(VPIN_DISTANCE, distance);


  // V1 + V3 - Bin status
  bool fullStatus = checkBinFull(distance);

  if (fullStatus) {

    Blynk.virtualWrite(VPIN_BIN_STATUS, "BIN FULL");
    Blynk.virtualWrite(VPIN_BIN_FULL, 1);

  } else {

    Blynk.virtualWrite(VPIN_BIN_STATUS, "NORMAL");
    Blynk.virtualWrite(VPIN_BIN_FULL, 0);
  }


  // V2 - Lid status
  if (lidIsOpen) {
    Blynk.virtualWrite(VPIN_LID_STATUS, "OPEN");
  } else {
    Blynk.virtualWrite(VPIN_LID_STATUS, "CLOSED");
  }
}


// ============================================================
// SETUP
// ============================================================

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println("=================================");
  Serial.println(" Smart Dustbin - Blynk System");
  Serial.println("=================================");


  // Initialize modules
  setupSensorModule();
  setupLidControl();
  setupAlertModule();


  // Connect to Blynk
  Serial.println("Connecting to Blynk...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Blynk connection initialized");


  Serial.println("System Ready");
  Serial.println("Hand detection: <= 20 cm");
  Serial.println("Bin full alert: <= 10 cm");
  Serial.println("Lid open duration: 2 seconds");
  Serial.println();


  // Send data to Blynk every 1 second
  timer.setInterval(1000L, sendDataToBlynk);
}


// ============================================================
// LOOP
// ============================================================

void loop() {

  Blynk.run();
  timer.run();


  // Read ultrasonic distance
  float distance = getDistance();


  // Invalid reading
  if (distance < 0) {

    Serial.println("Ultrasonic sensor: No valid reading");

    deactivateFullBinAlert();

    delay(200);

    return;
  }


  // Display distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // ==========================================================
  // BIN LEVEL DETECTION
  // ==========================================================

  updateBinLevel(distance);


  if (binIsFull) {

    activateFullBinAlert();

  } else {

    deactivateFullBinAlert();
  }


  // ==========================================================
  // HAND / OBJECT DETECTION
  // ==========================================================

  if (distance > FULL_DISTANCE &&
      distance <= HAND_DISTANCE) {

    openLid();
  }


  // ==========================================================
  // AUTOMATIC LID CLOSING
  // ==========================================================

  updateLidControl();


  delay(200);
}