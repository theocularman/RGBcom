/*
   RGB LED controler with commandline interface
   up to 10 user configurable colors, 3 modes,
   delay & resolution control.

   Sketch uses 11012 bytes
   Global variables use 943 bytes of dynamic memory

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

*/

#include "Led.h"
#include "Color.h"
#include "CLI.h"
#include "LedAt.h"
#include "LedFunc.h"

//Defs
#define TIMEOUT 100
#define BAUD 115200

#define R_PIN 10
#define G_PIN 9
#define B_PIN 11

//Function declarations
void fadeNoDelay(void);
void breathNoDelay(void);
void flashNoDelay(void);

//Function declarations for Callback/Commands
int cmd_flash();
int cmd_fade();
int cmd_breath();
int cmd_delay();
int cmd_resolution();
int cmd_rest();
int cmd_new();
int cmd_set();
int cmd_off();
int cmd_on();

//List of functions pointers corresponding to each command
int (*commands_func[])() {
  &cmd_flash,
  &cmd_fade,
  &cmd_breath,
  &cmd_delay,
  &cmd_resolution,
  &cmd_reset,
  &cmd_new,
  &cmd_set,
  &cmd_off,
  &cmd_on
};

//List of command names
const char *commands_str[] = {
  "flash",
  "fade",
  "breath",
  "delay",
  "res",
  "reset",
  "new",
  "set",
  "off",
  "on"
};

//Global class objects
CLI ledCli;                                 //LED CommandLine Interface
Led led(R_PIN, G_PIN, B_PIN, COMMON_ANODE); //LED class object
LedAt ledAt;                                //LED attribute object

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);         //Sets the baudrate for the serial com
  Serial.setTimeout(TIMEOUT); //Sets the read timeout
  ledCli.init(commands_func, commands_str, sizeof(commands_str) / sizeof(char *)); //Inits the commandline inteface
  Serial.println("LED CLI, Ready.");  //Meaningless ready message
}

void loop() {
  // put your main code here, to run repeatedly:
  while (1) {
    if (ledAt.getMode() == 0) {                     //Flashmode
      flashNoDelay(); //set delay '1000'
    }
    if (ledAt.getMode() == 1) {                     //Fademode
      fadeNoDelay(); //set delay '2000', res '50'
    }
    if (ledAt.getMode() == 2) {                     //Breath mode
      breathNoDelay(); //set delay '2000', res '50'
    }
    //Mode = 3...?, mystery mode!, cheap 'off' bug.... feature!
    ledCli.worker();
  }
}

//Command function, sets the display mode
int cmd_flash() {
  Serial.println("Flash Mode");
  ledAt.setMode(0); //Set mode in led attribute obj
  return 1;
}

//Command function, sets the display mode
int cmd_fade() {
  Serial.println("Fade Mode");
  ledAt.setMode(1); //Set mode in led attribute obj
  return 1;
}

//Command function, sets the display mode
int cmd_breath() {
  Serial.println("Breath Mode");
  ledAt.setMode(2); //Set mode in led attribute obj
  return 1;
}

//Command function, sets the delay time
int cmd_delay() {
  int a = ledCli.get_argInt();      //Grabs users delay value
  if (a >= ledAt.getResolution())   //Checks bounds
  {
    ledAt.setDuration(a);           //Sets delay
    Serial.print("Delay "); Serial.println(a);
  }
  else
  {
    Serial.print("n >= "); Serial.println(ledAt.getResolution());
    return 0; //Error
  }
  return 1; //All is well, break from mode and re-enter
}

//Command function, sets the resolution
int cmd_resolution() {
  int a = ledCli.get_argInt();        //Grabs user resolution
  if (a <= ledAt.getDuration()) {     //Checks bounds
    ledAt.setResolution(a);           //Sets resolution
    Serial.print("Resolution "); Serial.println(a);
  }
  else {
    Serial.print("n <= "); Serial.println(ledAt.getDuration());
    return 0; //Error
  }
  return 1; //All is well, break from mode and re-enter
}

//Resets to default values
int cmd_reset() {
  ledAt.reset();    //Calls reset function
  Serial.println("Reset to Default");
  return 1; //All is well, break from mode and re-enter
}

//Clears colors in buffer, well... just sets index to zero
int cmd_new() {
  ledAt.setMode(0);
  ledAt.setDuration(500);
  ledAt.setResolution(50);
  ledAt.setIndex(0);
  Serial.println("Color Memory Cleared");
  return 1; //All is well, break from mode and re-enter
}

