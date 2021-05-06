#include <Arduino.h>
#include "sona_rs485.h"

unsigned int data[13];
sona_rs485 sona1(2,9600,4,0x01);
void setup() {
  Serial.begin(9600);
  sona1.init();
}
void loop() {
  sona1.send_command(0x01);
  /*{ 
    delay(1);} while (Serial2.available());*/
  delay(200);
  sona1.get_data(data);

  for(int i = 0;i<13;i++){
    Serial.print(data[i]);
    Serial.print(" ");
  }
  Serial.println();
  delay(100);
}