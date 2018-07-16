#pragma once 

#ifndef _TS_INCLUDED
#define _TS_INCLUDED

#include "Arduino.h"
#include "task.h"
#include "debug.h"

/*
 * Examples:
 *  Scheduling a task:
 *    task t;
 *    TaskScheduler ts;
 *    t.init([prio], [func], [cycle], [id]);
 *    if(ts.registerTask(t) == 0)
 *      ts.startTask(t);
 *  
 *  Delete Task:
 *    Todo
 */

class TaskScheduler{
  public:
    int registerTask(task *t);
    
    int startTask(int id);
    int startTask(task *t);
    
    int stopTask(int id);
    int stopTask(task *t);
    
    int getNextFreeId();
    int executeNext();
  private:
    int checkIdIsFree(int id);
    int insertTaskList(task *t);
    task* getTaskById(int id);
    int deleteElementById(int id);
    task *getNextHighestPrio();
    task registeredTasksHead;
};

#endif


