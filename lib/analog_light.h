/*
  AnalogLight.h - Library for handling the house's analog light
*/

#include "Arduino.h"

class AnalogLight {
  public:
    AnalogLight();
    void setup(int pin);
    void setValue(int value);
  private:
    int _pin;
};
