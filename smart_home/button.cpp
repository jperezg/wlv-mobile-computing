#include "button.h"

Button::Button() {
}

void Button::setup(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

bool Button::isPressed() {
  return digitalRead(_pin) == HIGH;
}
