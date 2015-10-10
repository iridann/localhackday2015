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
#include <EngduinoMagnetometer.h>
#include <Wire.h>
//

// Fraser
float initialise() {
  float field[3];
  EngduinoButton.waitUntilPressed();
  EngduinoMagnetometer.xyz(field);
  return field[2];  
}

// Janos' methods
void shaking() {
  float acc[3];
  int counter = 0;

  while (true) {
    while (counter < 3) {
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

      if (acc[0] >= 1.5) {
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

// Fraser - Reads the XYZ values and prints them through serial.
int getXYZ(float initz) {
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
  return getChoice(z, initz);
  //Serial.println();
}

// Fraser - Determines if paper (0), scissors(1) or rock(2)
int getChoice(float z, float initz) {
  int init = int(initz);
  int value = int(z);
  if (init > 0) {
    if (value < init + 250) {
      return 0;
    } else if ((value > init + 250) && (value < init + 750)) {
      return 1;
    } else {
      return 2;
    }
  } else {
    if (value > init - 250) {
      return 0;
    } else if ((value > init - 250) && (value < init - 750)) {
      return 1;
    } else {
      return 2;
    }
  }
}

void setup() {
  EngduinoMagnetometer.begin();
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
  float initz = initialise();
  //prepare accelerometer
  shaking();
  
  //get score
  int score = getXYZ(initz);


  //send the shit
  while (true) {
    if (decision == 1337) {
      score_send(score);
    } else {
      score_recv(score);
    }

  }
  delay(500);
}

