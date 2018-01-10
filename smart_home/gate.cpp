#include "gate.h"

Gate::Gate() {
}

void Gate::setup(int pin) {
  _pin = pin;
  _servoGate.attach(_pin);
  _servoGate.write(90);
}

void Gate::open() {
  _servoGate.write(90);
}

void Gate::close() {
  _servoGate.write(180);
}
