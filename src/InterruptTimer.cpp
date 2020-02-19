/*
  Timer.cpp - Library for calling methods in specified time.
  Created by Jan Tabacki, February 12, 2020.
  Released into the public domain.
*/

#include "InterruptTimer.h"

int Timer::threadsArrayIterator = 0;
int Timer::threadsArraySize = 0;
TimerFunction* Timer::threadsArray = new TimerFunction[0];
bool Timer::wasMemoryAlocated = false;

void Timer::AddThread(void functionPointer(), int interval)
{
	if (threadsArrayIterator < threadsArraySize) {
		TimerFunction thread(functionPointer, interval, 0);
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

void Timer::EnableThread(void functionPointer()){
	for (int i = 0; i < threadsArraySize; i++) {
		if (threadsArray[i].pointer == functionPointer) {
			threadsArray[i].shouldBeExecuted = true;
			break;
		}
	}
}

void Timer::DisableThread(void functionPointer()){
	for (int i = 0; i < threadsArraySize; i++) {
		if (threadsArray[i].pointer == functionPointer) {
			threadsArray[i].shouldBeExecuted = false;
			break;
		}
	}
}

void Timer::CheckThreads()
{
	for (int i = 0; i < threadsArrayIterator; i++) {
		if(threadsArray[i].shouldBeExecuted){
			unsigned long checkTime = millis();
			if (threadsArray[i].lastEllapsed + threadsArray[i].interval <= checkTime) {
				threadsArray[i].lastEllapsed = checkTime;
				(*threadsArray[i].pointer)();
			}
		}
	}
}

void Timer::CreateSpace(int howManyThreads)
{
	if(!wasMemoryAlocated){
		threadsArray = new TimerFunction[howManyThreads];
		threadsArraySize = howManyThreads;
		wasMemoryAlocated = true;
		EnableInterruptTimer();
	}
}

void Timer::EnableInterruptTimer(){
	TCCR1A = 0;

	TCCR1B |= (1 << CS12);
	TCCR1B &= ~(1 << CS11);
	TCCR1B &= ~(1 << CS10);

	TCNT1 = 0;
	OCR1A = 63;

	TIMSK1 = (1 << OCIE1A);

	sei();
}

ISR(TIMER1_COMPA_vect){
	TCNT1 = 0;
	Timer::CheckThreads();
}
