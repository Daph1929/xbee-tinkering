#include <XBee.h>
#include <SoftwareSerial.h>
SoftwareSerial zigbee(10,11);
XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
ZBRxResponse rx = ZBRxResponse();
uint8_t *a;
uint8_t x;
int len;
int r=0,l=0,m=0;
void setup() {
 Serial.begin(9600);
 zigbee.begin(9600);
xbee.setSerial(zigbee);
}
void loop() {
  xbee.readPacket();
   
   if (xbee.getResponse().isAvailable()) {
     // got something
     
     if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
     xbee.getResponse().getZBRxResponse(rx);
      /* if(zigbee.available() > 0)
       {
         Serial.print(zigbee.read() ,HEX);
         Serial.println();
         } */
       // got a zb rx packet
      a = rx.getData();     //getData() give an address...so put it in a pointer (here--> a <--is a pointer)
      x=a[0];               //get the first byte and put it in a variable
      Serial.print(x ,HEX);  //print whole byte
      Serial.println();
      
     r=x & 0x01;    //extract data
     m=(x & 0x02) >> 1;
     l=(x & 0x04) >> 2;
     if(r)
     Serial.print("r\n");
     if(m)
     Serial.print("m\n");
     if(l)
     Serial.print("l\n");
      
}}
     if(Serial.available() > 0){
        char inByte = Serial.read();
       
        Serial.print(inByte);
        Serial.println();
       }
         
     
     }

