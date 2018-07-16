#include "debug.h"
#include "taskscheduler.h"

void execTask1(){
  pln(info, "execute task one");
}

task t;
TaskScheduler ts;

void setup() {
   t.init(1 /*prio*/, execTask1 /*func*/, 3000 /*cycle*/, 1 /*id*/);
   if(ts.registerTask(&t) == 0)
    ts.startTask(&t);

}

void loop() {
  // put your main code here, to run repeatedly:
  pln(info, "wait");
  ts.executeNext();
}
