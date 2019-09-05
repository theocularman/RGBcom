/*
 * LedAt.h
 * 
 * Container class for LED attributes, modes and such
 * 
 * Author: The Ocular Man  (⌐0_0)
 * Date:   9/4/2019
 * 
 */

#ifndef LEDAT_H
#define LEDAT_H
#include "Arduino.h"
#include "Color.h"

#define COLOR_BUF_SIZE 10   //Max size of internal color buffer

class LedAt {
  public:
    LedAt();
    void setDuration(int _t);                     //Sets the cycle durration
    bool addColor(int _c);                        //Adds color to the buffer
    void reset(void);                             //Reset to default
    void clearColor();                            //Clears the colors in the buffer
    void setResolution(int _r);                   //Sets the color resolution, small = corse, large = fine
    void setMode(int _m);                         //Sets the animation mdoe
    int getMode(void);                            //Gets the animation mode
    int getLastMode(void);                        //Returns the last mode
    int getResolution(void);                      //Gets the resolution
    int getDuration(void);                        //Gets the duration         
    int setColor(unsigned long _color);           //Sets the color
    int setIndex(int _s);                         //Sets the index
    Color *getAllAt(int &_t, int &_r, int &_s);   //Gets Color array, durration, resolution, index
  private:
    Color _array[COLOR_BUF_SIZE];                 //Color array buffer
    int _index;
    int _mode;
    int _duration;
    int _resolution;
    int _last_mode;
};

#endif
