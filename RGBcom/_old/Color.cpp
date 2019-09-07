/*
   File: Color.cpp
   Adapted from https://github.com/leka/moti/tree/dev/lib/Color

*/

#include "Arduino.h"
#include "Color.h"

Color::Color() {
  _r = _g = _b = 0;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
  _r = r;
  _g = g;
  _b = b;
}

void Color::getRGB(uint8_t* r, uint8_t* g, uint8_t* b) {
  *r = _r;
  *g = _g;
  *b = _b;
}

uint8_t Color::getR(void) {
  return _r;
}

uint8_t Color::getG(void) {
  return _g;
}

uint8_t Color::getB(void) {
  return _b;
}

double __mod(double a, double b) {
  double r = fmod(a, b);

  return r < 0.f ? r + b : r;
}

void Color::setRGB(uint8_t r, uint8_t g, uint8_t b) {
  _r = r;
  _g = g;
  _b = b;
}

Color Color::randomColor(void) {
  return Color(random(0, 255), random(0, 255), random(0, 255));
}

// operateur ==
bool Color::isEgal(Color const& colora) const
{
  return (_r == colora._r && _g == colora._g && _b == colora._b); // test si c'est egal
}

const Color Color::Black = Color(0, 0, 0);

//use them if you want them
/*
  const Color Color::Black = Color(0, 0, 0);
  const Color Color::White = Color(255, 255, 255);
  const Color Color::RedPure = Color(255, 0, 0);
  const Color Color::GreenPure = Color(0, 255, 0);
  const Color Color::BluePure = Color(0, 0, 255);
  const Color Color::DarkRed = Color(186, 48, 42);
  const Color Color::LightRed = Color(222, 63, 89);
  const Color Color::Purple = Color(165, 67, 188);
  const Color Color::LightBlue = Color(95, 184, 224);
  const Color Color::LightPink = Color(255, 232, 225);
  const Color Color::Yellow = Color(250, 211, 51);
  const Color Color::DarkYellow = Color(244, 174, 51);
  const Color Color::Orange = Color(240, 143, 51);
  const Color Color::DarkOrange = Color(239, 134, 59);
  const Color Color::LightGreen = Color(216, 255, 56);
*/
