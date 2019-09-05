/*
 * LedFunc.h
 * 
 * Helper functions for fadeing RGB values
 * 
 * Author: The Ocular Man  (⌐0_0)
 * Date:   9/4/2019
 * 
 */

#ifndef LEDFUNC_H
#define LEDFUNC_H
#include "Arduino.h"
#include "Color.h"

//Fades from 'working', to 'colorTo'. 'working' gets over written. Returns after '1 sub-cycle' of color shifting
//Takes current step & total steps
void fade(Color *working, Color colorTo, int16_t _step, int16_t step_size); 

//Math to make the shifting non-linear
double curve(double x, double res);

#endif
