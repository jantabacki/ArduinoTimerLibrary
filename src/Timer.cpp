/*
  Timer.cpp - Library for calling methods in specified time.
  Created by Jan Tabacki, February 12, 2020.
  Released into the public domain.
*/

#include "Timer.h"

Timer::Timer(int howManyThreads)
{
  threadsArray = new TimerFunction[howManyThreads];
  threadsArraySize = howManyThreads;
}

void Timer::AddThread(void functionPointer(), long interval)
{
  if (threadsArrayIterator < threadsArraySize) {
    TimerFunction thread(functionPointer, interval, millis());
    threadsArray[threadsArrayIterator] = thread;
    threadsArrayIterator++;
  }
}

void Timer::RemoveThread(void functionPointer())
{
  for (int i = 0; i < threadsArraySize; i++) {
    if (threadsArray[i].pointer == functionPointer) {
      for (int j = i; j < threadsArraySize - 1; j++) {
        threadsArray[j] = threadsArray[j + 1];
      }
      threadsArrayIterator--;
      break;
    }
  }
}

void Timer::StartThreads()
{
  while (true) {
    CheckThreads();
    yield();
  }
}

void Timer::CheckThreads()
{
  for (int i = 0; i < threadsArrayIterator; i++) {
    long checkTime = millis();
    if (threadsArray[i].lastEllapsed + threadsArray[i].interval <= checkTime) {
      threadsArray[i].lastEllapsed = checkTime;
      (*threadsArray[i].pointer)();
    }
  }
}
