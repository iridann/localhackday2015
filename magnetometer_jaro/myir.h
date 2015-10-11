#pragma once

#ifndef MYIR_h
#define MYIR_h

#define IRBUFSZ 1

#include <EngduinoIR.h>
#include <EngduinoLEDs.h>
#include <EngduinoButton.h>

int count = 0;
int RECV = 0;

//send a score
void score_send(int o_score) {
  while (true) {
    EngduinoIR.send(o_score);
  }
}

//receive a score & evalutate the game
void score_recv(int choice) {
  uint8_t buf[IRBUFSZ];
  int len = 0;

  while (!RECV) {
    len = EngduinoIR.recv(buf);
    
    //if I received something
    if (len > 0) {
      // buf[0] is the result of the enemy
      // choice is my result
      if (buf[0] == choice){
        EngduinoLEDs.setAll(YELLOW);
        return;
      }

      //winning logic
      switch(buf[0]) {
        case 0: 
          if (choice == 1)
            EngduinoLEDs.setAll(GREEN);
          else
            EngduinoLEDs.setAll(RED);
          break;

        case 1:
          if (choice == 0)
            EngduinoLEDs.setAll(RED);
          else
            EngduinoLEDs.setAll(GREEN);
          break;

        case 2:
          if (choice == 0)
            EngduinoLEDs.setAll(GREEN);
          else
            EngduinoLEDs.setAll(RED);
          break;


      }
      RECV = 0;      
      //delay is to be able to demonstrate the game
      //otherwise mainloop `loop()` would be too fast
      //to display the result to others
      delay(100000);
      return;
    }
  }
}

//method to choose which engduino is a receiver / sender
int select_score_recv() {
  unsigned long st = millis();
  //while 5s have NOT elapsed
  while ((millis() - st) < 5000) {
    if (EngduinoButton.wasPressed()) {
      ++count;
      EngduinoLEDs.setLED(count * 2, RED, 3);
    }
  }

  EngduinoLEDs.setAll(OFF);

  //if pressed once, send
  if (count == 1) {
    return 1337;
  } else if (count == 2) {
    return 42;
  }
}

#endif

