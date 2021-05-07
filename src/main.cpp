#include <Arduino.h>
#include "sona_rs485.h"

unsigned char data[13];
sona_rs485 sona1(2,9600,5,0x01);
void setup() {
  Serial.begin(9600);
  sona1.init();
}
void loop() {

  static unsigned long last_millis=0;
  static unsigned long command_time=0;
  static bool still_command=false;

  if(millis()-last_millis >= 400 && still_command == false){
    last_millis = millis();
    sona1.send_command(0x01);
    command_time = millis();
    still_command = true;
  }

  if(millis()-command_time >= 200 && still_command == true){
    sona1.get_data(data);
    for(int i = 0;i<13;i++){
      Serial.print(data[i]);
      Serial.print(" ");
    }
    Serial.println();
    still_command = false;
  }

}