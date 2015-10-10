/*#include "myir.h"

#include <EngduinoIR.h>
#include <EngduinoButton.h>

void select_role() {
  int count = 0;

  unsigned long st = millis();
  //while not 5s have elapsed
  while ((millis() - st) < 5000) {
    if (EngduinoButton.isPressed()) {
      count++; 
    }
  }
}

void handshake_begin() {
  EngduinoIR.send('H'); 
}

int handshake_end() {
  uint8_t buf[IRBUFSZ];
  
  int len = EngduinoIR.recv(buf); 
  return (len > 0 && buf[0] == 'H');
}*/
