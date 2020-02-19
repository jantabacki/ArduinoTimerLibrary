#include<InterruptTimer.h>

//Function to send to SerialMonitor information about being called
void function1() {
  Serial.println("Function - 1");
}

void function2() {
  Serial.println("Function - 2");
  //Remove first function from calling schedule
  Timer::RemoveThread(&function1);
  //Add third function to calling schedule, this function will be called every 2000ms
  Timer::AddThread(&function3, 2000);
  //Enable thread
  Timer::EnableThread(&function3);
}

bool builtInLedState = false;

//Changes state of builtin led
void function3() {
  Serial.println("Function - 3");
  builtInLedState = !builtInLedState;
}

//Independent function called from loop function
void function4() {
  //Report to SerialMonitor state of LED
  Serial.print("Independent thread updating LED state - LED if : ");
  if (builtInLedState) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
  //Update state of LED
  digitalWrite(LED_BUILTIN, builtInLedState);
}

void setup() {
  //Preparing space for two threads in Timer
  Timer::CreateSpace(2);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  //Add first and second function to calling schedule
  //Calling interval set to 100ms for function1 and to 1000ms for function2
  Timer::AddThread(&function1, 100);
  Timer::AddThread(&function2, 800);
  //Enable threads
  Timer::EnableThread(&function1);
  Timer::EnableThread(&function2);
}

void loop() {
  //Function independent from calling by Timer
  function4();
  delay(700);
}
