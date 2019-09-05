/* 
 *  CLI.cpp
 *  
 * Class Referance
 * 95% Borrowed Code
 * https://www.norwegiancreations.com/2018/02/creating-a-command-line-interface-in-arduinos-serial-monitor/
 * 
 */
#include "Arduino.h"
#include "cli.h"

//Inits all the things
void CLI::init(int (*cf[])(), const char *cs[], int _s) {
  _num_commands = _s;
  _commands_func = cf;
  _commands_str = cs;
  memset(line, 0, LINE_BUF_SIZE);
  memset(args, 0, sizeof(args[0][0]) * MAX_NUM_ARGS * ARG_BUF_SIZE);
  error_flag = 0;
}

//Reads line from serial buffer
bool CLI::readLine(void) {
  if (Serial.available()) { //If ya got something
    String string = Serial.readStringUntil("\n");      //Read till new line, or break after timeout
    if (strlen(string.c_str()) < LINE_BUF_SIZE) {      //Buffer check
      string.toCharArray(line, LINE_BUF_SIZE);  //Add to line buffer 
    }
    else {
      Serial.println("Input string too long.");
      error_flag = true;
    }
    return 1;
  }
  return 0;
}

// Parse line bufffer
void CLI::parseLine(void) {
  counter = 0;
  argument = strtok(line, " \n"); //im done documenting this.... ill finish it later

  while ((argument != NULL)) {
    if (counter < MAX_NUM_ARGS) {
      if (strlen(argument) < ARG_BUF_SIZE) {
        strcpy(args[counter], argument);
        argument = strtok(NULL, " \n");
        counter++;
      }
      else {
        Serial.println("Input string too long.");
        error_flag = true;
        break;
      }
    }
    else {
      break;
    }
  }
}

bool CLI::worker(void) {
  bool _return = 0;
  if (readLine()) {
    if (!error_flag) {
      parseLine();
    }
    if (!error_flag) {
      _return = execute();
    }
    error_flag = false;
    return _return; //something read
  }
  return 0; //false alarm
}

int CLI::execute(void) {
  for (int i = 0; i < _num_commands; i++) {
    if (strcmp(args[0], _commands_str[i]) == 0) {
      return (*_commands_func[i])();
    }
  }

  //memset(line, 0, LINE_BUF_SIZE);
  //memset(args, 0, sizeof(args[0][0]) * MAX_NUM_ARGS * ARG_BUF_SIZE);
  
  Serial.print(args[0]);
  Serial.println(" is an Invalid command.");
  return 0;
}

unsigned long CLI::get_argUlong(void) {
  unsigned long temp = strtoul(args[1], NULL, 16);
  return temp;
}

int CLI::get_argInt(void) {
  return atoi(args[1]);
}
