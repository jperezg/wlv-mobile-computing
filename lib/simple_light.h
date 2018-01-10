/*
  SimpleLight.h - Library for handling the house's simple light
*/

#include "Arduino.h"

class SimpleLight {
  public:
    SimpleLight();
    void setup(int pin);
    void setAuto(bool value);
    void turnOn();
    void turnOff();
    bool isAuto();
    bool isOn();
  private:
    int _pin;
    bool _isAutomatic;
    bool _state;
};
