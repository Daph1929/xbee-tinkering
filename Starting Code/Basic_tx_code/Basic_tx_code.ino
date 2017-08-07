#include <XBee.h>
#include <SoftwareSerial.h>
/*
This example is for Series 2 XBee
 Sends a ZB TX request with the value of analogRead(pin5) and checks the status response for success
*/
//SoftwareSerial mySerial(10, 11); // RX, TX
XBee xbee = XBee();   // create the XBee object
uint8_t payload[] = { 0 };
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fa);  // SH + SL Address of receiving XBee
ZBTxRequest zbTx = ZBTxRequest(addr64, payload,sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();
int pin1 = 0;
int pin2 = 0;
int pin3 = 0;
int pin4 = 0;
void setup() {
 //mySerial.begin(9600);
  Serial.begin(9600);
  xbee.setSerial(Serial);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  
  delay(5000);
}
void loop() {   
  pin1= digitalRead(A0);
  pin2= digitalRead(A1);
  pin3= digitalRead(A2);
  pin4= digitalRead(A3);
  payload[0]= ((pin4 << 3) | (pin3 << 2) | (pin2 << 1) | pin1) & 0x0F;
  zbTx.setFrameId(5);
  xbee.send(zbTx);
  //while (Serial.available() > 0) {
    //Serial.write(payload[0]);
    delay(10000);
  }
