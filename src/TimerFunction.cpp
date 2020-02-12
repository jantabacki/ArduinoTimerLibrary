/*
  TimerFunction.cpp - Helper class for Timer library.
  Created by Jan Tabacki, February 12, 2020.
  Released into the public domain.
*/

#include "TimerFunction.h"

TimerFunction::TimerFunction(functionPointer function, long intervalValue, long ellapsed)
{
  pointer = function;
  interval = intervalValue;
  lastEllapsed = ellapsed;
}

TimerFunction::TimerFunction() {

}
