/*
   File: Helper.cpp

   Author: The Ocular Man  (⌐0_0)
   Date:   9/6/2019

*/

#include "Arduino.h"
#include "Helper.h"

//Fades one tiny bit at a time, requires multiple calls
void fade(Color &from, Color to, int stepN, int smooth) {
  Color startColor = from;  //Starts with the working color
  Color endColor = to;

  int redDiff = endColor.getR() - startColor.getR();     //Calcs the difference between Red
  int greenDiff = endColor.getG() - startColor.getG();   //Calcs the difference between Green
  int blueDiff = endColor.getB() - startColor.getB();    //Calcs the difference between Blue

  int redValue, greenValue, blueValue;    //Temp values

  redValue = (int)startColor.getR() + changeN(redDiff, stepN, smooth);
  greenValue = (int)startColor.getG() + changeN(greenDiff, stepN, smooth);
  blueValue = (int)startColor.getB() + changeN(blueDiff, stepN, smooth);

  from = Color(redValue, greenValue, blueValue);
}

//Math to calculate the change value
double changeN(int diff, int stepN, int smooth) {
  return (diff / (double)smooth) * curve(stepN, smooth);
}

//Math to make the shifting non-linear. Current step number, Smooth factor.
double curve(double stepN, double smooth) {
  return pow(smooth, stepN / smooth) - 1.0;     //Plot it! its cool!
}
