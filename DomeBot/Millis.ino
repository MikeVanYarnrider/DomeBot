void tenSecUpdate(int testMillis, int tftMillis, int tenSeconds) {
  // EVERY 10 SECONDS
  if (testMillis - tftMillis >= tenSeconds) {
    // save the last time you blinked the LED
    tftMillis = testMillis;
    updateTempTft();
    updateHumTft();
  }
}


void fiveSecUpdate(int currentMillis, int previousMillis, int fiveSeconds) {
  // EVERY 5 SECONDS
  if (currentMillis - previousMillis >= fiveSeconds) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    getTempHum();
    handleWindow();
  }
}
