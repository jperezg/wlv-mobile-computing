// #include "Arduino.h"
#include "simple_light.h"

SimpleLight::SimpleLight() {
}

void SimpleLight::setup(int pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void SimpleLight::turnOn() {
  digitalWrite(_pin, HIGH);
}

void SimpleLight::turnOff() {
  digitalWrite(_pin, LOW);
}
