#define ADDRESS 0x4
#include "application.h"
 
void setup() {
  Wire.begin();
}
 
void loop() {
  Wire.requestFrom(ADDRESS, 1);
  uint8_t reading = Wire.read();
  Particle.publish("i2c-status", "light reading: " + String(reading));
 
  delay(10000); // wait 10 seconds for next scan
}