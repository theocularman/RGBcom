/*
 * LedFunc.cpp
 * 
 * Helper functions for fadeing RGB values
 * 
 * Author: The Ocular Man  (⌐0_0)
 * Date:   9/4/2019
 * 
 */

#include "Arduino.h"
#include "LedFunc.h"

//Fades one tiny bit at a time, requires multiple calls
void fade(Color *working, Color colorTo, int16_t _step, int16_t step_size) {
 
  Color *startColor = working;  //Starts with the working color
  Color endColor = colorTo;     
  int16_t redDiff = endColor.getR() - startColor->getR();     //Calcs the difference between Red
  int16_t greenDiff = endColor.getG() - startColor->getG();   //Calcs the difference between Green
  int16_t blueDiff = endColor.getB() - startColor->getB();    //Calcs the difference between Blue

  int16_t redValue, greenValue, blueValue;    //Temp values

  /*
   * To 'fade' we add small bits to the working color
   * small bits being, the difference between the two colors
   * devided by the total step size, then multiplyed by
   * the current step. This gives us a 'gradient' as steps++.
   * The current step is 'curved' to make the values non-linear. 
   * It looks better that way.
  */
  redValue = (int16_t)startColor->getR() + (redDiff / (double)step_size) * curve(_step, step_size);
  greenValue = (int16_t)startColor->getG() + (greenDiff / (double)step_size) * curve(_step, step_size);
  blueValue = (int16_t)startColor->getB() + (blueDiff / (double)step_size) * curve(_step, step_size);

  working->setRGB(redValue, greenValue, blueValue); //Give the working color a new color, closer to the end color by n steps.
}

//Math to make the shifting non-linear, takes 'current step number' and 'resolution'
double curve(double x, double res) {
  return pow(res, x / res) - 1.0;     //Plot it! its cool!
}
