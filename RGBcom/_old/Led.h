/*
   File: Led.h
   Adapted from https://github.com/leka/moti/tree/dev/lib/Led

*/

#ifndef LED_H
#define LED_H

#include "Arduino.h"
#include "Color.h"

//Mode definitions
#define COMMON_ANODE 1
#define COMMON_CATHODE 0

class Led {
  public:
    Led();
    Led(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, bool acFlag);
    Led(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, Color colorValue, bool acFlag);

    Color dim(Color colorValue, uint8_t level); //0% - 100%
    Color dim(uint8_t redValue, uint8_t greeValue, uint8_t blueValue, uint8_t level); //0% - 100%

    void CATHODE(void);
    void ANODE(void);

    void shine(void);
    void shine(Color colorValue);
    void shine(Color colorValue, uint8_t level);
    void shine(uint8_t redValue, uint8_t greeValue, uint8_t blueValue);
    void shine(uint8_t redValue, uint8_t greeValue, uint8_t blueValue, uint8_t level);

    void turnOff(void);

    Color getColor(void);
    void setColor(Color colorValue);
    void setColor(Color colorValue, uint8_t level);

  protected:
    bool _AC;
    uint8_t _redPin, _greenPin, _bluePin;
    Color _colorValue;
};


#endif
