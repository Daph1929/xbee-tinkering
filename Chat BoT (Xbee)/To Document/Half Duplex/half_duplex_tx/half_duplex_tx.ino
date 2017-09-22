#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial zigbeee(10,11);

XBee xbee = XBee();

static char payload[50];
static char inByte[50];

XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fd); //SH and SL address of receiver
ZBTxRequest zbTx = ZBTxRequest(addr64, payload,sizeof(payload)); //instance for making the frame
ZBTxStatusResponse txStatus = ZBTxStatusResponse(); //instance for getting the status

XBeeResponse response = XBeeResponse();
    
// create reusable response objects for responses we expect to handle
    
ZBRxResponse rx = ZBRxResponse(); 
    
    uint8_t *a;
    
    char x[50];
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
      
      
       if(j == i-1)
      {  
        data_avai = true;
       Serial.print("----------Message sent----");
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

xbee.readPacket();
    
   if (xbee.getResponse().isAvailable()) {
      // got something
      
   if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {

       xbee.getResponse().getZBRxResponse(rx);
       XBeeAddress64 return_address=rx.getRemoteAddress64();
       zbTx.setAddress64(return_address);
     
       Serial.println("---------------Message Received---------------");
       Serial.println(" ");

        // got a zb rx packet
  
        a = rx.getData();     //getData() give an address...so put it in a pointer (here--> a <--is a pointer)
    
   for (int i = 0; i < 50 ; i ++)
      {
        x[i]=a[i];               //get the first byte and put it in a variable
        Serial.print(x[i]);
        
      }
    }
   }


memset(payload,0,sizeof(payload));
}
