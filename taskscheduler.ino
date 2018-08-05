#include "debug.h"
#include "taskscheduler.h"

void execTask1(){
  pln(warning, "execute task one, time: " + String(millis()));
}

task *t;
TaskScheduler ts;

void setup() {
  initDbg();
  t = new task();
  t->init(1 /*prio*/, execTask1 /*func*/, 1000 /*cycle*/, 2 /*id*/);
  if(ts.registerTask(t) == 0)
    ts.startTask(t);
  else
    pln(error, "could not register task");
    
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  pln(error, "wait");
  ts.executeNext();
  delay(10);
}
