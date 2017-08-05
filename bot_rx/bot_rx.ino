
#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial zigbee(10,11);
XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
ZBRxResponse rx = ZBRxResponse();
uint8_t *a;
uint8_t x;
int legth;

void setup() {
  Serial.begin(115200);
  zigbee.begin(9600);
 xbee.setSerial(zigbee); 

//  pinMode(13,OUTPUT);
//  pinMode(12,OUTPUT);
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
       x=a[0];
                             //get the first byte and put it in a variable
      
        
}}}
 
      
      
