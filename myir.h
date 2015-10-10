#pragma once

#ifndef MYIR_h
#define MYIR_h

#define IRBUFSZ 1

#include <EngduinoIR.h>
#include <EngduinoLEDs.h> 
#include <EngduinoButton.h>

int count = 0;

//begin the handshake
void handshake_begin() {
  EngduinoIR.send('H'); 
}

//end the handshake
int handshake_end() {
  uint8_t buf[IRBUFSZ];
  
  int len = EngduinoIR.recv(buf);
  if (buf[0] == 'H') { 
    EngduinoLEDs.setAll(BLUE);
  }
  return (len > 0 && buf[0] == 'H');
}

void select_role() {
  unsigned long st = millis();
  //while not 5s have elapsed
  while ((millis() - st) < 5000) {
    if (EngduinoButton.isPressed()) {
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

void score_send() {
  //variable to 
  EngduinoIR.send('H');   
}

#endif
