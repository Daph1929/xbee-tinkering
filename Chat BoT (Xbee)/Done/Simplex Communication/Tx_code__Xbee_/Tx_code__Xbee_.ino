#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial zigbeee(10,11);

XBee xbee = XBee();

static uint8_t payload[10];
static uint8_t inByte[10];

XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fd); //SH and SL address of receiver
ZBTxRequest zbTx = ZBTxRequest(addr64, payload,sizeof(payload)); //instance for making the frame
ZBTxStatusResponse txStatus = ZBTxStatusResponse(); //instance for getting the status

void setup() {
  
  Serial.begin(115200);
  zigbeee.begin(9600);
  xbee.setSerial(zigbeee);

  delay(1000);
  
  }

 void loop() {
 boolean data_avai = false;

  int i = 0;
  
//do{
while(Serial.available() > 0){
  
  inByte[i] = Serial.read();  
  //Serial.print("i = ");Serial.print(i);
  //Serial.print("   ");
 // Serial.println(inByte[i],HEX);
 delay(10);
  i++;
  
  }//}while(inByte[i]==13);

  for(int j = 0; j < i; j++  )
   {  
      //Serial.print("j = " );Serial.print(j);
      //Serial.print(" ");
      payload[j] =  inByte[j];
      Serial.print(payload[j] ,HEX);
      Serial.println(" ");
      
       if(j == i-1)
      {  
        data_avai = true;
        Serial.print(" | ");
        Serial.print(j);
        
       }}
  
  

    

 /*  //data_avai = true;
 //payload[0] = ((pin1 << 2) | pin1) & 0x0F;
  //payload [1] = */
if (data_avai == true) 
  {zbTx.setFrameId(5);
  xbee.send(zbTx);
  Serial.print("Packet Sent");
  Serial.println();
  delay(100);}

}
