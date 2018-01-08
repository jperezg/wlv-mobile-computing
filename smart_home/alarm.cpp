// #include "Arduino.h"
#include "alarm.h"

Alarm::Alarm() {
}

void Alarm::setup(int buzzerPin, SimpleLight light) {
  _buzzerPin = buzzerPin;
  _light = light;
  pinMode(_buzzerPin, OUTPUT);
}

void Alarm::check() {
  if (_isActive) {
    analogWrite (_buzzerPin, 255);
    _light.turnOn();
    delay (500);
    analogWrite (_buzzerPin, 0);
    _light.turnOff();
    delay (100);
  } else {
    analogWrite (_buzzerPin, 0);
    _light.turnOff();
  }
}

void Alarm::set(bool isActive) {
  _isActive = isActive;
}
