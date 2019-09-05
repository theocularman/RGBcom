/*
   LedAt.cpp

   Container class for LED attributes, modes and such

   Author: The Ocular Man  (⌐0_0)
   Date:   9/4/2019

*/

#include "Arduino.h"
#include "LedAt.h"

//Resets data on call
LedAt::LedAt() {
  reset();
}

//Get function, return color array, and duration, resolution, index
Color *LedAt::getAllAt(int &_t, int &_r, int &_s) {
  _t = _duration;
  _r = _resolution;
  _s = _index;
  return _array;
}

//Resets the internals of thething
void LedAt::reset(void) {
  _mode = 0;                    //Mode flash
  _duration = 500;              //Duration, 500ms
  _resolution = 50;             //Resolution 50, 10ms subcycle
  _index = 3;                   //colors in buffer
  _array[0] = Color(255, 0, 0); //red
  _array[1] = Color(0, 255, 0); //green
  _array[2] = Color(0, 0, 255); //blue
}

//Sets mode
void LedAt::setMode(int _m) {
  _last_mode = _mode; //Mode history
  _mode = _m;
}

//Gets mode
int LedAt::getMode(void) {
  return _mode;
}

//Returns last mode
int LedAt::getLastMode(void)
{
  return _last_mode;
}

//Sets duration
void LedAt::setDuration(int _t) {
  _duration = _t;
}

//Gets durration
int LedAt::getDuration(void) {
  return _duration;
}

//Sets resolution
void LedAt::setResolution(int _r) {
  _resolution = _r;
}

//Gets resoltion
int LedAt::getResolution(void) {
  return _resolution;
}

//Set the color in the next buffer spot
int LedAt::setColor(unsigned long _color) {
  if (_color > 0xFFFFFF)  //Color out of range?
    return 1;
  if (_index >= COLOR_BUF_SIZE) //Buffer full?
    return 2;

  int b = _color & 0xFF;          //Mask for blue value
  int g = (_color >> 8) & 0xFF;   //Mask for green value
  int r = (_color >> 16) & 0xFF;  //Mask for red value

  _array[_index] = Color(r, g, b); //Sets rgb value in color array buffer
  _index++;                        //Steps to next cell

  return 0;
}

//Sets the index
int LedAt::setIndex(int _s) {
  _index = _s;
}
