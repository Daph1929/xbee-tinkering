  #include <SoftwareSerial.h>
  
  SoftwareSerial keypad(10,11); //Rx = 10, Tx = 11
  SoftwareSerial zigbee (8,9);  //Rx = 8 , Tx = 9

  #include <XBee.h>

  XBee xbee = XBee(); //xbee instance


void setup() {

Serial.begin(9600);  //beigin serial communication at baud rate 9600
  
while (!Serial) {
    //wait for serial port to connect.
    
    }
 keypad.begin(9600); 
 zigbee.begin(9600);
 xbee.setSerial(zigbee);   
  
  }

void loop(){

   //by default the last initializd port is listening

   //to listen to a particular port , explicitely select it

   keypad.listen();
   Serial.println("Data from keypad");
   while (keypad.available() > 0)      //checking for incoming bytes of character
   {
    char inByte = keypad.read();       // reading what is available at this port
    Serial.write(inByte);
   
    }

  Serial.println();
  zigbee.listen();
  Serial.println("Data from zigbee");
  while (zigbee.available() > 0 )        //checking for incoming bytes of character
  {
    char inByte = zigbee.read();        // reading what is available at this port
    Serial.write(inByte);              
   }
   Serial.println();

  
  
  }
