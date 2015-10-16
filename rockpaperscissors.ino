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

 /* Fraser - Reads the accelerometer x, y and z axis acceleration 
  *          values after a delay - to allow for discrepancies in
  *          the time period between shaking ending and the player
  *          finalising their choice.
  *
  *          Returns the result of the getChoice() function for the
  *          read z axis acceleration value.
  */
int getXYZ() {
  float field[3];
  // Delay to account for discrepancy between finishing shaking and
  // player finalising choice.
  delay(4000);
  EngduinoAccelerometer.xyz(field);

  // The z axis acceleration value is used to determine the position
  // of the engduino for the purpose of the RPS game.
  float z = field[2];
  return getChoice(z);
}

/* Fraser - Takes the z axis acceleration value passed to it
 *          and determines the player's choice of element from
 *          it, returning an integer value denoting which element
 *          has been selected.
 *
 *          Paper corresponds to 0, Scissors correspond to 1 and
 *          Rock corresponds to 2.
 */
int getChoice(float z) {
  float value = z;

  // Looks at the z axis acceleration value to determine
  // angle of inclination from the rest position. The z
  // values of -0.50 and 0.50 are the values at a 45 degree
  // incline either side of rest (left and right respectively).
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
