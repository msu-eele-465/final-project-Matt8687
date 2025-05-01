#include <Arduino.h>
#include <Wire.h>

void clear();
void startTop();

byte error, address;

void setup() {
  Serial.begin(115200);
  Serial.println("Serial Started.");

  Serial.println("Starting I2C Wire...");
  Wire.begin();
  Wire.setClock(800000);
  clear();
  Serial.println("I2C Wire Started.");

}
 
void loop() {
  error = 1;
  byte data[] = "How is you Matt ";
  int nDevices;
  address = 0x40;

  startTop();

  Serial.println("Sending LCD Data");
  Wire.beginTransmission(address);
  Wire.write(data, sizeof(data)-1);
  Serial.println();
  Serial.println(sizeof(data)-1);
  error = Wire.endTransmission();
  if (error == 0) {
    Serial.println("Unable to write to 0x40");
  }
  sleep(3);
}

void clear(){
  address = 0x40;
  Wire.beginTransmission(address);
  for(int i = 0; i<16; i++){
    Wire.write('z');
  }
  Wire.write('H');
  Wire.write('G');
  error = Wire.endTransmission();
}

void startTop(){
  address = 0x40;
  Wire.beginTransmission(address);
  for(int i = 0; i<16; i++){
    Wire.write('z');
  }
  Wire.write('H');
  Wire.write('G');
  Wire.write('T');
  error = Wire.endTransmission();
}