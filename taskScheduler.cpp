#pragma once 
#include "TaskScheduler.h"

int TaskScheduler::getNextFreeId(){
  pln(trace, String(__func__));
  for(int i=0;i<1000;i++){
      pln(info, "check " + String(i));
      if(checkIdIsFree(i)==0){
        pln(info, "return " + String(i));
        return i;
      }
  }
  pln(info, "failed");
  return -1;
}

int TaskScheduler::checkIdIsFree(int id){
  pln(trace, String(__func__));
  task *t = registeredTasksHead.next;
  pln(info, "search for id " + String(id));
  while(t != NULL){
    if(t->id == id)
      return -1;
    else
      t = t->next;
  }
  return 0;
}

int TaskScheduler::executeNext(){
  pln(trace, String(__func__));
  task *t = getNextHighestPrio();
  if(t){
    pln(info, "task found");
    t->func();
  } else {
    pln(info, "no task to execute");
    return -1; //no task scheduled
  }
}

task* TaskScheduler::getNextHighestPrio(){
  pln(trace, String(__func__));
  task *t = registeredTasksHead.next;
  task *mostRel = NULL;
  int highestPrio = 0;
  while(t != NULL){
    if(t && t->priority > highestPrio && t->execute && t->callDue()){
      pln(info, "found task " + String(t->id));
      highestPrio = t->priority;
      mostRel = t;
    }
    t = t->next;
  }
  return mostRel;
}

task* TaskScheduler::getTaskById(int id){
  pln(trace, String(__func__));
  task *t = registeredTasksHead.next;
  while(t != NULL){
    if(t->id == id)
      return t;
  }
  return NULL;
}

int TaskScheduler::stopTask(int id){
  pln(trace, String(__func__));
  task *t = getTaskById(id);
  if(t){
    stopTask(t);
    return 0;
  }else{
    return -1; //task not found 
  }
}

int TaskScheduler::startTask(int id){
  task *t = getTaskById(id);
  if(t){
    startTask(t);
    return 0;
  }else{
    return -1; //task not found 
  }
}

int TaskScheduler::stopTask(task *t){
  pln(trace, String(__func__));
  t->execute = false;
  return 0;
}

int TaskScheduler::startTask(task *t){
  pln(trace, String(__func__));
  t->execute = true;
  return 0;
}

int TaskScheduler::registerTask(task *t){
  pln(trace, String(__func__));
  return insertTaskList(t);
}

int TaskScheduler::insertTaskList(task *t){
  pln(trace, String(__func__));
  if(t == NULL)
    return -1;
  if(checkIdIsFree(t->id) != 0)
    return -1;

  pln(info, "save registered tasks head, id");
  task *curFirst = registeredTasksHead.next;
  pln(info, "set head next task " + String(t->id));
  registeredTasksHead.next = t;
  pln(info, "set inserted task next");
  t->next = curFirst;
  return 0;
}





