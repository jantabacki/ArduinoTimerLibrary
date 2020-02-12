/*
  Timer.h - Library for calling methods in specified time.
  Created by Jan Tabacki, February 12, 2020.
  Released into the public domain.
*/
#ifndef Timer_h
#define Timer_h

#include "TimerFunction.h"
#include "Arduino.h"

class Timer
{
private:
  typedef void (*functionPointer)();
  int threadsArrayIterator = 0;
  int threadsArraySize = 0;
  TimerFunction *threadsArray = new TimerFunction[1];
public:
  Timer();
  Timer(int);
  void AddThread(void functionPointer(), long interval);
  void RemoveThread(void functionPointer());
  void StartThreads();
  void CheckThreads();
};

#endif
