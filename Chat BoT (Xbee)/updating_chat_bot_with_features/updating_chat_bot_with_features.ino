
    #include <XBee.h>
    
    #include <SoftwareSerial.h>

    SoftwareSerial zigbeee(10,11);

    XBee xbee = XBee();

    static char payload[50];
    
    static char inByte[50];

    XBeeAddress64 addr64 = XBeeAddress64(0,0); //SH and SL address of receiver

    ZBTxRequest zbTx = ZBTxRequest(addr64, payload,sizeof(payload)); //instance for making the frame
    
    ZBTxStatusResponse txStatus = ZBTxStatusResponse(); //instance for getting the status

    XBeeResponse response = XBeeResponse();
    
    // create reusable response objects for responses we expect to handle
    
    ZBRxResponse rx = ZBRxResponse(); 

    FrameIdResponse f =  FrameIdResponse();
    
    uint8_t *a;
    
    char x[50];

    uint8_t add1[7];
    
    void setup() {
      
      Serial.begin(115200);
      zigbeee.begin(9600);
      xbee.setSerial(zigbeee);
    
      delay(1000);
      
      }
    
     void loop() {
    
    Talk_Listen();
    
     
    }

 void Talk_Listen()
  {
     boolean data_avai = false;                                                         //Boolean variable---if Data Available it will become true
    
     int i = 0;
      
    //do{
     while(Serial.available() > 0){
     
      inByte[i] = Serial.read();                                                        //Read Available Serial Data and Stor in an array called inByte[]
      //Serial.print("i = ");Serial.print(i);
      //Serial.print("   ");
      // Serial.println(inByte[i],HEX);+
      delay(10);
      i++;
      
      }//}while(inByte[i]==13);
     if(inByte[0]=='t')                                                                 //if user types in t1/t2/....etc a particular address is chosen accordingly
      {                                                                                 //and message is sent to this particular address
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
    
       /*  //data_avai = true;
     //payload[0] = ((pin1 << 2) | pin1) & 0x0F;
      //payload [1] = */
    if (data_avai == true)                                                                //Once Data available is true send this packet
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

    void poll_reply()
    {xbee.readPacket();
        
       if (xbee.getResponse().isAvailable()) {
          // got something
          
       if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
    
         xbee.getResponse().getZBRxResponse(rx);
         XBeeAddress64 return_address=rx.getRemoteAddress64();
         zbTx.setAddress64(return_address);
        /* int frame_id = f.getFrameId();
         Serial.println("Frame received Id = ");
         Serial.println(frame_id);
         got a zb rx packet*/
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
            
          }
        if(x[10]=='*'/*&&  x[16]=='&' && x[27]=='*'*/){
        
          //Serial.print("I got the request for  address");
          payload[0]=' ';
          zbTx.setFrameId(6);
          xbee.send(zbTx);
          delay(100);

           x[10]=' ';
          //x[16]=' ';
          //x[27]=' '; 

      

          }
          }  } }
    
    memset(payload,0,sizeof(payload));
    
      
      }

