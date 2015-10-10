#include <EngduinoIR.h>

#define IRBUFSZ 1

void handshake_begin() {
  EngduinoIR.send('H'); 
}

bool handshake_end() {
  uint8_t buf[IRBUFSZ];
  
  int len = EngduinoIR.recv(buf);

  /*if (len > 0 && buf[0] == 'H') {
    return true;
  } else {
    return false;
  }*/
  
  return (len > 0 && buf[0] == 'H');
}


void setup() {
  //start the IR
  EngduinoIR.begin();
}

void loop() {
    

}
