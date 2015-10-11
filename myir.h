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

//receive a score
void score_recv(int choice) {
  RECV = 0;

  uint8_t buf[IRBUFSZ];
  int len = 0;

  while (!RECV) {
    len = EngduinoIR.recv(buf);
    
    //if we received any data
    if (len > 0) {
      // buf[0] is the result of the enemy
      // choice is my result
      if(buf[0] == choice){
        EngduinoLEDs.setAll(YELLOW);
        return;
      }

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
      
      delay(100000);
      RECV = 0;
      
      return;
    }
  }
}

int select_score_recv() {
  unsigned long st = millis();
  //while not 5s have elapsed
  while ((millis() - st) < 5000) {
    if (EngduinoButton.wasPressed()) {
      ++count;
      EngduinoLEDs.setLED(count * 2, RED, 3);
    }
  }

  //if I press button once, I want to send
  EngduinoLEDs.setAll(OFF);
  
  if (count == 1) {
    return 1337;
  } else {
    return 42;
  }
}

#endif

