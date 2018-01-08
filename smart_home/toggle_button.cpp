// #include "Arduino.h"
#include "toggle_button.h"

ToggleButton::ToggleButton() {
}

void ToggleButton::setup(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
  _isPressed = false;
}

bool ToggleButton::getState() {
  bool isPressed = digitalRead(_pin) == HIGH;
  if (isPressed) {
    _isPressed = !_isPressed;
  }
  return _isPressed;
}
