/*
  SimpleLight.h - Library for handling the house's simple light
*/

#include "Arduino.h"

class SimpleLight {
  public:
    SimpleLight();
    void setup(int pin);
    void turnOn();
    void turnOff();
  private:
    int _pin;
};
