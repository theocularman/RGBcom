/*
   File: Token.cpp

   Author: The Ocular Man  (⌐0_0)
   Date:   9/6/2019

*/

#include "Arduino.h"
#include "Token.h"

Token::Token() {
  reset();
}

void Token::reset(void) {
  _palette_size = 3;
  _palette[0] = Color(255, 0, 0); //red
  _palette[1] = Color(0, 255, 0); //green
  _palette[2] = Color(0, 0, 255); //blue
  _mode = 0;
  _mode_h = _mode;
  _delay = 500;
  _smooth = 20;
  _intensity = 90; //Default is 90%
}

/*  Callback junk  */
void Token::setMode(uint8_t mode) {
  _mode_h = _mode; //mode history
  _mode = mode;
}

uint8_t Token::getMode(void) {
  return _mode;
}

uint8_t Token::getModeH(void) {
  return _mode_h;
}

int Token::getDelay(void) {
  return _delay;
}

void Token::setDelay(int delay_speed) {
  _delay = delay_speed;
}

void Token::setSmooth(int smooth) {
  _smooth = smooth;
}

void Token::setIntensity(int intensity) {
  _intensity = intensity;
}

void Token::setNew(uint8_t n) {
  _palette_size = n;
}

int Token::setColor(unsigned long _color) {

  if ((_color > 0xFFFFFF) || _color < 0)
    return 1;
  if (_palette_size >= PALETTE_SIZE)
    return 2;

  int b = _color & 0xFF;          //Mask for blue value
  int g = (_color >> 8) & 0xFF;   //Mask for green value
  int r = (_color >> 16) & 0xFF;  //Mask for red value

  _palette[_palette_size] = Color(r, g, b);
  _palette_size++;

  return 0;
}
