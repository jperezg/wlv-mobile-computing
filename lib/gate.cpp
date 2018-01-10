#include "gate.h"

Gate::Gate() {
}

void Gate::setup(int pin) {
  _pin = pin;
  _position = GATE_CLOSE_ANGLE;
  _servoGate.attach(_pin);
  _servoGate.write(_position);
}

void Gate::open() {
  _servoGate.write(GATE_OPEN_ANGLE);
}

void Gate::close() {
  _servoGate.write(GATE_CLOSE_ANGLE);
}
