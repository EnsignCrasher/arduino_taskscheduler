#pragma once

#ifndef _DEBUG_H_INCLUDED
#define _DEBUG_H_INCLUDED

#include "Arduino.h" 

enum errLevel{
  error, 
  warning,
  info,
  trace
};

/*static class Debugger{
  public:
    static void pln(int lvl,String msg);
    static void init();
    bool initialized = false;
  private:
    
};*/

static void initDbg(){
//  if(!initialized){
     Serial.begin(9600);
     Serial.println("Debugger initialized");
//     initialized = true;
//  }  
}

static void pln(int lvl, String msg){
  switch(lvl){
    case error:
      Serial.println("   dbg [error]: " + msg);
      break;
    case warning:
      Serial.println("      dbg [warn ]: " + msg);
      break;
    case info:
      //Serial.println("         dbg [info ]: " + msg);
      break;
    case trace:
      Serial.println("dbg [trace]: " + msg);
      break;
    default:
      Serial.println("dbg        : " + msg);
      break;
  }
  delay(100);
}

#endif
