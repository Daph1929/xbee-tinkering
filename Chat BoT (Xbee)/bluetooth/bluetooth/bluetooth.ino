    #include <XBee.h>                                                                 //xbee library found on github
    
    #include <SoftwareSerial.h>                                                       //Software serial library to have more than one tx and rx pins

    SoftwareSerial zigbeee(10,11);                                                    // Rx = 10, Tx = 11; (cotroller has t o talk to xbee and serially send data to the screen for chat

    XBee xbee = XBee();                                                               //Instance of xbee

    static char payload[50];                                                          //Array for storing payload data to be sent
    
    static char inByte[50];                                                           //Array for Storing in Data Available Serially

    static char addresses[10][4];                                                 // to store lsb addresses of Routers

    XBeeAddress64 addr64 = XBeeAddress64(0,0);                                       //SH and SL address of receiver

    ZBTxRequest zbTx = ZBTxRequest(addr64, payload,sizeof(payload));                  //instance for making the frame
    
    ZBTxStatusResponse txStatus = ZBTxStatusResponse();                              //instance for getting the status

    XBeeResponse response = XBeeResponse();                                           // create reusable response objects for responses we expect to handle
    
    ZBRxResponse rx = ZBRxResponse();                                                //Instance for response

    // FrameIdResponse f =  FrameIdResponse();

    uint8_t *pointer ;                                                                //pointer to go through the addresses
    
    uint8_t *a;                                                                      // Pointer to store starting address of Payload
    
    char x[50];                                                                       //Array to store Received Data

    uint8_t add1[7];                                                                   //Array to store and read return address

    const long interval = 120000;                                                       //Coodinator Polling Interval

    unsigned long previousMillis = 0;                                                 //Variable to store previously Polled Time

    boolean polled_at_setup = false;
    
    void setup() {
      
      Serial.begin(115200);                                                           //Its important to set Serial Baud Rate different from zigbee baud rate
      zigbeee.begin(9600);
      xbee.setSerial(zigbeee);                                                        //Setting which Serial port should xbee communicate with
     
      delay(1000);
      
      }
    
     void loop() {

      Talk_Listen();
     
     }


  void Talk_Listen()
  {
     boolean data_avai = false;                                                        
    
     int i = 0;
      
    
     while(Serial.available() > 0){
     
      inByte[i] = Serial.read();                                                       
      //Serial.print("i = ");Serial.print(i);
      //Serial.print("   ");
      // Serial.println(inByte[i],HEX);+
      delay(10);
      i++;
      
      }
     if(inByte[0]=='t')                                                                 
      {                                                                               
       char ax = inByte[1];
       if(ax=='1'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fa);zbTx.setAddress64(addr64);Serial.print("you are now in conversation with xbee 1");}
       if(ax=='2'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fd);zbTx.setAddress64(addr64);Serial.print("you are now in conversation with xbee 2");}
       if(ax=='3'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x41565710);zbTx.setAddress64(addr64);Serial.print("you are now in conversation with xbee 3");}
       if(ax=='4'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x4156583E);zbTx.setAddress64(addr64);Serial.print("you are now in conversation with xbee 4");}
       if(ax=='5'){ XBeeAddress64 addr64 = XBeeAddress64(0xFFFFFFFF, 0xFFFFFFFF);zbTx.setAddress64(addr64);Serial.print("you are now in conversation with everyone");} 
       inByte[0]='d';                                                                   //If inByte[0] valuse isnt changed inside this loop, this loop will keep  running 
       //inByte[1]=' ';                                                                   //till user types somehting
       }
       
     for(int j = 0; j < i; j++  )                                                       //Storing available data in Payload
       {  
          //Serial.print("j = " );Serial.print(j);
          //Serial.print(" ");
          payload[j] =  inByte[j];
          Serial.print(payload[j]);
          Serial.print("");
          
           if(j == i-1)                                                                 //Once data s stored make data available true
          {  
            data_avai = true;
            Serial.print("----------Message sent----");
            Serial.print(j);
            Serial.print("----");
            Serial.println();
            Serial.println();
            
        }}  
    
     
    if (data_avai == true)                                                               
      {zbTx.setFrameId(5);
      xbee.send(zbTx);
      delay(100);}

    xbee.readPacket();
        
       if (xbee.getResponse().isAvailable()) {
          // got something
          
       if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
    
         xbee.getResponse().getZBRxResponse(rx);
         XBeeAddress64 return_address=rx.getRemoteAddress64();
         zbTx.setAddress64(return_address);
           /* // got a zb rx packet*/
         //zbTx.getAddress64();
        //Serial.print(y);
        for (int j = 1; j < 9 ;j++)
        { 
          add1[j]= return_address>>(64-(8*j));
          /*Serial.print(add[j],HEX);
          Serial.print(" ");*/
          }
        if(add1[7]==86)
        {
         if(add1[8]==250){Serial.print("Xbee 1:--");}
         if(add1[8]==253){Serial.print("Xbee 2:--");} 
          
         }
        if(add1[7]==87){Serial.print("Xbee 3:--");}
        if(add1[7]==88){Serial.print("Xbee 4:--");} 
         
        
        a = rx.getData();     //getData() give an address...so put it in a pointer (here--> a <--is a pointer)
        
       for (int i = 0; i < 49 ; i++)
        {x[i]=a[i];               //get the first byte and put it in a variable
        Serial.print(x[i]);
        Serial.print("");
       if(i==48)
          {  
            
            Serial.print("----------- Message Received-----");
            Serial.println();
            
          }}  

        

          
    }}
    
    memset(payload,0,sizeof(payload));
    
    
    
    }

  
