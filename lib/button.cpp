#include "button.h"

Button::Button() {
}

void Button::setup(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
  _isPressed = false;
}

bool Button::isPressed() {
  int newState = digitalRead(_pin);
  if (newState != _lastState) {
    _isPressed = newState == HIGH;
    _lastState = newState;
    delay(50);
  }
  return _isPressed;
}
