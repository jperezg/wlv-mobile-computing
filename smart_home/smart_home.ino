#include <SoftwareSerial.h>
#include "analog_light.h"
#include "alarm.h"
#include "toggle_button.h"
#include "button.h"
#include "fire_detector.h"
#include "gate.h"

#define INTERIOR_LIGHT_LED1 8
#define INTERIOR_LIGHT_BUTTON 7
#define INTERIOR_LIGHT_ANALOG 11
#define INTERIOR_LIGHT_POT 2
#define EXTERIOR_LIGHT_LED 5
#define ALARM_SPEAKER_PIN 6
#define ALARM_LED_PIN 12
#define ALARM_BUTTON_PIN 13
#define SERVO_PIN 10
#define PHOTORESISTOR_PIN A1
#define FIRE_DETECTOR_PIN A0
#define XBEE_RX_PIN 2
#define XBEE_TX_PIN 3

SimpleLight simpleLight;
SimpleLight outdoorsLight;
SimpleLight alarmLight;
AnalogLight analogLight;
ToggleButton simpleLightButton;
Button alarmButton;
Alarm alarm;
Gate gate;
FireDetector fireDetector;
SoftwareSerial zigBee(XBEE_RX_PIN, XBEE_TX_PIN);

enum Command {
  CommandNone,
  CommandSimpleLight,
  CommandAnalogLight,
  CommandExteriorLight,
  CommandAlarm,
  CommandGate
};

void setup() {
  Serial.begin(9600);
  zigBee.begin(9600);

  // Device 2 - Outdoors setup
  outdoorsLight.setup(EXTERIOR_LIGHT_LED);
  outdoorsLight.setAuto(true);
  simpleLightButton.setup(INTERIOR_LIGHT_BUTTON);
  gate.setup(SERVO_PIN);

  // Device 3 - Indoors setup
  simpleLight.setup(INTERIOR_LIGHT_LED1);
  analogLight.setup(INTERIOR_LIGHT_ANALOG);

  // Device 4 - Alarm setup
  alarmLight.setup(ALARM_LED_PIN);
  alarm.setup(ALARM_SPEAKER_PIN, alarmLight);
  fireDetector.setup(FIRE_DETECTOR_PIN);
  alarmButton.setup(ALARM_BUTTON_PIN);
}

void loop() {
  checkOutdoorsLights();
  checkIndoorsLights();
  checkAlarm();
  handleCommands();
}

void checkOutdoorsLights() {
  if (outdoorsLight.isAuto()) {
    if (analogRead(PHOTORESISTOR_PIN) <= 100) {
      if (!outdoorsLight.isOn()) {
        outdoorsLight.turnOn();
        zigBee.println("exterior_light:on");
      }
    } else {
      if (outdoorsLight.isOn()) {
        outdoorsLight.turnOff();
        zigBee.println("exterior_light:off");
      }
    }
  }
}

void checkIndoorsLights() {
  // if (simpleLightButton.getState()) {
  //   simpleLight.turnOn();
  // } else {
  //   simpleLight.turnOff();
  // }

  // int lightValue = (255 * analogRead(INTERIOR_LIGHT_POT))/1023;
  // analogLight.setValue(lightValue);
  // Serial.println(lightValue);
}

void checkAlarm() {
  alarm.check();

  if (alarmButton.isPressed()) {
    alarm.set(false);
    zigBee.println("alarm:off");
  }

  if (fireDetector.check() != NO_FIRE) {
    alarm.set(true);
    zigBee.println("alarm:on");
  }
}

int handleCommands() {
  if (zigBee.available()) {
    String rawString = zigBee.readStringUntil('\r');
    rawString.replace("\n", "");

    int pos = rawString.indexOf(":");

    if (pos == -1) {
      return 0;
    }

    String component = rawString.substring(0, pos);
    String action = rawString.substring(pos + 1);

    Command command = getCommand(component);

    Serial.print(component + " : ");
    Serial.print(action);
    Serial.println("\n");

    if (command == CommandNone) {
      return 0;
    }

    switch (command) {
      case CommandSimpleLight:
        handleCommandSimpleLight(simpleLight, action);
        break;
      case CommandExteriorLight:
        if (action == "on") {
          outdoorsLight.setAuto(false);
        } else {
          outdoorsLight.setAuto(true);
        }
        handleCommandSimpleLight(outdoorsLight, action);
        break;
      case CommandAnalogLight:
        handleCommandAnalogLight(action);
        break;
      case CommandAlarm:
        handleCommandAlarm(action);
        break;
      case CommandGate:
        handleCommandGate(action);
        break;
    }

    zigBee.println(component + ":" + action);

    delay(10);
    return 1;
  }
}

Command getCommand(String str) {
  if (str == "interior_light") return CommandSimpleLight;
  if (str == "analog_light") return CommandAnalogLight;
  if (str == "exterior_light") return CommandExteriorLight;
  if (str == "alarm") return CommandAlarm;
  if (str == "gate") return CommandGate;
  return CommandNone;
}

void handleCommandSimpleLight(SimpleLight light, String action) {
  Serial.println("Light -> " + action + "\n");
  if (action == "on") {
    light.turnOn();
  } else {
    light.turnOff();
  }
}

void handleCommandAnalogLight(String action) {
  analogLight.setValue(action.toInt());
}

void handleCommandAlarm(String action) {
  if (action == "on") {
    alarm.set(true);
  } else {
    alarm.set(false);
  }
}

void handleCommandGate(String action) {
  Serial.print("Gate "+action+ "\n");
  if (action == "open") {
    gate.open();
  } else {
    gate.close();
  }
}
