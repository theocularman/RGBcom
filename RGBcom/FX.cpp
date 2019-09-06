/*
   File: FX.cpp

   Author: The Ocular Man  (⌐0_0)
   Date:   9/6/2019

*/

#include "Arduino.h"
#include "FX.h"

FX::FX() {
  _color_count = 0;
  _pulse_count = 1;
  _old_mode = 42; //"Answer to the Ultimate Question of Life, the Universe, and Everything"
  refresh(); //test
}

uint8_t FX::getIntensity(void) {
  return _intensity;
}

int FX::getTime(void) {
  return _time;
}
int FX::getSmooth(void) {
  return _new_smooth;
}

Color FX::getStart(void) {
  return _start;
}

Color FX::getEnd(void) {
  return _end;
}

void FX::refresh(void) {
  if (_palette_size == 0) {
    _start = Color::Black;
    _end = Color::Black;
    _color_count = 0;
    return;
  }
  if (_old_mode != _mode) {
    _old_mode = _mode;
    speedMath();
  }
  fxCount();
}

void FX::speedMath(void) {
  if (_mode == 0) {
    _time = _delay;
    _new_smooth = 1;
  }
  if ((_mode == 1) || (_mode == 2)) {
    _time = _delay / _smooth;
    _new_smooth = _smooth;
  }
}

void FX::fxCount(void) {
  if (_mode == 3) {
    _start = Color::Black;
    _end = Color::Black;
    return;
  }
  if ((_mode == 0) || (_mode == 1)) {
    _start = _palette[_color_count % _palette_size];
    _end = _palette[(_color_count + 1) % _palette_size];
    _color_count++;
    return;
  }
  if (_mode == 2) {
    if (_pulse_count) {
      _start = Color::Black;
      _end = _palette[_color_count % _palette_size];
    }
    else {
      _start = _palette[_color_count % _palette_size];
      _end = Color::Black;
      _color_count++;
    }
    _pulse_count = !_pulse_count;
    return;
  }
}
