#pragma once

#ifndef MYIR_h
#define MYIR_h

#define IRBUFSZ 1

#include <EngduinoIR.h>
#include <EngduinoLEDs.h>
#include <EngduinoButton.h>

int RECV = 0;
int count = 0;

int pink[3] = {255, 105, 180};

void rdy() {
  EngduinoLEDs.setAll(GREEN);
  delay(1500);
  EngduinoLEDs.setAll(OFF);
}

//begin the handshake
void handshake_begin() {
  EngduinoLEDs.setLED(2, GREEN, 5);
  unsigned long int k = millis();
  while (millis() - k < 7500) {
    EngduinoIR.send('H');
  }

  EngduinoLEDs.setAll(pink[0], pink[1], pink[2]);
}

//end the handshake
int handshake_end() {
  EngduinoLEDs.setLED(4, RED, 5);
  uint8_t buf[IRBUFSZ];
  int len = 0;

  while (!RECV) {
    len = EngduinoIR.recv(buf);

    if (len > 0) {
      EngduinoLEDs.setLED(4, RED, 5);
      
      RECV = 1;
    }

    if (buf[0] == 'H') {
      EngduinoLEDs.setAll(YELLOW);
    }
  }
  EngduinoLEDs.setAll(pink[0], pink[1], pink[2]);

  return (len > 0 && buf[0] == 'H');
}

void select_role() {
  unsigned long st = millis();
  //while not 5s have elapsed
  while ((millis() - st) < 5000) {
    if (EngduinoButton.wasPressed()) {
      EngduinoLEDs.setLED(count, RED, 3);
      count++;
    }
  }

  //if I press button once, I want to send
  if (count == 1) {
    handshake_begin();
  } else {
    handshake_end();
  }
}

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
    
    if (len > 0) {

      // buf[0] is the result of the enemy
      // choice is my result
      //if(buf[0] == choice){
        //EngduinoLEDs.setAll(YELLOW);
        //return;
      //}

      Serial.print("enemy: ");
      Serial.print(buf[0]);
      Serial.println();
      Serial.print("me: ");
      Serial.print(choice);
      Serial.println();

      switch(buf[0]){
        case 0: 
          if(choice == 1)
            EngduinoLEDs.setAll(GREEN);
          else
            EngduinoLEDs.setAll(RED);
          break;

        case 1:
          if(choice == 0)
            EngduinoLEDs.setAll(RED);
          else
            EngduinoLEDs.setAll(GREEN);
          break;

        case 2:
          if(choice == 0)
            EngduinoLEDs.setAll(GREEN);
          else
            EngduinoLEDs.setAll(RED);
          break;


      }
      
      RECV = 0;
      return;



      //EngduinoLEDs.setAll(pink[0], pink[1], pink[2]); 
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
