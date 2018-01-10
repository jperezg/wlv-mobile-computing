#include "analog_light.h"

AnalogLight::AnalogLight() {
}

void AnalogLight::setup(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

void AnalogLight::setValue(int value) {
  analogWrite(_pin, value);
}
