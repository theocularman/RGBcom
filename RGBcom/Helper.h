/*
   File: Helper.h

   Author: The Ocular Man  (⌐0_0)
   Date:   9/6/2019

*/

#ifndef HELPER_H
#define HELPER_H

#include "Arduino.h"
#include "Color.h"

void fade(Color &from, Color to, int stepN, int smooth);
double changeN(int diff, int stepN, int smooth);
double curve(double stepN, double smooth);

#endif
