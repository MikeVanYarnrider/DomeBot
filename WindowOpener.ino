/*
  Stepper Motor Setup
*/

void moveSteps(bool dir, int steps, byte ms) {
  for (int i = 0; i < steps; i++) {
    moveOneStep(dir); // Rotate a step 
    delay(ms); // Control the speed
  }
}
void moveOneStep(bool dir) {
  // Define a variable, use four low bit to indicate the state of port
  static byte out = 0x01;
  // Decide the shift direction according to the rotation direction
  if (dir) { // ring shift left
    out != 0x08 ? out = out << 1 : out = 0x01;
  }
  else { // ring shift right
    out != 0x01 ? out = out >> 1 : out = 0x08;
  }
  // Output singal to each port
  for (int i = 0; i < 4; i++) {
    digitalWrite(outPorts[i], (out & (0x01 << i)) ? HIGH : LOW);
  }
}

/*WINDOW HANDLER*/
void handleWindow() {
  if (temp > windowOpenTemp) {
    Serial.println(temp);
    RELAY_PIN_STATE = 0;
    digitalWrite(RELAY_PIN, RELAY_PIN_STATE);
    Serial.println(RELAY_PIN_STATE);
  } else {
    RELAY_PIN_STATE = 1;
    digitalWrite(RELAY_PIN, RELAY_PIN_STATE);
    Serial.println(RELAY_PIN_STATE);
  }
}
