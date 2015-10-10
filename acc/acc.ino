
#include <EngduinoLEDs.h>
#include <EngduinoAccelerometer.h>
#include <Wire.h>

// Janos' methods 
void shaking(){
	float acc[3];
	int counter = 0;	
	
	while(true){
	
	    while (counter < 4){
			EngduinoLEDs.setAll(YELLOW, 1);
		    EngduinoAccelerometer.xyz(acc);
			Serial.print(" x: ");
			Serial.print(acc[0]);
			Serial.print(" y: ");
			Serial.print(acc[1]);
			Serial.print(" z: ");
			Serial.print(acc[2]);
			Serial.print(" counter: ");
			Serial.print(counter);
			Serial.println();
			
			if(acc[0] >= 1.5)
				{
					counter++;
					EngduinoLEDs.setAll(RED, 1);
				}
			delay(100);
		}
		EngduinoLEDs.setAll(BLUE, 1);
		break;
		
	}
}
/////////////////

void setup(){
	EngduinoLEDs.begin();
	EngduinoAccelerometer.begin();
	Serial.begin(9600);
}

void loop(){
	

}
