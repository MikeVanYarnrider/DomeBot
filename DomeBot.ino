#include <Wire.h>
#include <dht.h>

// TOUCH DISPLAY
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 200
#define MAXPRESSURE 1000

// STEPPER
#include <Unistep2.h>


// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP = 8, XM = A2, YP = A3, YM = 9; //240x320 ID=0x9341
const int TS_LEFT = 102, TS_RT = 916, TS_TOP = 76, TS_BOT = 896;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn, test_btn;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
// ******************************************************************************

// DEFINITION FUR STEPPER MOTOR
const int outPorts[] = {53, 51, 49, 47};
Unistep2 stepperX(53, 51, 49, 47, 4096, 1000);


// ******************************************************************************

// GLOBAL VARIABLES
int temp = 0;
int hum = 0;
int windowOpenTemp = 22;
// ******************************************************************************


// RELAY PINS
const int RELAY_PIN  = 52; // Arduino pin connected to relay's pin
int RELAY_PIN_STATE = 1;

// ******************************************************************************

// TEMP SENSOR
dht DHT; // create dht object
#define DHT11_PIN 26 // the number of the DHT11 sensor pin
// ******************************************************************************


// TOUCH MENU
byte menuPage = 1

// ******************************************************************************

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long tftMillis = 0;        // will store last time LED was updated


// constants won't change:
const long fiveSeconds = 5000;           // interval at which to blink (milliseconds)
const long tenSeconds = 10000;           // interval at which to blink (milliseconds)



void setup() {

  Serial.begin(9600);                // initialize serial


  /*
    Defines Stepper Motor Output pins
  */
  for (int i = 0; i < 4; i++) {
    pinMode(outPorts[i], OUTPUT);
  }

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_PIN_STATE);

  /*
      Touch Setup
  */
  uint16_t ID = tft.readID();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  Serial.println("Calibrate for your Touch Panel");
  if (ID == 0xD3D3) ID = 0x9486; // write-only shield
  tft.begin(ID);
  tft.setRotation(0);            //PORTRAIT
  tft.fillScreen(BLACK);
  on_btn.initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
  off_btn.initButton(&tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);
  test_btn.initButton(&tft, 180, 260, 100, 40, WHITE, YELLOW, BLACK, "TEST", 2);

  on_btn.drawButton(false);
  off_btn.drawButton(false);
  test_btn.drawButton(false);


  tft.drawLine(0, 50, 240, 50, WHITE);
  tft.drawLine(0, 1, 240, 1, WHITE);
  tft.drawLine(120, 0, 120, 50, WHITE);

  tft.setCursor(10, 10);

  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("TEMP");
  tft.setCursor(10, 25);

  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("C");

  tft.setCursor(130, 10);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("HUM");
  tft.setCursor(130, 27);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("%");

  tft.fillRect(40, 80, 160, 80, RED);
}


void loop() {

  /*
    MILLIS INSTEAD OF DELAY TO MAKE BUTTONS WORK WHILE DHT11 gets Data
    Takes Milliseconds and executes every X milliseconds instead of a fixed delay
  */
  unsigned long currentMillis = millis();
  unsigned long testMillis = millis();


  stepperX.run();


  // EVERY 10 SECONDS
  if (testMillis - tftMillis >= tenSeconds) {
    // save the last time you blinked the LED
    tftMillis = testMillis;
    updateTempTft();
    updateHumTft();
  }

  // EVERY 5 SECONDS
  if (currentMillis - previousMillis >= fiveSeconds) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    getTempHum();
    handleWindow();
  }

  //  moveSteps(true, 32 * 64, 2);


  /*
    Touch MENU
  */

  
  bool down = Touch_getXY();
  on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
  off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
  if (on_btn.justReleased())
    on_btn.drawButton();
  if (off_btn.justReleased())
    off_btn.drawButton();
  if (on_btn.justPressed()) {
    on_btn.drawButton(true);
    tft.fillRect(40, 80, 160, 80, GREEN);
    stepperX.move(4096);
  }
  if (off_btn.justPressed()) {
    off_btn.drawButton(true);
    tft.fillRect(40, 80, 160, 80, RED);
    stepperX.stop();

  }
}

int getTempHum() {
  // read DHT11 and judge the state according to the return value

  // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error,\t");
      break;
    default:
      Serial.print("Unknown error,\t");
      break;
  }

  // DISPLAY DATA
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1);

  temp =  DHT.temperature;
  hum =  DHT.humidity;

}

void startWaterpump() {

}
