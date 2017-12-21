#include <LiquidCrystal.h>

#define LED_CONTRAST_PIN 6
#define SPEAKER_PIN 7
#define IR_PIN 2

#define CONTRAST 120

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  pinMode(SPEAKER_PIN, OUTPUT);

  analogWrite(LED_CONTRAST_PIN, CONTRAST);

  lcd.begin(16, 2);
}

void loop() {
  // triggerAlarm();
}

void triggerAlarm() {
  printInLCD("ALARM!", 1);

  analogWrite (SPEAKER_PIN, 255);
  delay (500);
  analogWrite (SPEAKER_PIN, 0);
  delay (100);
}

void printInLCD(String s, int row) {
  lcd.setCursor(0, row);
  lcd.print(s);
}
