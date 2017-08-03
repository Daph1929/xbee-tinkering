 #include <SoftwareSerial.h>

SoftwareSerial RFID(10,11);   //Rx = 10, Tx = 11
SoftwareSerial ESP8266_module (8,9); //Rx = 8, Tx = 9

void setup() {
Serial.begin(9600);  // begin serial communication (at baud rate 9600)
//while (!Serial){
  //exit loop when i enter something through serial monitor
 // }

  RFID.begin(9600);
  ESP8266_module.begin(9600);
}

void loop() {

  RFID.listen(); // LIsten through pins 10 and 11
  //Serial.println("Data from RFID");

  while (Serial.available() > 0){ // check idf anything is available
    
    char inByte = RFID.read(); // read and store what is available at pins 10, and 11
    Serial.print(inByte);
    }
//Serial.println();
  ESP8266_module.listen(); //liten to line 8 and 9
  //Serial.println("Data from ESP8266");

  while(Serial.available() > 0){    //check if data available

    char inByte = ESP8266_module.read();   //read data and store in variable
    Serial.print(inByte);                  //print this data
    
    
    }

   
   while(Serial.available() > 0){
    char inByte = Serial.read();
    Serial.print(inByte);
    
    }
//Serial.println();
}
