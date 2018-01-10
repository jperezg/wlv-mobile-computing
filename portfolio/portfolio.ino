#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define LED_CONTRAST_PIN 6
#define CONTRAST 100
#define XBEE_RX_PIN 8
#define XBEE_TX_PIN 9
#define BUTTON_UP_PIN 7
#define BUTTON_OK_PIN 10
#define BUTTON_DOWN_PIN 13

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial zigBee(XBEE_RX_PIN, XBEE_TX_PIN);

void setup() {

  analogWrite(LED_CONTRAST_PIN, CONTRAST);

  lcd.begin(16, 2);
  lcd.autoscroll();

  Serial.begin(9600);
  zigBee.begin(9600);

  pinMode(BUTTON_UP_PIN, INPUT);
  pinMode(BUTTON_OK_PIN, INPUT);
  pinMode(BUTTON_DOWN_PIN, INPUT);

  showMenu();
}

void loop() {
  checkButtons();

  // if (zigBee.available()) {
  //   printInLCD(zigBee.readString(), 0);
  // }
}

void showMenu() {
  printInLCD("1. Option 1", 0);
  printInLCD("2. Option 2", 1);
}

void printInLCD(String s, int row) {
  lcd.setCursor(0, row);
  lcd.print(s);
}

void checkButtons() {
  if (digitalRead(BUTTON_UP_PIN) == HIGH) {
    Serial.println("digitalRead(BUTTON_UP_PIN) == HIGH");
    // lcd.clear();
    // printInLCD("UP", 1);
    zigBee.println("interior_light:on");
    delay(100);
  } else if (digitalRead(BUTTON_OK_PIN) == HIGH) {
    Serial.println("digitalRead(BUTTON_OK_PIN) == HIGH");
    // lcd.clear();
    // printInLCD("OK", 1);
  } else if (digitalRead(BUTTON_DOWN_PIN) == HIGH) {
    Serial.println("digitalRead(BUTTON_DOWN_PIN) == HIGH");
    // lcd.clear();
    // printInLCD("DOWN", 1);

    zigBee.println("interior_light:off");
    delay(100);
  }
}
