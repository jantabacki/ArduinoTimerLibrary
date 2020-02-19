/*
  Timer.h - Library for calling methods in specified time.
  Created by Jan Tabacki, February 12, 2020.
  Released into the public domain.
*/
#ifndef InterruptTimer_h
#define InterruptTimer_h

#include "TimerFunction.h"
#include "Arduino.h"

class Timer
{
private:
	typedef void (*functionPointer)();
  	static int threadsArrayIterator;
	static int threadsArraySize;
	static TimerFunction *threadsArray;
	static bool wasMemoryAlocated;
	static void EnableInterruptTimer();
public:
	static void AddThread(void functionPointer(), int interval);
	static void RemoveThread(void functionPointer());
	static void CheckThreads();
	static void CreateSpace(int);
	static void EnableThread(void functionPointer());
	static void DisableThread(void functionPointer());
};

#endif
