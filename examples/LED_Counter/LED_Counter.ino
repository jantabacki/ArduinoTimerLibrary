#include<Timer.h>

/*
   (D2) (+)LED1(-) [Resistor] (GND)
   (D3) (+)LED2(-) [Resistor] (GND)
   (D4) (+)LED3(-) [Resistor] (GND)
   (D5) (+)LED4(-) [Resistor] (GND)
*/

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
  //Define how many threads you want to ues
  Timer::CreateSpace(4);
  //Prepare pins 2, 3, 4 and 5 to work as outputs
  for (int i = 2; i < 6; i++) {
    pinMode(i, OUTPUT);
  }
  //Add Function to calling shedule, first function will be called every 500ms
  Timer::AddThread(&changeStateLED1, 500);
  //Second function will be called every 1000ms and so on
  Timer::AddThread(&changeStateLED2, 1000);
  Timer::AddThread(&changeStateLED3, 2000);
  Timer::AddThread(&changeStateLED4, 4000);
  //Start tasks to run in specified time
  Timer::EnableThread(&changeStateLED1);
  Timer::EnableThread(&changeStateLED2);
  Timer::EnableThread(&changeStateLED3);
  Timer::EnableThread(&changeStateLED4);
}

void loop() {
  //The LEDs will flash despite delay
  delay(8000);
  //When they will count 15 in binary one will continue blinking but rest will be in lighting state
  //Due to disabling threads in state when LED's were set to HIGH state
  Timer::DisableThread(&changeStateLED2);
  Timer::DisableThread(&changeStateLED3);
  Timer::DisableThread(&changeStateLED4);
}
