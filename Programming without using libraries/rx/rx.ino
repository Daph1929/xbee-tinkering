#include <SoftwareSerial.h>

SoftwareSerial zigbee(10,11);

uint8_t inByte[20];

int m = 0;

void setup() {
  
  Serial.begin(115200);
  zigbee.begin(9600);
 
  
}

void loop() {


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
