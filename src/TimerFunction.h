/*
  TimerFunction.h - Helper class for Timer library.
  Created by Jan Tabacki, February 12, 2020.
  Released into the public domain.
*/
#ifndef TimerFunction_h
#define TimerFunction_h

class TimerFunction
{
private:
  typedef void(*functionPointer)();
public:
  functionPointer pointer;
  int interval;
  unsigned long lastEllapsed;
  bool shouldBeExecuted = false;
  TimerFunction(functionPointer, int, unsigned long);
  TimerFunction();
};

#endif
