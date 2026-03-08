#include "temperature_sensor.h"

bool TemperatureSensor::begin() {
  started = beginImpl();
  return started;
}

void TemperatureSensor::setOffsets(TemperatureData _offset) {
  this->offsetData = _offset;
}

bool TemperatureSensor::isStarted() const {
  return started;
}

TemperatureData TemperatureSensor::read() {
  if (!started) {
    return {};
  }
  return readImpl() + offsetData;
}
