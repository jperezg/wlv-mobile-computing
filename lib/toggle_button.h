/*
  ToggleButton.h - Library for handling the house's simple light
*/

#include "Arduino.h"

class ToggleButton {
  public:
    ToggleButton();
    void setup(int pin);
    void toggle();
    bool getState();
  private:
    int _pin;
    bool _isPressed;
};
