#include "fire_detector.h"

const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

FireDetector::FireDetector() {
}

void FireDetector::setup(int pin) {
  _pin = pin;
}

int FireDetector::check() {
	int sensorReading = analogRead(_pin);
	int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  delay(1);
  return range;
}
