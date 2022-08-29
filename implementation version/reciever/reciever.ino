/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <CRC32.h>
//led port
int led = 15;
int flag_start = 1;
char a_start;
byte b_start;
int i=0;
int count=0;
byte answer[30];
byte incomingByte=0;
byte start_byte[]={0x55,0x01,0x02};

uint8_t broadcastAddress[] = {0x44, 0x17, 0x93, 0x15, 0xc2, 0xF3};
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[40];
    byte b[100];
    uint32_t check_sum;
} struct_message;

// Create a struct_message called myData
struct_message myData;
//
struct_message recData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));

//  Serial.println("@@");
//  Serial.print(myData.b[1]);
//  Serial.print(myData.b[2]);
//  Serial.print(myData.b[3]);
//  Serial.print(myData.b[4]);
//  Serial.print(myData.b[5]);
//  Serial.print(myData.check_sum);
  CRC32 crc;
//            Serial.println(sizeof(myData));'
  for (size_t i = 2; i < 50; i++)
    {
    crc.update(myData.b[i]);
    }
  uint32_t checksum = crc.finalize();
  myData.check_sum=checksum;
  if(checksum==myData.check_sum){
//    Serial.print("Success");
    }
    else{
    Serial.println("fail on crc");
    Serial.println(checksum);
    Serial.println(myData.check_sum);
    
      }
//  if(flag_start){
//    a_start=myData.a;
//    b_start=myData.b;
//    flag_start=0;
//  }

//    if(myData.a!=a_start){
//      Serial.println("error");
//      Serial.println("recieved");
//      Serial.println(myData.a);
//      Serial.println("should have been");
//      Serial.println(a_start);
//    }
//    Serial.print(myData.b);
//    if(myData.b!=b_start){
//      Serial.println("error");
//      Serial.println("recieved");
//      Serial.println(myData.b);
//      Serial.println("should have been");
//      Serial.println(b_start);
//    }
   //feedback
   recData.b[1]=myData.b[1];
//   Serial.println(recData.b[1]);
   for(int j=0;j<40;j++){
          recData.a[j]=myData.a[j];
          
         }
     recData.check_sum=myData.check_sum;
//   Serial.println("recData.a");
//   Serial.println(recData.a);
   esp_now_send(broadcastAddress, (uint8_t *) &recData, sizeof(recData));
   //
    //writing using serial
//    Serial.write(myData.a);
//    Serial.println();
//    for(int k=2;k<5;k++){
//      for(int k=0;k<3;k++){
////        Serial.write(myData.b[k]);
//          int bytesSent=Serial.write(start_byte[k]);
//          Serial.print(bytesSent);
////          Serial.print(start_byte[k]);
////        Serial.print("minevisim");
////        Serial.print(myData.b[k]);
////        Serial.print("|||");
//        }
     Serial.flush();
//     Serial.print(Serial.availableForWrite());
     if( Serial.availableForWrite()){
     Serial.write(start_byte[0]);
     Serial.write(start_byte[1]);
     Serial.write(start_byte[2]);
//     Serial.print(start_byte[0]);
//     Serial.print(start_byte[1]);
//     Serial.print(start_byte[2]);
//     Serial.println(start_byte[0]);
//     Serial.println(start_byte[1]);
//     Serial.println(start_byte[2]);
     }
//   while(Serial.available()==0){
     for(int i=1;i<200;i++){
//     Serial.print(Serial.available());
    if(Serial.available() > 0 ){
      Serial.println("oomad tooooo");
      incomingByte=Serial.read();
      Serial.print("incomingByte :");
      Serial.print(incomingByte);
      Serial.print("  ##");
//    incomingString=String(incomingByte);
      if(incomingByte==85){
        i=0;
        Serial.println("finding the begining of the message");
        }
      answer[i]=incomingByte;
      i++;
//      break;
    }
    delay(1);
     }
//    }
//    Serial.println();
   //
    a_start=a_start+1;
    b_start=b_start+1;
    if(a_start=='z'){
          
          a_start='a';
          }
    if(b_start==256){
          b_start=1;
       }
//    Serial.println("loop");
//    Serial.println(count);
    count=count+1;

}
//call back func
//
//
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
//  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
//    Serial.println("Delivery success");
  }
  else{
//    Serial.println("Delivery fail");
  }
}
//
//
void setup() {
  // put your setup code here, to run once:
  // Initialize Serial Monitor
  pinMode(15, OUTPUT);
  Serial.begin(57600,SERIAL_8E1);

  
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
//    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_register_recv_cb(OnDataRecv);

   
//  for(int k=0;k<3;k++){
//        Serial.write(start_byte[k]);
//        Serial.println(start_byte[k]);
//        }
//  delay(40);
//     Serial.print(Serial.available());
//    if(Serial.available() > 0 ){
//      incomingByte=Serial.read();
//      Serial.print("incomingByte :");
//      Serial.print(incomingByte);
//      Serial.print("  ##");
////    incomingString=String(incomingByte);
//      if(incomingByte==85){
//        i=0;
//        Serial.println("finding the begining of the message");
//        }
//      answer[i]=incomingByte;
//      i++;
//
//
//    }
}

void loop() {
  // put your main code here, to run repeatedly:


}
