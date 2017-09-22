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

     //Setup_Poll();

     //midTime_Poll();
     Talk_Listen();
     
     }


//////////////////////////////////////////////////////////////////////////////////

/*
Making function for data base kind of stuff

void add_database_update(){
int count = 0; 
String lsb_address; 
   if(ax=='count'){ 
              XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, lsb_address);
              zbTx.setAddress64(addr64);
              Serial.print("you are now in conversation with xbee"); Serial.print(count);}
              count++;
  
  }



*/


void Setup_Poll()
{
   if(polled_at_setup==false)
      { 
        Serial.print("Coodinator Polling   ");
        polled_at_setup = true;
        Serial.print("entered loop");
        int time_length = 10000;
        unsigned long storedMillis = millis();
        Serial.println(storedMillis);
       do
        { 
         
          XBeeAddress64 addr64 = XBeeAddress64(0xFFFFFFFF, 0xFFFFFFFF);
          zbTx.setAddress64(addr64);
          payload[10]= '*';
          zbTx.setFrameId(7);
          xbee.send(zbTx); 
          delay(100);
          xbee.readPacket();                                                     
        
          if (xbee.getResponse().isAvailable()) {
              
              // got something

                
           if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
    
         xbee.getResponse().getZBRxResponse(rx);
         XBeeAddress64 return_address=rx.getRemoteAddress64();
         zbTx.setAddress64(return_address);

         a = rx.getData(); 

         x[1] = a[1];
         Serial.print(x[1]);
           }}
          
          
          }while(millis()-storedMillis<=time_length);
          
          
          
          
          
          Serial.print("Polling Done");

          
         }
  
  
  }

  void midTime_Poll(){
    
      unsigned long currentMillis = millis();                                           //Current Time gotten by fuction called millis()
   
     if(currentMillis - previousMillis >= interval){                                   //check if its time to poll
      
      previousMillis = currentMillis;                                                  //Store polling Time
      Serial.println(currentMillis);
      XBeeAddress64 addr64 = XBeeAddress64(0xFFFFFFFF, 0xFFFFFFFF);                    //Set address for broadcast message
      zbTx.setAddress64(addr64);                                                       //Set the address in the frame
      Serial.println("getting addresses");
      payload[10]= '*';                                                                //Set payload as something identifiable by router in order to reply back on its own
      //payload[16]='&';
      //payload[27]='*';
      zbTx.setFrameId(6);                                                              //Set frame id
      xbee.send(zbTx);                                                                 //Send the packet
      delay(100);}


      xbee.readPacket();                                                     
        
       if (xbee.getResponse().isAvailable()) {
          // got something

                
       if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
    
         xbee.getResponse().getZBRxResponse(rx);
         XBeeAddress64 return_address=rx.getRemoteAddress64();
         zbTx.setAddress64(return_address);
        
               
        a = rx.getData();     //getData() give an address...so put it in a pointer (here--> a <--is a pointer)
        
       for (int i = 0; i < 3 ; i++)
        {x[i]=a[i];               //get the first byte and put it in a variable
         Serial.print(x[i]);
         Serial.print("");
         }
          
        if(x[0]==' '){
        for (int j = 1; j < 9 ;j++)
        { 
          add1[j]= return_address>>(64-(8*j));
          Serial.print(add1[j],HEX);
          Serial.print(" ");
        
        }
          
        uint8_t temp[4];
        for(int j = 0; j < 4; j++)
        {
         temp[j]=add1[5+j];
         Serial.print(temp[j],HEX);
         Serial.print(" ");
         
         }memset(addresses,0,sizeof(addresses));

       
        for(int n = 0; n<10; n++){
        for(int m = 0; m<4; m++)
       { 
         
         addresses[n][m]=temp[m];
         Serial.println(); 
         Serial.print(n);
         Serial.print(" ");
         Serial.print(addresses[n][m],HEX);
         
         
        }
        }
         x[0]='H';
        }
         memset(payload,0,sizeof(payload)); //memset==fastest way to clear an array
        }
        }
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

  
