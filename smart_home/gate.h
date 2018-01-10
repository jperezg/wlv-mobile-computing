/*
  Gate.h - Library for handling the house's analog light
*/

#include "Arduino.h"
#include <Servo.h>

class Gate {
  public:
    Gate();
    void setup(int pin);
    void open();
    void close();
  private:
    int _pin;
    Servo _servoGate;
};