//Sets new color
int cmd_set() {
  unsigned long c = ledCli.get_argUlong();
  int a = ledAt.setColor(c); //Grabs users hex value
  if (a)  {
    if (a == 1)
      Serial.println("Color Out of Range");
    else
      Serial.println("Color Memory Full");
    return 0; //Error
  }
  Serial.println("New Color Added");
  return 1; //All is well, break from mode and re-enter
}

//Turns leds off, and throws mode out of bounds
int cmd_off() {
  if (ledAt.getMode() == 3)
    return 0;
  led.shine(0, 0, 0); //Led's off
  ledAt.setMode(3); //Mystery mode!
  Serial.println("...Fine, Powering OFF");
  return 1; //All good
}

//Turn on, saves last mode
int cmd_on() {
  if (ledAt.getMode() != 3)
    return 0;
  ledAt.setMode(ledAt.getLastMode()); //Sets last mode for resume
  Serial.println("I'm Turned ON Now! YaY!");
  return 1; //All good
}

//Flash animation loop with no delays
void flashNoDelay(void) {
  int _time, _res, _size, cnt = 0;
  Color *_array = ledAt.getAllAt(_time, _res, _size); //Grabs array, time, resolution & index from LED attributes obj
  Color swatch = _array[cnt]; //Color obj, init with first color
  unsigned long previousMillis1 = 0; //Delay counter

  //Loops forever, untill command from user is valid
  while (1) {
    unsigned long currentMillis = millis(); //Keeps time
    if ((currentMillis - previousMillis1 >= _time)) { //If our time has been hit
      previousMillis1 = currentMillis;  // Remember the time
      led.shine(swatch);  //Apply the swatch color
      cnt = (cnt + 1) % _size;  //Update color counter
      swatch = _array[cnt];     //assign new color to swatch
    }
    if (ledCli.worker())  //If a command has been recived, break from func
      return; //returns to 'loop'
  }
}

//Breath animation loop with no delays
void breathNoDelay(void) {
  int _time, _res, _size, cnt = 0;
  Color *_array = ledAt.getAllAt(_time, _res, _size); //Grabs array, time, resolution & index from LED attributes obj
  int _delay = _time / _res;  //Calculate new sub-cycle delay
  unsigned long previousMillis1 = 0; //Delay counter

  while (1) {
    Color swatch = Color(0, 0, 0); //Black
    Color swap = _array[cnt]; //working color thing
    int breath_cnt = 0;   //Breath counter
    while (breath_cnt < 2) {  //Cycles twice, off->color, color->off
      int _step = 0;  //Fade step counter
      bool _break = 1;  //Break flag

      while (_break) {
        unsigned long currentMillis = millis(); //Keeps time
        if ((currentMillis - previousMillis1 >= _delay)) {  //If our time was hit
          previousMillis1 = currentMillis;  // Remember the time
          fade(&swatch, swap, _step, _res); //Fade the color by one step
          led.shine(swatch);  //Show the swatch
          _step++;  //Inc step
          if (_step >= _res) //If the step cnt is = to the resolution, thats one cycle
            _break = 0; //break from cycle
        }
        if (ledCli.worker())  //If a command has been recived, break from func
          return;
      }
      swap = Color(0, 0, 0); //BLACK!!!!!
      breath_cnt++; //incriment Breath counter
    }
    cnt = (cnt + 1) % _size;  //Incriment color counter
  }
}

//Fade animation loop with no delays
void fadeNoDelay(void) {
  int _time, _res, _size, cnt = 0;
  Color *_array = ledAt.getAllAt(_time, _res, _size); //Grabs array, time, resolution & index from LED attributes obj
  int _delay = _time / _res;  //Calculate new sub-cycle delay
  unsigned long previousMillis1 = 0; //Delay counter

  while (1) {
    bool _break = 1;  //Break flag
    int _step = 0; //sub-cycle step counter
    Color swatch = _array[cnt]; //Color ojb

    while (_break) {
      unsigned long currentMillis = millis(); //Keep the time man
      if ((currentMillis - previousMillis1 >= _delay)) { //If times up, do the things
        previousMillis1 = currentMillis;  // Remember the time
        fade(&swatch, _array[(cnt + 1) % _size], _step, _res);  //Fade one sub-cycle
        led.shine(swatch);  //Show the Swatch
        _step++;  //Sub-cycle step counter
        if (_step >= _res) //If the step cnt is = to the resolution, thats one cycle
          _break = 0; //break from cycle
      }
      if (ledCli.worker()) //If a command has been recived, break from func
        return;
    }
    cnt = (cnt + 1) % _size; //Incriment color counter
  }
}


/*
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

*/
