
#include <SoftwareSerial.h>

SoftwareSerial zigbee(10,11);

#define Start_Byte 0x7E

uint8_t frame[] = {0x7E, 0x00, 0x0F, 0x10, 0x01, 0x00, 0x7D, 0x33, 0xA2, 0x00, 0x41, 0x56, 0x58, 0x3E, 0xFF, 0xFE, 0x00, 0x00, 0x64, 0xAB};

boolean sendf = false;

uint8_t inByte[20];

int m = 0;

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
  for(int i = 0; i<21; i++)
  {
    
    zigbee.write(frame[i]);
    Serial.print(frame[i],HEX);
    Serial.print(" ");
    
    }
    sendf=false;
}

int i = 0;
while(zigbee.available()>0)

{ 
  inByte[i] = zigbee.read();
  Serial.print(inByte[i],HEX);
  Serial.print(" ");
  m = i;
  i++;

  
    } 
  

boolean frame_interpret = false;
while(Serial.available()>0)
{ 
 
  char input = Serial.read();
  Serial.println(input);
  if(input=='f')
  {
    frame_interpret = true;
    
    }
 
  }
 if(frame_interpret == true)
 { Serial.println();
  Serial.print("No of Bytes = ");
  Serial.print(i);
  Serial.println();
  Serial.print("Start Byte = ");
  Serial.print(inByte[0],HEX);
  Serial.println();
  Serial.print("Length = ");
  Serial.print(inByte[1],HEX);
  Serial.print(inByte[2],HEX);
  Serial.println();
  Serial.print("Frame type: (Receive Packet) : ");
  Serial.print(inByte[3],HEX);
  Serial.println();
  Serial.print("Source Address ");
  
    
  for (int j = 0; j < 8;j++)
  { 
if(j==0)
{
  inByte[5] =inByte[4];
    int x = inByte[6];
    inByte[6]=x-32;
  
  } 
    
    Serial.print(inByte[5+j],HEX);
    Serial.print(" ");
 

    }
  Serial.println();
  Serial.print("Data : ");
 
  for (int j = 16; j< m; j++)
  {
    Serial.print(inByte[j],HEX);
    Serial.print(" ");
    }

  Serial.println();
  Serial.print("Checksum :  ");
  Serial.print(inByte[m],HEX);
  }

}
