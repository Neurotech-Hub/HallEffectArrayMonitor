// by Matt Gaidica, PhD

#include "ADS1X15.h"

#define ADDR_GND 0x48
#define ADDR_VDD 0x49
#define ADDR_SDA 0x4A
#define ADDR_SCL 0x4B

ADS1115 ADS(ADDR_SCL);
ADS1115 ADS2(ADDR_SDA);
const int HALL_EN_GPIO = 5;
float f, adcVals[8];
int i;

void setup() {
  digitalWrite(HALL_EN_GPIO, HIGH);
  Serial.begin(115200);
  while (!Serial) {
    ;  // Wait for the serial port to connect. Needed for native USB port only
  }
  Wire.begin();
  Serial.println("Load enabled");
  ADS.begin();
  // ADS.setWireClock(50000);
  // Wire.setClock(50000); // Set I2C frequency to 50 kHz

  ADS.setGain(0);
  ADS.setDataRate(7);  //  0 = slow   4 = medium   7 = fast

  ADS2.begin();
  // ADS2.setWireClock(50000);
  ADS2.setGain(0);
  ADS2.setDataRate(7);  //  0 = slow   4 = medium   7 = fast

  f = ADS.toVoltage(1);  // voltage factor
  while(!ADS.isReady() || !ADS2.isReady()) {
    Serial.println("Blocks not ready");
    delay(1000);
  }
  Serial.println("Initiated...");
}

void loop() {
  for (i = 0; i < 8; i++) {
    if (i < 4) {
      Serial.print(ADS.readADC(i) * f, 4);
    } else {
      Serial.print(ADS2.readADC(i - 4) * f, 4);
    }
    if (i < 7) {
      Serial.print("\t");
    }
  }
  Serial.println("");
  // delay(500);
}