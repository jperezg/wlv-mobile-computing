/*
  Button.h - Library for handling the house's simple light
*/

#include "Arduino.h"

class Button {
  public:
    Button();
    void setup(int pin);
    bool isPressed();
  private:
    int _pin;
};
