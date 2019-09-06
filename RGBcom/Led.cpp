/*
   File: Led.cpp
   Adapted from https://github.com/leka/moti/tree/dev/lib/Led

*/

#include "Arduino.h"
#include "Led.h"

Led::Led() {
  _colorValue = Color(0, 0, 0);
}

Led::Led(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, bool acFlag) {
  _AC = acFlag;
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;

  _colorValue = Color(0, 0, 0);
}

Led::Led(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, Color colorValue, bool acFlag) {
  Led(redPin, greenPin, bluePin, acFlag);
  _colorValue = colorValue;
}

Color Led::dim(Color colorValue, uint8_t level) {
  return dim(colorValue.getR(), colorValue.getG(), colorValue.getB(), level);
}

Color Led::dim(uint8_t redValue, uint8_t greenValue, uint8_t blueValue, uint8_t level) {
  redValue *= (double) level * .01;
  greenValue *= (double) level * .01;
  blueValue *= (double) level * .01;
  return Color(redValue, greenValue, blueValue);
}

void Led::CATHODE(void) {
  analogWrite(_redPin, _colorValue.getR());
  analogWrite(_greenPin, _colorValue.getG());
  analogWrite(_bluePin, _colorValue.getB());
}

void Led::ANODE(void) {
  analogWrite(_redPin,   255 - _colorValue.getR());
  analogWrite(_greenPin, 255 -  _colorValue.getG());
  analogWrite(_bluePin,  255 - _colorValue.getB());
}

void Led::shine(void) {
  //If COMMON_ANODE
  if (_AC)
    ANODE();
  else
    CATHODE();
}

void Led::shine(Color colorValue) {
  setColor(colorValue);
  shine();
}

void Led::shine(Color colorValue, uint8_t level) {
  setColor(colorValue, level);
  shine();
}

void Led::shine(uint8_t redValue, uint8_t greeValue, uint8_t blueValue) {
  setColor(Color(redValue, greeValue, blueValue));
  shine();
}

void Led::shine(uint8_t redValue, uint8_t greeValue, uint8_t blueValue, uint8_t level) {
  setColor(dim(redValue, greeValue, blueValue, level));
  shine();
}

void Led::turnOff(void) {
  setColor(Color(0, 0, 0));
  shine();
}

Color Led::getColor(void) {
  return _colorValue;
}

void Led::setColor(Color colorValue) {
  _colorValue = colorValue;
}

void Led::setColor(Color colorValue, uint8_t level) {
  _colorValue = dim(colorValue, level);
}
