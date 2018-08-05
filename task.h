#pragma once

#ifndef _TASK_H_INCLUDED
#define _TASK_H_INCLUDED

#include "Arduino.h"
#include "debug.h"

class task{
  public:
    void init(int prio, void (*pfunc)(void), unsigned int pcycle, int pid){
      pln(trace, String(__func__));
      priority = prio;
      func = pfunc;
      lastExecutionTime = 0;
      /*
       * make a test call 
       */
      pln(info, "Exec test call");
      pfunc();
      
      cycle = pcycle;
      id = pid;
    };
    task *next;
    bool execute;
    int id;
    void (*func)(void);
    int priority;    
    unsigned int cycle;
    unsigned long lastExecutionTime = 0;
    bool callDue(){ 
      pln(trace, String(__func__) + "ts: " + String(millis()) + "ms");
      bool isDue = millis()>(lastExecutionTime+cycle);
      isDue ? pln(info, "task is due"):pln(info, "task is not due");
      return isDue; 
    }
  private:   
};

#endif
