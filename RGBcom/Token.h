/*
   File: Token.h

   Author: The Ocular Man  (⌐0_0)
   Date:   9/6/2019

*/

#ifndef TOKEN_H
#define TOKEN_H

#include "Arduino.h"
#include "EEPROM.h"
#include "Color.h"

#define PALETTE_SIZE 10

class Token {
  public:
    Token();
    void reset(void);
    void LoadPer(void); //load from eeprom
    void SavePer(void); //save to eeprom

    void HEXtoRGB(uint8_t &r, uint8_t &g, uint8_t &b, unsigned long _color);
    unsigned long RGBtoHEX(uint8_t r, uint8_t g, uint8_t b);

    /* callback junk */
    void setMode(uint8_t mode);
    uint8_t getMode(void);
    uint8_t getModeH(void);
    int getDelay(void);
    void setDelay(int delay_speed);
    void setSmooth(int smooth);
    void setIntensity(uint8_t intensity);
    void setNew(uint8_t n);
    uint8_t setColor(unsigned long _color);
    uint8_t getPsize(void);
    Color getColorAt(uint8_t n);

  protected:
    Color _palette[PALETTE_SIZE];
    uint8_t _palette_size;
    uint8_t _mode;
    uint8_t _intensity;
    int _delay;
    int _smooth;
    uint8_t _mode_h;

    /* Struct for eeprom read / write */
    /* 48 bytes? */
    int eeAddress;
    struct SaveState {
      uint8_t _new;
      uint8_t _pal_size;
      uint8_t _mode;
      uint8_t _int;
      int _delay;
      int _smot;
      unsigned long _pal[PALETTE_SIZE];
    };

    SaveState persistence;
};

#endif
