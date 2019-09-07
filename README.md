# RGBcom
 Arduino RGB Controller with Terminal

## Intro
 This Project is the start of an arduino based, *dumb* RGB strip controller useing PWM.
 None of that fancy addressable stuff here kids.
 
 My hope is to replace my existing RGB LED controller. I'm tired of useing the chintzy remote,
 and I feel it has limited lighting options.
 
### Current Features 
 - USB serial communications, for sending commands from the PC using the command line interface.
 - Super Basic command structure.
 - Fast response time.
 - User programmable color palette, up to 10 unique colors.
 - User programmable color sequence.
 - User configurable intensity control.
 - On/Off control.
 - Save to EEPROM (for avr boards).
 - Dump the setting over serial.
 - 3 operating modes, **Flash**, **Fade** and **Pulse**.
 - User programmable speed and resolution (for fade sensitivity).
 - Common Anode / Cathode, ```Led led(R_PIN, G_PIN, B_PIN, COMMON_ANODE); //LED class object```
 
### Command Help
```
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
   save     : Saves to EEPROM, loaded @ start
   dump     : Dumps current settings

   --- Settings ---------------------------------------------------
   reset        : This puts everything back into defalt (rgb flash)
   delay n      : This sets the total delay time per cycle
   dim n        : This dims the lights 0% - 100%, default is 90%
   smooth n     : This sets the resolution of the cycle
   <notes>        The delay between cycles can be calulated like this
                  delay/res = cycle delay
                  ex. 2000ms/50 = 40ms, so 40ms per each sub-cycle (led break time)

   --- Color Commands ----------------------------------------------------
   new            : This clears all the colors in the color buffer
   set NNNNNN     : This sets one color at a time, color 1 - color 10, in
                    that order. Colors are set in HEX, 'FF00FF'.
   -- example -----------------------------------------------------------
   new                // Clears current colors
   set 00FF00         // Sets GREEN, color 1
   set FF0000         // Sets RED, color 2
   fade               // Fades between color 1 and color 2
   delay 2000         // Sets delay to 2000ms
   smooth 50          // Sets resolution to 50, 2000/50= 40ms per subcycle
   pulse              // Sets pulse mode
   smooth 100         // Sets the resolution to 100, 20ms per subcycle
   dim 50             // Dims the light level to 50%
   reset              // Back to default
   save               // Saves current settings to EEPROM, loaded @ start
   dump               // Dumps settings

```

## Use case
 Ideal applications include
 
 - USB controlled desk lighting
 - USB controlled PC case lighting
 - Cheap USB controlled adult film lighting (just a joke... maybe).

## Setup
 ### Change The Pin Definitions
 ```
 /* Change for your RGB pins */
    #define R_PIN 10
    #define G_PIN 9
    #define B_PIN 11
 ```
 ### Change The Common Mode
 ```
 Led led(R_PIN, G_PIN, B_PIN, COMMON_ANODE);
 Led led(R_PIN, G_PIN, B_PIN, COMMON_CATHODE); //untested
 ```

 Once the arduino has been programmed with *RGBcom* your ready to controll your LEDs over USB with commands.
 
 **Hardware setup will also be required, see the hardware section below.**


## Hardware
 Work in progress...
 