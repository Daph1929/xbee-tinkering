#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial zigbeee(10,11);

XBee xbee = XBee();

static char payload[10];
static char inByte[10];

XBeeAddress64 addr64 = XBeeAddress64( 0x0013a200, 0x415656fa); //SH and SL address of receiver
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
      Serial.print(payload[j]);
      Serial.print("");
      
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

 /*int dec_to_hex(int a)
 {
  long dec , quotient, remainder;
  int i,j =0;
  char hex[5];
  quotient = a;
  while(quotient!=0)
  {
    remainder = quotient % 16;
    if (remainder < 10)
        hex[j++] = 48 +remainder;
    else
        hex[j++]=  55 + remainder;
    
    
    quotient = quotient /16;
     for (i = j ; i >= 0 ; i--)
    { return(hex[i]);  } 
    
    }*/
  
  

