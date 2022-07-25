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

//led port
int led = 15;
int flag_start = 1;
char a_start;
byte b_start;
int count=0;
uint8_t broadcastAddress[] = {0x44, 0x17, 0x93, 0x16, 0x06, 0xA8};
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a;
    byte b;
} struct_message;

// Create a struct_message called myData
struct_message myData;
//
struct_message recData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  
  if(flag_start){
    a_start=myData.a;
    b_start=myData.b;
    flag_start=0;
  }
//  Serial.print("Bytes received: ");
//  Serial.println(len);
//  Serial.print("string: ");
//  Serial.println(myData.a);
//  Serial.println(myData.b);
//  Serial.println();
//  Serial.println("bbb");
//  Serial.println( TYPE_NAME(myData.a) );
    if(myData.a!=a_start){
      Serial.println("error");
      Serial.println("recieved");
      Serial.println(myData.a);
      Serial.println("should have been");
      Serial.println(a_start);
    }
    if(myData.b!=b_start){
      Serial.println("error");
      Serial.println("recieved");
      Serial.println(myData.b);
      Serial.println("should have been");
      Serial.println(b_start);
    }
   //feedback
   recData.a=myData.a;
   recData.b=myData.b;
   esp_now_send(broadcastAddress, (uint8_t *) &recData, sizeof(recData));
   //
    a_start=a_start+1;
    b_start=b_start+1;
    if(a_start=='z'){
          
          a_start='a';
          }
    if(b_start==256){
          b_start=1;
       }
    Serial.println("loop");
    Serial.println(count);
    count=count+1;
//  if(myData.a=="turn_on"){
//    Serial.println("turn_on");
//    Serial.println("ghataan oomade too if");
//    digitalWrite(led, HIGH);
//  }
//  if(String(myData.a)=="turn_on"){
//    Serial.println("turn_on");
//    Serial.println("ghataan oomade too if,dovomi");
//    digitalWrite(led, HIGH);
//  }
//  if(String(myData.a)=="turn_off"){
//    Serial.println("turn_off");
//    digitalWrite(led, LOW);
//  }
//  Serial.println("oomad ta tah");
//  Serial.println("mydata start:" + myData.a + "Mydata Ends");
//  Serial.println(myData.a=="turn_on");
//  Serial.println(String(myData.a)=="turn_on");
//  Serial.println(String(myData.a)=="turn_on\n\n");
//  Serial.println(myData.a=="turn_on\n\n");
//  Serial.println(myData.a=="turn_on\n\n\n");
//  Serial.println(myData.a=="turn_on\n");
//  Serial.println(String(myData.a)=="turn_on\n");
}
//call back func
//
//
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
//
//
void setup() {
  // put your setup code here, to run once:
  // Initialize Serial Monitor
  pinMode(15, OUTPUT);
  Serial.begin(115200);

  
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // put your main code here, to run repeatedly:

}
}
