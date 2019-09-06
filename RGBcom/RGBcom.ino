/*
   RGB LED controler with commandline interface
   Up to 10 user configurable colors.
   3 modes: flash, fade, pulse.
   User configurable delay.
   User configurable smoothing.
   User configurable intensity control.

   Sketch uses 9596 bytes
   Global variables use 524 bytes of dynamic memory

   Author: The Ocular Man  (⌐0_0)
   Date:   9/6/2019

   -- Common Cathode mode is untested --

   Commands:
   --- Modes ----------------------------------------------------------
   flash    : This enters the flash mode
   fade     : This enters the fade mode
   pulse    : This enters the pulse mode
   off      : Turns LEDs off
   on       : Turns LEDs on

   --- Parm settings ---------------------------------------------------
   reset        : This puts everything back into defalt (rgb flash)
   delay n      : This sets the total delay time per cycle
   dim n        : dims the lights 0% - 100%, default is 90%
   smooth n     : This sets the resolution of the cycle
   <notes>        The delay between cycles can be calulated like this
                  delay/res = cycle delay
                  ex. 2000ms/50 = 40ms, so 40ms per each sub-cycle (led break time)

   --- Color Commands ----------------------------------------------------
   new            : This clears all the colors in the color buffer
   set NNNNNN     : This sets one color at a time, color 1 - color 10, in
                    that order. Colors are set in HEX, 'FF00FF'.
   -- example -----------------------------------------------------------
   new                //Clears current colors
   set 00FF00         //Sets GREEN, color 1
   set FF0000         //Sets RED, color 2
   fade               //Fades between color 1 and color 2
   delay 2000         //Sets delay to 2000ms
   smooth 50          //Sets resolution to 50, 2000/50= 40ms per subcycle
   pulse              //Sets pulse mode
   smooth 100         //Sets the resolution to 100, 20ms per subcycle
   dim 50             //Dims the light level
   reset              //Back to default

*/

#include "Led.h"
#include "Color.h"
#include "Helper.h"
#include "FX.h"
#include "CLI.h"

#define TIMEOUT 100
#define BAUD 115200

/* Change for your RGB pins */
#define R_PIN 10
#define G_PIN 9
#define B_PIN 11

//Function declarations for Callback/Commands
int cmd_flash();
int cmd_fade();
int cmd_pulse();
int cmd_delay();
int cmd_smooth();
int cmd_rest();
int cmd_new();
int cmd_set();
int cmd_off();
int cmd_on();
int cmd_dim();

//List of functions pointers corresponding to each command
int (*commands_func[])() {
  &cmd_flash,
  &cmd_fade,
  &cmd_pulse,
  &cmd_delay,
  &cmd_smooth,
  &cmd_reset,
  &cmd_new,
  &cmd_set,
  &cmd_off,
  &cmd_on,
  &cmd_dim
};

//List of command names
const char *commands_str[] = {
  "flash",
  "fade",
  "pulse",
  "delay",
  "smooth",
  "reset",
  "new",
  "set",
  "off",
  "on",
  "dim"
};

/* -------- Main junk ---------- */

FX RGB;
Led led(R_PIN, G_PIN, B_PIN, COMMON_ANODE); //LED class object, COMMON_ANODE or COMMON_CATHODE
CLI CommandLine;                            //LED CommandLine Interface

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
  Serial.setTimeout(TIMEOUT); //Sets the read timeout
  Serial.println("RGBcom TestA");
  CommandLine.init(commands_func, commands_str, sizeof(commands_str) / sizeof(char *));
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long previousMillis = 0;

  while (1)
  {
    RGB.refresh();
    Color _start = RGB.getStart();
    Color _end = RGB.getEnd();

    int _step = 0;
    while (_step < RGB.getSmooth()) //Derp, idk how I missed that
    {
      unsigned long currentMillis = millis();
      if ((currentMillis - previousMillis >= RGB.getTime()))
      {
        previousMillis = currentMillis;
        fade(_start, _end, _step, RGB.getSmooth());
        led.shine(_start, RGB.getIntensity());
        _step++;
      }
      if (CommandLine.worker())
        break;
    }
  }
}

/* -------- Command functions below ---------- */

//Command function, sets the display mode
int cmd_flash() {
  Serial.println(F("Flash"));
  RGB.setMode(0); //flash
  return 1;
}

//Command function, sets the display mode
int cmd_fade() {
  Serial.println(F("Fade"));
  RGB.setMode(1); //fade
  return 1;
}

//Command function, sets the display mode
int cmd_pulse() {
  Serial.println(F("Pulse"));
  RGB.setMode(2); //fade
  return 1;
}

//Command function, sets the delay time
int cmd_delay() {
  int _delay = CommandLine.getArgInt();
  if (_delay < RGB.getSmooth()) {
    Serial.print(F("n >= ")); Serial.println(RGB.getSmooth());
    return 0;
  }
  RGB.setDelay(_delay);
  RGB.speedMath();
  Serial.print(F("Set ")); Serial.println(_delay);
  return 1;
}

//Command function, sets the resolution
int cmd_smooth() {
  int _smooth = CommandLine.getArgInt();
  if ((_smooth > 256) || (_smooth > RGB.getDelay())) {
    Serial.print(F("256 > n < ")); Serial.println(RGB.getDelay());
    return 0;
  }
  RGB.setSmooth(_smooth);
  RGB.speedMath();
  Serial.print(F("Set ")); Serial.println(_smooth);
  return 1;
}

//Resets to default values
int cmd_reset() {
  RGB.reset();
  RGB.speedMath();
  Serial.println(F("Reset"));
  return 1;
}

//Turns leds off, and throws mode out of bounds
int cmd_off() {
  if (RGB.getMode() == 3)
    return 0;
  RGB.setMode(3); //Super Secret Mystery Mode!
  led.turnOff();
  Serial.println(F("OFF"));
  return 1;
}

//Turn on, saves last mode
int cmd_on() {
  if (RGB.getMode() != 3)
    return 0;
  RGB.setMode(RGB.getModeH());
  Serial.println(F("ON"));
  return 1;
}

//Sets the Intensity, 0% - 100%
int cmd_dim() {
  int _intensity = CommandLine.getArgInt();
  if ((_intensity < 0) || (_intensity > 100)) {
    Serial.print(F("n = 0-100"));
    return 0;
  }
  RGB.setIntensity(_intensity);
  Serial.print(F("Set %")); Serial.println(_intensity);
  return 0;
}

//Clears colors in buffer, well... just sets index to zero
int cmd_new() {
  RGB.setNew(0);
  //RGB.refresh();
  Serial.println("M Wipe");
  return 1;
}

//Sets new color
int cmd_set() {
  unsigned long colorHEX = CommandLine.getArgUlong();
  uint8_t flag = RGB.setColor(colorHEX);
  if (flag == 0) {
    Serial.println(F("Color Added"));
    return 1;
  }
  if (flag == 1)
    Serial.println(F("Out of Range"));
  else
    Serial.println(F("Mem Full"));
  return 0;
}

/* --- notes-----

   -- Fire Fx --
   new
   set bd0000
   set ff3700
   set 470000
   set ff9100
   set bd0000
   set ff3700
   fade
   res 7      //4 - 10.. 20?
   delay 400  //400 - 800

  ---------------- */
