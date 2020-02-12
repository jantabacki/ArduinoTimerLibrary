#include<Timer.h>

/*
 * (D2) (+)LED1(-) [Resistor] (GND)
 * (D3) (+)LED2(-) [Resistor] (GND)
 * (D4) (+)LED3(-) [Resistor] (GND)
 * (D5) (+)LED4(-) [Resistor] (GND)
*/

//Define how many threads you want to ues
Timer timer(4);

//Function which changes state of digital ouput 2 to oposite state when called
bool led1State = false;
void changeStateLED1() {
  led1State = !led1State;
  digitalWrite(2, led1State);
}

//Function which changes state of digital ouput 3 to oposite state when called
bool led2State = false;
void changeStateLED2() {
  led2State = !led2State;
  digitalWrite(3, led2State);
}

//Function which changes state of digital ouput 4 to oposite state when called
bool led3State = false;
void changeStateLED3() {
  led3State = !led3State;
  digitalWrite(4, led3State);
}

//Function which changes state of digital ouput 5 to oposite state when called
bool led4State = false;
void changeStateLED4() {
  led4State = !led4State;
  digitalWrite(5, led4State);
}

void setup() {
  //Prepare pins 2, 3, 4 and 5 to work as outputs
  for (int i = 2; i < 6; i++) {
    pinMode(i, OUTPUT);
  }
  //Add Function to calling shedule, first function will be called every 500ms
  timer.AddThread(&changeStateLED1, 500);
  //Second function will be called every 1000ms and so on
  timer.AddThread(&changeStateLED2, 1000);
  timer.AddThread(&changeStateLED3, 2000);
  timer.AddThread(&changeStateLED4, 4000);
  //Start timer to run all tasks in specified time
  timer.StartThreads();
}

void loop() {}
