#include "simple_light.h"

SimpleLight::SimpleLight() {
}

void SimpleLight::setup(int pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
  _isAutomatic = false;
  _state = false;
}

void SimpleLight::turnOn() {
  digitalWrite(_pin, HIGH);
  _state = true;
}

void SimpleLight::turnOff() {
  digitalWrite(_pin, LOW);
  _state = false;
}

void SimpleLight::setAuto(bool value) {
  _isAutomatic = value;
}

bool SimpleLight::isAuto() {
  return _isAutomatic;
}

bool SimpleLight::isOn() {
  return _state;
}
