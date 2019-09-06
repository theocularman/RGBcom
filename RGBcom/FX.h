/*
   File: FX.h

   Author: The Ocular Man  (⌐0_0)
   Date:   9/6/2019

*/

#ifndef FX_H
#define FX_H

#include "Arduino.h"
#include "Color.h"
#include "Token.h"

class FX : public Token {
  public:
    FX();
    void refresh(void);
    void fxCount(void);
    void speedMath(void);
    int getTime(void);
    int getSmooth(void);
    uint8_t getIntensity(void);

    Color getStart(void);
    Color getEnd(void);

  private:
    int _old_mode;
    int _time;
    int _step;
    int _new_smooth;
    int _color_count;
    bool _pulse_count;
    Color _start;
    Color _end;
};

#endif
