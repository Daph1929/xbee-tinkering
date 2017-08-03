
#include <XBee.h>

XBee xbee = XBee();

uint8_t payload[] = { 0, 0 };
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656FD');
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

int payload[] = {0,0,0}
void setup() {
  Serial.begin(9600);
  xbee.setSerial(Serial);
}

void loop() {
  zbTx.setFrameId(5)
  payload[0] = 0x0F;
  payload[1] = 0x0D;
  xbee.send(zbTx);

   
  
}
