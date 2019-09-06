/*
   File: Color.h
   Adapted from https://github.com/leka/moti/tree/dev/lib/Color

*/

#ifndef COLOR_H
#define COLOR_H

#include "Arduino.h"

class Color {
  public:
    Color();
    Color(uint8_t r, uint8_t g, uint8_t b);

    void getRGB(uint8_t* r, uint8_t* g, uint8_t* b);
    uint8_t getR(void);
    uint8_t getG(void);
    uint8_t getB(void);

    void setRGB(uint8_t r, uint8_t g, uint8_t b);

    bool isEgal(Color const& colora) const;

    static Color randomColor(void);

    static const Color Black;

    //use them if you want them
    /*
        static const Color Black;
        static const Color White;
        static const Color RedPure;
        static const Color GreenPure;
        static const Color BluePure;
        static const Color DarkRed;
        static const Color LightRed;
        static const Color Purple;
        static const Color LightBlue;
        static const Color LightPink;
        static const Color Yellow;
        static const Color DarkYellow;
        static const Color Orange;
        static const Color DarkOrange;
        static const Color LightGreen;
    */
  private:
    uint8_t _r, _g, _b;
};


#endif
