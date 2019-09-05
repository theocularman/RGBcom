/* 
 *  CLI.h
 *  
 * Class Referance
 * 95% Borrowed Code
 * https://www.norwegiancreations.com/2018/02/creating-a-command-line-interface-in-arduinos-serial-monitor/
 * 
 */

#ifndef CLI_H
#define CLI_H
#include "Arduino.h"

#define LINE_BUF_SIZE 64    //Maximum input string length
#define ARG_BUF_SIZE 10     //Maximum argument string length
#define MAX_NUM_ARGS 2      //Maximum number of arguments

class CLI {
  public:
    void init(int (*cf[])(), const char *cs[], int _s); //Inits things
    bool worker(void);                                  //Worker function, gets called from loop
    unsigned long get_argUlong(void);                   //Gets user argument
    int get_argInt(void);                               //Gets user argument

  private:
    bool error_flag;                        //ERR flag
    char line[LINE_BUF_SIZE];               //Line buffer
    char args[MAX_NUM_ARGS][ARG_BUF_SIZE];  //Argument buffer
    int counter;                            //Counter
    char *argument;                         //Char pointer
    int (**_commands_func)();               //Callback array pointer?
    const char **_commands_str;             //Command string pointer thing of doom.....
    int _num_commands;                      //Total number of commands to cycle

    int execute(void);                      //Goes to callback
    bool readLine(void);                    //Reads line from the serial buff
    void parseLine(void);                   //Parses and tokenizes the line buffer
};

#endif
