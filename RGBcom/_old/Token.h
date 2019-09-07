/*
   File: Token.h

   Author: The Ocular Man  (⌐0_0)
   Date:   9/6/2019

*/

#ifndef TOKEN_H
#define TOKEN_H

#include "Arduino.h"
#include "Color.h"

#define PALETTE_SIZE 10

class Token {
  public:
    Token();
    void reset(void);
    /* callback junk */
    void setMode(uint8_t mode);
    uint8_t getMode(void);
    uint8_t getModeH(void);
    int getDelay(void);
    void setDelay(int delay_speed);
    void setSmooth(int smooth);
    void setIntensity(int intensity);
    void setNew(uint8_t n);
    int setColor(unsigned long _color);

  protected:
    Color _palette[PALETTE_SIZE];
    uint8_t _palette_size;
    uint8_t _mode;
    uint8_t _intensity;
    int _delay;
    int _smooth;
    uint8_t _mode_h;
};

#endif
