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
      void (*func)(void) = pfunc;
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
      pln(trace, String(__func__));
      return millis()>(lastExecutionTime+cycle); 
    }
  private:   
};

#endif
