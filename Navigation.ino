//int updateMainMenu() {
//  switch (mainMenu) {
//    case 0:
//      mainMenu = 1;
//      break;
//    case 1:
//      lcd.clear();
//      lcd.print(">Bewaesserung");
//      lcd.setCursor(0, 1);
//      lcd.print("Fenster");
//      break;
//    case 2:
//      lcd.clear();
//      lcd.print("Bewaesserung");
//      lcd.setCursor(0, 1);
//      lcd.print(">Fenster");
//      break;
//    case 3:
//      lcd.clear();
//      lcd.print(">TEMP & HMD");
//      lcd.setCursor(0, 1);
//      lcd.print("MenuItem4");
//      break;
//    case 4:
//      lcd.clear();
//      lcd.print("TEMP & HMD");
//      lcd.setCursor(0, 1);
//      lcd.print(">MenuItem4");
//      break;
//    case 5:
//      mainMenu = 4;
//      break;
//  }
//}
//
//
//
//void mainMenuNavigation() {
//  if (!digitalRead(downButton)) {
//    mainMenu++;
//    updateMainMenu();
//    delay(100);
//    while (!digitalRead(downButton));
//  }
//  if (!digitalRead(upButton)) {
//    mainMenu--;
//    updateMainMenu();
//    delay(100);
//    while (!digitalRead(upButton));
//  }
//  if (!digitalRead(selectButton)) {
//    executeAction();
//    updateMainMenu();
//    delay(100);
//    while (!digitalRead(selectButton));
//  }
//}
//
//void executeAction() {
//  switch (mainMenu) {
//    case 1:
//      action1();
//      break;
//    case 2:
//      action2();
//      break;
//    case 3:
//      displayTempHum();
//      break;
//    case 4:
//      action4();
//      break;
//  }
//}
//
//void action1() {
//  lcd.clear();
//  lcd.print(">Executing #1");
//  delay(1500);
//}
//void action2() {
//  lcd.clear();
//  lcd.print("Open");
//  lcd.setCursor(0, 1);
//  lcd.print("Close");
//  delay(1500);
//}
//void displayTempHum() {
//  lcd.clear();
//  lcd.print("TMP: ");
//  lcd.print("C ");
//  lcd.print(temp);
//
//  lcd.setCursor(0, 1); // set cursor to second line
//  lcd.print("HMD: ");
//  lcd.print("% ");
//  lcd.print(hum);
//  delay(5000);
//}
//void action4() {
//  lcd.clear();
//  lcd.print(">Executing #4");
//  delay(1500);
//}
