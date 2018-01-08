/*
  FireDetector.h - Library for handling the house's analog light
*/

#include "Arduino.h"

#define CLOSE_FIRE 0
#define DISTANT_FIRE 1
#define NO_FIRE 2

class FireDetector {
  public:
    FireDetector();
    void setup(int pin);
    int check();
  private:
    int _pin;
};
