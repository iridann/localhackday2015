#include <EngduinoMagnetometer.h>
#include <Wire.h>

// Fraser - Reads the XYZ values and prints them through serial.
void getXYZ() {
 float field[3];
 EngduinoMagnetometer.xyz(field); 
 
  float x = field[0];
  float y = field[1];
  float z = field[2];
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(", y: ");
  Serial.print(y);
  Serial.print(", z: "); 
  Serial.print(z);
  Serial.print(", choice: ");
  Serial.print(getChoice(z));
  Serial.println();
}

// Fraser - Determines if paper (0), scissors(1) or rock(2)
int getChoice(float z) {
  int value = int(z);
  if (value < 3250) {
      return 0;
  } else if ((value > 3250.0) && (value < 3750.0)) {
      return 1;
  } else {
      return 2;
  }  
}

void setup() {
 EngduinoMagnetometer.begin(); 
}

void loop() {
  getXYZ();
  delay(500);
}


