<<<<<<< HEAD
extern "C" {
	#include <acceleration.h>
}


void loop(){
	return;
}

void setup(){
	acceleration.blink();
	delay(10000);
	return;
}
=======
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
>>>>>>> 0476e9432fa5eb81bcaf4a62957f36268f731f9e
