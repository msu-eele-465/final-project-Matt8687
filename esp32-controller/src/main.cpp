#include <Arduino.h>
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
}
 
void loop() {
  byte error, address;
  byte data[] = {"THow is you Matt"};
  int nDevices;
  address = 0x40;
  Serial.println("Sending LCD Data");
  Wire.beginTransmission(address);
  Wire.write(data, 16);
  error = Wire.endTransmission();
  if (error == 0) {
    Serial.println("Unable to write to 0x40");
  }
  sleep(1);
}