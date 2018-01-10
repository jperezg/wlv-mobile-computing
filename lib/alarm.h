/*
  AnalogLight.h - Library for handling the house's analog light
*/

#include "Arduino.h"
#include "simple_light.h"

class Alarm {
  public:
    Alarm();
    void setup(int buzzerPin, SimpleLight light);
    void set(bool isActive);
    void check();
  private:
    bool _isActive;
    int _buzzerPin;
    SimpleLight _light;
};
