// by Matt Gaidica, PhD

#include "ADS1X15.h"

ADS1115 ADS(0x48);


void setup() 
{
  Serial.begin(115200);
  ADS.begin();
  Serial.println("\n\nHello, Hall.");
}

void loop() 
{
  // Read input from the Serial Monitor
  if (Serial.available()) {
    char incomingChar = Serial.read();
    
    if (incomingChar == '\n') {
      // Process the data after receiving a newline character
      processReceivedData();
    }
    if (incomingChar == 'r') {
      Serial.println("--RESET\n\n");
    }
  }
}

void processReceivedData() {
  ADS.setGain(1);

  int16_t val_0 = ADS.readADC(0);  
  int16_t val_1 = ADS.readADC(1);  
  int16_t val_2 = ADS.readADC(2);  

  float f = ADS.toVoltage(1);  // voltage factor

  Serial.print(val_0 * f, 3); Serial.print('\t');
  Serial.print(val_1 * f, 3); Serial.print('\t');
  Serial.print(val_2 * f, 3); Serial.println();
}