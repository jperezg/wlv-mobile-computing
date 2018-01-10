#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include "button.h";

#define LED_CONTRAST_PIN 6
#define CONTRAST 110
#define XBEE_RX_PIN 8
#define XBEE_TX_PIN 9
#define BUTTON_DIGITAL_PIN 7
#define BUTTON_DOOR_PIN 10
#define BUTTON_ALARM_PIN 13
#define POTENTIOMETER_PIN 2

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
int lastPotentiometerValue = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial zigBee(XBEE_RX_PIN, XBEE_TX_PIN);
Button alarmButton, doorButton, digitalLightButton, analogLightButton;

String screen[] = { "DO | IL | AN | AL", "   |   |   |    "};

int alarmState = 0;
int doorState = 0;
int digitalLightState = 0;
int analogLightState = 0;

void setup() {

  analogWrite(LED_CONTRAST_PIN, CONTRAST);

  lcd.begin(16, 2);

  Serial.begin(9600);
  zigBee.begin(9600);

  digitalLightButton.setup(BUTTON_DIGITAL_PIN);
  doorButton.setup(BUTTON_DOOR_PIN);
  alarmButton.setup(BUTTON_ALARM_PIN);

  showDisplay(0);
  showStates();
}

void loop() {
  handleControls();
  checkCommands();
}

void showDisplay(int row) {
  lcd.setCursor(0, row);
  lcd.print(screen[row]);
}

void showStates() {
  char buffer[20];
  sprintf(buffer, "%d  |%d  |%d  |%d   ", doorState, digitalLightState, analogLightState, alarmState);
  screen[1] = (String) buffer;
  Serial.println(screen[1]);
  showDisplay(1);
}

void printInLCD(String s, int row) {
  lcd.setCursor(0, row);
  lcd.print(s);
}

void handleControls() {
  if (digitalLightButton.isPressed()) {
    if (digitalLightState) {
      zigBee.println("interior_light:off");
    } else {
      zigBee.println("interior_light:on");
    }
  } else if (alarmButton.isPressed()) {
    if (alarmState) {
      zigBee.println("alarm:off");
    } else {
      // zigBee.println("alarm:on");
    }
  } else if (doorButton.isPressed()) {
    if (doorState) {
      zigBee.println("gate:close");
    } else {
      zigBee.println("gate:open");
    }
  }

  // int val = analogRead(POTENTIOMETER_PIN) - 34;
  // // int lightValue = (255 * val)/10;
  // if (lightValue != lastPotentiometerValue) {
  //   // zigBee.println("analog_light:" + lightValue);
  //
  //   lastPotentiometerValue = lightValue;
  // }
  delay(100);
}

void checkCommands() {
  bool hasChanged = false;
  if (zigBee.available()) {
    String rawString = zigBee.readStringUntil('\r');
    rawString.replace("\n", "");
    int pos = rawString.indexOf(":");

    if (pos == -1) {
      return 0;
    }

    String component = rawString.substring(0, pos);
    String action = rawString.substring(pos + 1);

    Serial.println(component);
    Serial.println(action);
    Serial.println("---");

    if (component == "interior_light") {
      digitalLightState = action == "on" ? 1 : 0;
      hasChanged = true;
    }

    if (component == "alarm") {
      alarmState = action == "on" ? 1 : 0;
      hasChanged = true;
    }

    if (component == "gate") {
      doorState = action == "open" ? 1 : 0;
      hasChanged = true;
    }

    delay(10);
  }

  if (hasChanged) {
    showStates();
  }
}
