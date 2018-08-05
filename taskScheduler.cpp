#pragma once 
#include "TaskScheduler.h"

int TaskScheduler::getNextFreeId(){
  pln(trace, String(__func__) + "ts: " + String(millis()) + "ms");
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
  pln(trace, String(__func__) + "ts: " + String(millis()) + "ms");
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
  pln(trace, String(__func__) + "ts: " + String(millis()) + "ms");
  task *t = getNextHighestPrio();
  if(t != NULL){
    pln(info, "task " + String(t->id) + " found, last execution: " + String(t->lastExecutionTime));
    t->func();
    t->lastExecutionTime = millis();
    pln(info, "set last execution time to " + String(t->lastExecutionTime));
    pln(info, "func executed");
  } else {
    pln(info, "no task to execute");
    return -1; //no task scheduled
  }
}

task *TaskScheduler::getNextHighestPrio(){
  /*pln(trace, "test");
  t = registeredTasksHead.next;
  return true;*/
  
  pln(trace, String(__func__) + "ts: " + String(millis()) + "ms");
  
  task *t = NULL;
  //registeredTasksHead.next->id++;
  //pln(info, "increased tasksHead id, t id: " +String(t->id) + ", head next id: " + String(registeredTasksHead.next->id));
  task *tmp = registeredTasksHead.next;
  int highestPrio = 0;
  int highestID = 0;
  long t1 = millis();
  pln(info, "search scheduled task with highest priority");
  long t2 = millis();

  pln(info, "delta millis : " + String(t2-t1));
    
  while(tmp != NULL){
    if(tmp->priority > highestPrio && tmp->execute && tmp->callDue()){
      pln(info, "found task " + String(tmp->id) + " priority " + String(tmp->priority));
      highestPrio = tmp->priority;
      //found = true;
      highestID = tmp->id;
    } else {
      pln(info, "timestamp: " + String(millis()) + "ms");
      pln(info, "skip task " + String(tmp->id) + ", next execution in " + String(tmp->lastExecutionTime+tmp->cycle-millis()) + " ms");
      pln(info, "last execution was " + String(tmp->lastExecutionTime) + "ms");
      pln(info, "execution cycle " + String(tmp->cycle) + "ms");
    }
    tmp = tmp->next;
  }

  if(highestID != 0){
    t = getTaskById(highestID);
    pln(info, "t.id is " + String(t->id));
  } else {
    pln(info, "no task found");
  }  
  
  
  return t;
}

task* TaskScheduler::getTaskById(int id){
  pln(trace, String(__func__) + "ts: " + String(millis()) + "ms");
  task *t = registeredTasksHead.next;
  while(t != NULL){
    if(t->id == id)
      return t;

    t = t->next;
  }
  return NULL;
}

int TaskScheduler::stopTask(int id){
  pln(trace, String(__func__) + "ts: " + String(millis()) + "ms");
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
  pln(trace, String(__func__) + "ts: " + String(millis()) + "ms");
  t->execute = false;
  return 0;
}

int TaskScheduler::startTask(task *t){
  pln(trace, String(__func__) + "ts: " + String(millis()) + "ms");
  t->execute = true;
  return 0;
}

int TaskScheduler::registerTask(task *t){
  pln(trace, String(__func__) + "ts: " + String(millis()) + "ms");
  pln(info, "task id " + String(t->id));
  return insertTaskList(t);
}

int TaskScheduler::insertTaskList(task *t){
  pln(trace, String(__func__) + "ts: " + String(millis()) + "ms");
  pln(info, "task id " + String(t->id));
  if(t == NULL){
    pln(info, "task is null, return -1");
    return -1;
  }
  if(checkIdIsFree(t->id) != 0){
    pln(info, "task id is not free");
    return -1;
  }
    

  pln(info, "save registered tasks head, id");
  task *curFirst = registeredTasksHead.next;
  pln(info, "set head next task " + String(t->id));
  registeredTasksHead.next = t;
  pln(info, "set inserted task next");
  t->next = curFirst;
  return 0;
}





