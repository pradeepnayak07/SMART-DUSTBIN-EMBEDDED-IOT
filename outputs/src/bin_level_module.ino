// ============================================================
// Smart Dustbin - Bin Level Module
// ============================================================
// Purpose:
// Determines whether the dustbin is full based on the
// ultrasonic distance reading.
//
// Full-bin threshold:
// <= 10 cm
//
// Note:
// The current project uses distance threshold detection.
// Fill-percentage calculation is kept as a future enhancement.
// ============================================================

const float FULL_DISTANCE = 10.0;

bool binIsFull = false;


// ------------------------------------------------------------
// Check whether the bin is full
// ------------------------------------------------------------
bool checkBinFull(float distance) {

  if (distance < 0) {
    return false;
  }

  return distance <= FULL_DISTANCE;
}


// ------------------------------------------------------------
// Update and report bin status
// ------------------------------------------------------------
void updateBinLevel(float distance) {

  bool currentStatus = checkBinFull(distance);

  if (currentStatus && !binIsFull) {

    Serial.println("!!! BIN FULL !!!");

    binIsFull = true;

  } else if (!currentStatus && binIsFull) {

    Serial.println("Bin status: NORMAL");

    binIsFull = false;
  }
}