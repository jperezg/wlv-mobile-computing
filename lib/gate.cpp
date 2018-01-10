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
  for(int i = _position; i <= GATE_OPEN_ANGLE; i += GATE_DIFF) {
    _servoGate.write(i);
    delay(200);
  }
}

void Gate::close() {
  for(int i = _position; i <= GATE_CLOSE_ANGLE; i += GATE_DIFF) {
    _servoGate.write(i);
    delay(200);
  }
}
