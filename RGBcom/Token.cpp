/*
   File: Token.cpp

   Author: The Ocular Man  (⌐0_0)
   Date:   9/6/2019

*/

#include "Arduino.h"
#include "EEPROM.h"
#include "Token.h"

Token::Token() {
  eeAddress = 0; //address zero
  EEPROM.get(eeAddress, persistence);
  if (persistence._new != 0xA) { //first run
    reset();
    SavePer(); //burn EEPROM
    return;
  }
  LoadPer();
  return;
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

void Token::LoadPer(void) {
  _palette_size = persistence._pal_size;
  _mode = persistence._mode;
  _intensity = persistence._int;
  _delay = persistence._delay;
  _smooth = persistence._smot;

  for (int i = 0; i < _palette_size; i++) {
    uint8_t r, g, b;
    HEXtoRGB(r, g, b,  persistence._pal[i]);
    Color temp = Color(r, g, b);
    _palette[i] = temp;
  }
  _mode_h = _mode; //I forgot what this was for...
}

void Token::SavePer(void) {
  persistence._new = 0xA; //enough?
  persistence._pal_size = _palette_size;
  persistence._mode = _mode;
  persistence._int = _intensity;
  persistence._delay = _delay;
  persistence._smot = _smooth;

  for (int i = 0; i < _palette_size; i++) {
    Color _p = _palette[i];
    persistence._pal[i] = RGBtoHEX(_p.getR(), _p.getG(), _p.getB());
  }
  EEPROM.put(eeAddress, persistence);
}

void Token::HEXtoRGB(uint8_t &r, uint8_t &g, uint8_t &b, unsigned long _color) {
  b = _color & 0xFF;          //Mask for blue value
  g = (_color >> 8) & 0xFF;   //Mask for green value
  r = (_color >> 16) & 0xFF;  //Mask for red value
}

unsigned long Token::RGBtoHEX(uint8_t r, uint8_t g, uint8_t b) {
  unsigned long _hex = 0;
  _hex |= (unsigned long)r << 16;
  _hex |= (unsigned long)g << 8;
  _hex |= b;
  return _hex;
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

void Token::setIntensity(uint8_t intensity) {
  _intensity = intensity;
}

void Token::setNew(uint8_t n) {
  _palette_size = n;
}

uint8_t Token::setColor(unsigned long _color) {

  if ((_color > 0xFFFFFF) || _color < 0)
    return 1;
  if (_palette_size >= PALETTE_SIZE)
    return 2;
    
  uint8_t r, g, b;
  HEXtoRGB(r, g, b, _color);

  _palette[_palette_size] = Color(r, g, b);
  _palette_size++;

  return 0;
}

uint8_t Token::getPsize(void) {
  return _palette_size;
}

Color Token::getColorAt(uint8_t n) {
  return _palette[n];
}
