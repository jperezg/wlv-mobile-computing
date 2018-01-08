#include "analog_light.h"
#include "alarm.h"
#include "toggle_button.h"
#include "button.h"
#include "fire_detector.h"
#include <SoftwareSerial.h>
#include <Servo.h>

#define INTERIOR_LIGHT_LED1 8
#define INTERIOR_LIGHT_BUTTON 7
#define INTERIOR_LIGHT_LED2 9
#define INTERIOR_LIGHT_POT 2
#define EXTERIOR_LIGHT_LED 5
#define ALARM_SPEAKER_PIN 6
#define ALARM_LED_PIN 12
#define ALARM_BUTTON_PIN 13
#define SERVO_PIN 4
#define PHOTORESISTOR_PIN A1
#define FIRE_DETECTOR_PIN A0

SimpleLight simpleLight;
SimpleLight outdoorsLight;
SimpleLight alarmLight;
AnalogLight analogLight;
ToggleButton simpleLightButton;
Button alarmButton;
Alarm alarm;
Servo servoGate;
FireDetector fireDetector;
SoftwareSerial zigBee(3, 2);

char barry;

void setup() {
  Serial.begin(9600);
  zigBee.begin(9600);

  // Device 3 - Indoors setup
  simpleLight.setup(INTERIOR_LIGHT_LED1);
  analogLight.setup(INTERIOR_LIGHT_LED2);

  // Device 2 - Outdoors setup
  outdoorsLight.setup(EXTERIOR_LIGHT_LED);
  simpleLightButton.setup(INTERIOR_LIGHT_BUTTON);
  servoGate.attach(SERVO_PIN);

  // Device 4 - Alarm setup
  alarmLight.setup(ALARM_LED_PIN);
  alarm.setup(ALARM_SPEAKER_PIN, alarmLight);
  fireDetector.setup(FIRE_DETECTOR_PIN);
  alarmButton.setup(ALARM_BUTTON_PIN);

  // Serial.begin(115200);
  // Serial.println();
  //
  // WiFi.begin("StudentCOM", "");
  //
  // Serial.print("Connecting");
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println();
  //
  // Serial.print("Connected, IP address: ");
  // Serial.println(WiFi.localIP());
}

void loop() {
  checkOutdoorsLight();
  checkAlarm();

  // // Make servo go to 90 degrees
  // servoGate.write(90);
  // delay(1000);
  // // Make servo go to 180 degrees
  // servoGate.write(180);
  // delay(1000);
  //
  //
  // if (zigBee.available()) {
  //   // Serial.println("Waiting");
  //   barry = zigBee.read();
  //   Serial.print(barry);
  //   delay(2000);
  //   zigBee.print("Klk");
  // }

  if (simpleLightButton.getState()) {
    simpleLight.turnOn();
  } else {
    simpleLight.turnOff();
  }

  // int lightValue = (255 * analogRead(INTERIOR_LIGHT_POT))/1023;
  // analogLight.setValue(lightValue);
  // Serial.println(lightValue);


  // alarm.turnOnBuzzer();

  // for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
  //   // sets the value (range from 0 to 255):
  //   analogLight.setValue(fadeValue);
  //   // wait for 30 milliseconds to see the dimming effect
  //   delay(30);
  // }
  //
  // // fade out from max to min in increments of 5 points:
  // for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
  //   // sets the value (range from 0 to 255):
  //   analogLight.setValue(fadeValue);
  //   // wait for 30 milliseconds to see the dimming effect
  //   delay(30);
  // }
}

void checkOutdoorsLight() {
  analogRead(PHOTORESISTOR_PIN) <= 100 ? outdoorsLight.turnOn() : outdoorsLight.turnOff();
}

void checkAlarm() {
  alarm.check();

  if (alarmButton.isPressed()) {
    alarm.set(false);
  }

  if (fireDetector.check() != NO_FIRE) {
    alarm.set(true);
  }
}
