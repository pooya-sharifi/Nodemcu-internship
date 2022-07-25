#include <ESP8266WiFi.h>
#include <espnow.h>
uint8_t broadcastAddress[] = {0x44, 0x17, 0x93, 0x16, 0x06, 0xA8};
//to check prevously sent items
char sent_a;
byte sent_b=0;
typedef struct struct_message {
  char a;
  byte b;
} struct_message;

// Create a struct_message called myData
struct_message myData;
struct_message recData;

int incomingByte = 0; // for incoming serial data

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
//on Data Recieve
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&recData, incomingData, sizeof(recData));
  Serial.println(recData.a);
  Serial.println(sent_a);
  Serial.println(sent_b);
  Serial.println(recData.b);
//  if(sent_a==recData.a and sent_b==recData.b){
//    Serial.println("the feed back was correct");
//    }
  if(sent_b==recData.b){
    Serial.println("the feed back was correct");
    }
  
  
}

void setup() {
  // put your setup code here, to run once:
  // Init Serial Monitor
  Serial.begin(250000);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_register_recv_cb(OnDataRecv);


}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    myData.b=incomingByte;
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    sent_b=myData.b;
    }
}
