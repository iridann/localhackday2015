extern "C"{
  #include "myir.h"
}

#include <EngduinoButton.h>
#include <EngduinoIR.h>
#include <EngduinoLEDs.h> 

void setup() {
  EngduinoButton.begin();
  EngduinoIR.begin();
}

void loop() {
  select_role();
  
  EngduinoLEDs.setAll(BLUE);
  delay(500);
  EngduinoLEDs.setAll(OFF);
}
