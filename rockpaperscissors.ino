extern "C" {
#include "myir.h"
}

//Jaro
#include <EngduinoButton.h>
#include <EngduinoIR.h>
#include <EngduinoLEDs.h>

//Janos & Fraser
#include <EngduinoAccelerometer.h>
#include <Wire.h>

//Janos: method for initializing the rps game,
//e.g. the initial three hand movements
void shaking() {
  int counter = 0;
  float acc[3];

  while (true) {
    while (counter < 3) {
      delay(100);

      EngduinoLEDs.setAll(YELLOW, 1);
      EngduinoAccelerometer.xyz(acc);

      //if we reach enough acceleration when moving from up to down
      if (acc[0] >= 1.2) {
        counter++;
        EngduinoLEDs.setAll(RED, 1);
      }
    }
    //ready
    EngduinoLEDs.setAll(BLUE, 1);
    break;
  }
}

//Fraser - Reads the XYZ values and prints them through serial.
int getXYZ() {
  float field[3];
  //wait with finding the arduino's position until button was pressed
  EngduinoButton.waitUntilPressed();
  EngduinoButton.waitUntilReleased();
  EngduinoAccelerometer.xyz(field);

  //z-axis determines the position with respect to RPS
  float z = field[2];
  return getChoice(z);
}

// Fraser - Determines if paper (0), scissors(1) or rock(2)
int getChoice(float z) {
  float value = z;

  //finely tuned values for engduino orientation
  //when the angle is atleast 45deg, we know that
  //the chosen element has changed
  if (value <= -0.50) {
    return 0;
  } else if ((value < 0.50) && (value > -0.50)) {
    return 1;
  } else if (value >= 0.50) {
    return 2;
  }
}

void setup() {
  //Janos
  EngduinoAccelerometer.begin();

  //Jaro
  EngduinoLEDs.begin();
  EngduinoButton.begin();
  EngduinoIR.begin();
}

void loop() {
  //decide what I want to do
  int decision = select_score_recv();

  //prepare accelerometer
  shaking();

  //get score
  int score = getXYZ();

  //send the score
  while (true) {
    if (decision == 1337) {
      score_send(score);
    } else {
      score_recv(score);
      delay(1000000);
    }
  }
}
