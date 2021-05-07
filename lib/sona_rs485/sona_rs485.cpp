#include "sona_rs485.h"
#include <Arduino.h>

sona_rs485::sona_rs485(int _uart_num,int _baud ,int _cs_pin,int _address){
    uart_num = _uart_num;
    baud = _baud;
    cs_pin = _cs_pin;
    command_data[2] = _address;
}

void sona_rs485::init(){
    if(uart_num == 2){
        Serial2.begin(baud);
    }
    pinMode(cs_pin,OUTPUT);
}

void sona_rs485::send_command(int command){
    digitalWrite(cs_pin,HIGH);
    command_data[3] = command;
    int check = 0;
    for(int j = 0;j<4;j++){
        check += command_data[j];
    }
    command_data[4] = check && 0x00ff;
    for(int i = 0;i<5;i++){
        Serial2.write(command_data[i]);
    }
}

bool sona_rs485::get_data(unsigned char* sona_data_buffer){
    digitalWrite(cs_pin,LOW);
    int sona_data_flag = 0;
    while(Serial2.available()){
        sona_data[sona_data_flag] = Serial2.read();
        if(sona_data_flag == 1 && sona_data[0] != 0x55 && sona_data[1] != 0xAA){
            sona_data_flag = 0;
            break;
        }
        if(sona_data_flag == 12){
            /*int check = 0;
            for(int i=0;i<12;i++){
                check += sona_data[i];
            }
            check = check && 0x00ff;
            if(check != sona_data[12]){
                sona_data_flag = 0;
                break;
            }else{
                for(int i=0;i<13;i++){
                    //Serial.print(sona_data[i]);
                    sona_data_buffer[i] = sona_data[i];
                }
                return true;
            }*/
            for(int i = 0;i<13;i++){
                sona_data_buffer[i] = sona_data[i];
            }
            for(int i = 0;i<13;i++){
                Serial.print(sona_data[i]);
                Serial.print(" ");
            }       
            Serial.println();
            }
        sona_data_flag++;
    }
    return false;
}