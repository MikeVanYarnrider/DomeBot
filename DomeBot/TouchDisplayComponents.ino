void updateTempTft() {
  tft.setTextSize(4);
  if (temp > 21) {
    tft.setTextColor(RED, BLACK);

  } else {
    tft.setTextColor(WHITE, BLACK);
  }
  tft.setCursor(60, 10);
  tft.print(temp);
}

void updateHumTft() {
  tft.setTextSize(4);
  tft.setTextColor(WHITE, BLACK);
  tft.setCursor(180, 10);
  tft.print(hum);
}
