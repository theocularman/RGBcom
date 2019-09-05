# RGBcom
 Arduino RGB interface

## Intro
 This Project is the start of an arduino based, *dumb* RGB strip controller useing PWM.
 None of that fancy addressable stuff here kids.
 
### Features 
 - USB serial communications, for sending commands from the PC using the command line interface.
 - Super Basic command stucture.
 - Fast response time.
 - User programmable color palette, up to 10 unique colors.
 - User programmable color sequence.
 - 3 operating modes, **Flash**, **Fade** and **Breath**.
 - User programmable speed and resolution (for fade sensitivity).
 - Common Anode / Cathode, ```Led led(R_PIN, G_PIN, B_PIN, COMMON_ANODE); //LED class object```
 
### Command Help
```
   RGB LED controler with commandline interface
   up to 10 user configurable colors, 3 modes,
   delay & resolution control.

   Sketch uses 11012 bytes
   Global variables use 999 bytes of dynamic memory

   Author: The Ocular Man  (⌐0_0)
   Date:   9/4/2019

   Commands:
   --- Modes ---
   flash    : This enters the flashing mode
   fade     : This enters the fade mode
   breath   : This enters the breath mode
   off      : Turns LEDs off
   on       : Turns LEDs on

   --- Parm settings ---
   reset    : this puts everything back into defalt (rgb flash)
   delay n  : This sets the total delay time per cycle
   res n    : This sets the resolution of the cycle
   <notes>    The delay between cycles can be calulated like this
              delay/res = cycle delay
              ex. 2000ms/50 = 40ms, so 40ms per each sub-cycle (led break time)

   --- Color Commands ---
   new            : This clears all the colors in the color buffer
   set NNNNNN     : This sets one color at a time, color 1 - color 10, in
                    that order. Colors are set in HEX
   -- example --
   new
   set 00FF00      //Sets GREEN, color 1
   set FF0000      //Sets RED, color 2
   fade            //Fades between color 1 and color 2
   delay 2000      //Sets delay to 2000ms
   res 50          //Sets resolution to 50, 2000/50= 40ms per subcycle
   res 100         //Sets the resolution to 100, 20ms per subcycle
   reset           //Back to default
```

## Hardware
 Work in progress...
 