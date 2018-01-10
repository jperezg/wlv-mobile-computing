/*
  Gate.h - Library for handling the house's analog light
*/

#include "Arduino.h"
#include <Servo.h>

#define GATE_OPEN_ANGLE 60
#define GATE_CLOSE_ANGLE 60
#define GATE_DIFF 10

class Gate {
  public:
    Gate();
    void setup(int pin);
    void open();
    void close();
  private:
    int _pin;
    int _position;
    Servo _servoGate;
};
