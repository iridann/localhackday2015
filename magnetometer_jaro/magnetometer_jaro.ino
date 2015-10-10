extern "C" {
#include "myir.h"
}

//jaro
#include <EngduinoLEDs.h>
#include <EngduinoButton.h>
#include <EngduinoIR.h>
//end jaro

//janos and fraser
#include <EngduinoAccelerometer.h>
#include <Wire.h>
//




// Janos' methods
void shaking() {
  float acc[3];
  int counter = 0;

  while (true) {
    while (counter < 3) {
            delay(100);

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

      if (acc[0] >= 1.2) {
        counter++;
        EngduinoLEDs.setAll(RED, 1);
      }
    }
    EngduinoLEDs.setAll(BLUE, 1);
    break;

  }
}
/////////////////

// Fraser - Reads the XYZ values and prints them through serial.
int getXYZ() {
  delay(1000);
  float field[3];
  EngduinoAccelerometer.xyz(field);

  float x = field[0];
  float y = field[1];
  float z = field[2];
  //Serial.print("x: ");
  //Serial.print(x);
  //Serial.print(", y: ");
  //Serial.print(y);
  //Serial.print(", z: ");
  //Serial.print(z);
  //Serial.print(", choice: ");
  return getChoice(z);
  //Serial.println();
}

// Fraser - Determines if paper (0), scissors(1) or rock(2)
int getChoice(float z) {
  int value = int(z);
  if (value < -0.60) {
    return 0;
  } else if ((value <= 0.60) && (value > -0.60)) {
    return 1;
  } else {
    return 2;
  }
}

void setup() {
  //EngduinoMagnetometer.begin();
  EngduinoIR.begin();

  //jaro
  EngduinoLEDs.begin();
  EngduinoButton.begin();
  
  //janos
  EngduinoAccelerometer.begin();
}

void loop() {
  //decide what I want to do
  int decision = select_score_recv();

  //prepare accelerometer
  shaking();
  
  //get score
  int score = getXYZ();
  Serial.print("my Score: ");
  Serial.print(score);
  Serial.println();


  //send the shit
  while (true) {
    if (decision == 1337) {
      score_send(score);
    } else {
      score_recv(score);
      delay(1000000);
    }

  }
  delay(500);
}


