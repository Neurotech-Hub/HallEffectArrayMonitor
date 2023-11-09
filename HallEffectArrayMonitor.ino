// by Matt Gaidica, PhD

#include "ADS1X15.h"
#define ADDR_GND 0x48
#define ADDR_VDD 0x49
#define ADDR_SDA 0x4A
#define ADDR_SCL 0x4B

ADS1115 ADS(ADDR_SCL);
ADS1115 ADS2(ADDR_SDA);
const int HALL_EN_GPIO = 13;
float f, adcVals[8];
int i;

void setup() {
  digitalWrite(HALL_EN_GPIO, 1);
  Serial.begin(115200);
  ADS.begin();
  ADS2.begin();
  ADS.setGain(0);
  ADS2.setGain(0);
  f = ADS.toVoltage(1);  // voltage factor
  Serial.println("\n\Initiated...");
}

void loop() {
  for (i = 0; i < 8; i++) {
    if (i < 4) {
      Serial.print(ADS.readADC(i) * f);
    } else {
      Serial.print(ADS2.readADC(i - 4) * f);
    }
    Serial.print("\t");
  }
  Serial.println("");
  // delay(500);
}