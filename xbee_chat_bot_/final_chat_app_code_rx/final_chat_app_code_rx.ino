#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial zigbee(10,11);
XBee xbee = XBee();

static char payload[10];
static char inByte[10];

XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
ZBRxResponse rx = ZBRxResponse();
XBeeAddress64 addr64 = XBeeAddress64(0, 0);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload,sizeof(payload));
uint8_t *a;
char x[10];
int legth;
void setup() {
  Serial.begin(115200);
  zigbee.begin(9600);
 xbee.setSerial(zigbee);

//  pinMode(13,OUTPUT);
//  pinMode(12,OUTPUT);
}

void loop() {

 /*if(zigbee.available() > 0)
        {
          Serial.print(zigbee.read() ,HEX);
          Serial.println();
          }*/
  
 xbee.readPacket();
    
   if (xbee.getResponse().isAvailable()) {
      // got something
      
   if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {

     xbee.getResponse().getZBRxResponse(rx);
     XBeeAddress64 return_address=rx.getRemoteAddress64();
     zbTx.setAddress64(return_address);
        // got a zb rx packet
  
    a = rx.getData();     //getData() give an address...so put it in a pointer (here--> a <--is a pointer)
    
   for (int i = 0; i < 10 ; i ++)
    {x[i]=a[i];               //get the first byte and put it in a variable
    Serial.print(x[i]);
    Serial.print("");}
    
}}


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
if(inByte[0]=='t')
  {
   char ax = inByte[1];
   if(ax=='1'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fa);zbTx.setAddress64(addr64);Serial.print("you are now in conversation with xbee 1");}
   if(ax=='2'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fd);zbTx.setAddress64(addr64);Serial.print("you are now in conversation with xbee 2");}
   if(ax=='3'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fa);zbTx.setAddress64(addr64 );Serial.print("you are now in conversation with xbee 3");}
   if(ax=='4'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fa);zbTx.setAddress64(addr64 );Serial.print("you are now in conversation with xbee 4");}
    
   inByte[0]='x';
   
   }
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

 if (data_avai == true) 
  {zbTx.setFrameId(5);
  xbee.send(zbTx);
  Serial.print("Packet Sent");
  Serial.println();
  delay(100);}

     }
