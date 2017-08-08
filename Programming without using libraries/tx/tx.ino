
#include <SoftwareSerial.h>

SoftwareSerial zigbee(10,11);

#define Start_Byte 0x7E

uint8_t frame[] = {0x7E, 0x00, 0x0F, 0x10, 0x01, 0x00, 0x7D, 0x33, 0xA2, 0x00, 0x41, 0x56, 0x58, 0x3E, 0xFF, 0xFE, 0x00, 0x00, 0x64, 0xAB};

boolean sendf = false;

void setup() {
  
  Serial.begin(115200);
  zigbee.begin(9600);
  
}

void loop() {

while(Serial.available()>0)

{
  char inByte = Serial.read();
  Serial.print(inByte);
  Serial.print(" ");
  if(inByte=='s'){

    sendf = true;
    
    }  
  
  }


if(sendf==true){
  for(int i = 0; i<20; i++)
  {
    
    zigbee.write(frame[i]);
    Serial.print(frame[i],HEX);
    Serial.print(" ");
    
    }
    sendf=false;
}



}
