#include<Timer.h>

//Initialization of timer with place for two tasks
Timer timer(2);

//Function to send to SerialMonitor information about being called
void function1() {
  Serial.println("Function - 1");
}

void function2() {
  Serial.println("Function - 2");
  //Remove first function from calling schedule
  timer.RemoveThread(&function1);
  //Add third function to calling schedule, this function will be called every 2000ms
  timer.AddThread(&function3, 2000);
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
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  //Add first and second function to calling schedule
  //Calling interval set to 100ms for function1 and to 1000ms for function2
  timer.AddThread(&function1, 100);
  timer.AddThread(&function2, 1000);
}

void loop() {
  //Timer will check if any of tasks in schedule should be called
  timer.CheckThreads();
  //Function independent from calling by Timer
  function4();
}
