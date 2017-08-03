
    #include <XBee.h>
    #include <SoftwareSerial.h>

    SoftwareSerial zigbee(10,11);
    
    XBee xbee = XBee();
    
    XBeeResponse response = XBeeResponse();  //response object  
    
    
    ZBRxResponse rx = ZBRxResponse();   //instance of ZBRxResponse
    
    
    uint8_t *a;                         //pointer to get starting address of payload
    uint8_t x;                      //array to stor the data gotten from the payload
    int legth;                          //legth varaible to store length of payload
                                        //counter variable

    void setup() {

    Serial.begin(115200);                //Begin serial comm. at 115200 baud rate
    zigbee.begin(9600);                 //(software serial) (Rx = pin 10, Tx = pin 11)
    xbee.setSerial(zigbee);             //void XBee::setSerial(Stream &serial){_serial = &serial;}
   
              }
              

    void loop() {


    
    /*if(zigbee.available() > 0)
    {
       Serial.print(zigbee.read() ,HEX);
       Serial.print(" ");
    }*/
   
    /*xbee.readPacket();                                       //
    
    
    if (xbee.getResponse().isAvailable()) {                   // Data available???
      // got something
      
    
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {    // What type of packet? 
                                                              //Is it a response packet?
    
    xbee.getResponse().getZBRxResponse(rx);                   //get the data into rx

       
    /* // legth = rx.getDataLength();                             //get length of payload
     // Serial.print(legth , DEC);                                     
    //  int i = 0;*/


      /* a = rx.getData();
       x[0] = a[0];
       Serial.print(x[0]);*/
    
    /*for(i = 0; i < ;i++)
    { a = rx.getData();     //getData() give an address...so put it in a pointer (here--> a <--is a pointer)
      x[i]=a[i];
      Serial.print(x[i],HEX);
      Serial.print(" ");}
      i++;
      legth--;
       
     } }*/
       
           
    /* //get the first byte and put it in a variable
       -
     // String hexString[i] = String(x[i], HEX);
     //Serial.print(hexString[i]);
     //Serial.print(b);
     //legth = rx.getDataLength();
     //Serial.print(legth ,HEX);*/
       
       
     /*for (i = 0; i < sizeof(hexString); i += 2) {
        temp[0] = input[i];
        temp[1] = input[i + 1];
        temp[2] = '\0';
        index = atoi(temp);
        c = toascii(index);
        Serial.print(c);
      }*/
    
      
     /* if(Serial.available() > 0){

         char inByte = Serial.read();
         
         Serial.print(inByte);
         Serial.print("");
        }*/
        
        
        /*}}*/
   
       
          
     
        }
       
      
      
