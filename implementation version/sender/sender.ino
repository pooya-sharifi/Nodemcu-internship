#include <ESP8266WiFi.h>
#include <espnow.h>
#include <QueueList.h>
#include <CRC32.h>
uint8_t broadcastAddress[] = {0x44, 0x17, 0x93, 0x16, 0x06, 0xA8};
//to check prevously sent items
char sent_a[40];
byte sent_b=0;
typedef struct struct_message {
  char a[40];
  byte b[100];
  uint32_t check_sum;
} struct_message;

int flag_fail=0;

 int i=0;
 int k=0;

uint32_t prev_check_sum;

// Create a struct_message called myData
struct_message myData;
struct_message recData;

bool flag_beg=0;

QueueList <char> queue;

byte incomingByte = 0; // for incoming serial data
String incomingString; // for incoming serial data

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
//  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
//    Serial.println("Delivery success");
    
    if(flag_fail!=0){
//      flag_fail=flag_fail-1;
      flag_fail=0;
      }
     
  }
  else{
    Serial.println("Delivery fail");
    //in ke fail beshe baaz befreste
    flag_fail=flag_fail+1;
//    Serial.println(myData.b,200);
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  }
}




//on Data Recieve
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&recData, incomingData, sizeof(recData));
//  Serial.println("Recieved");
//  Serial.println(recData.a);
//  Serial.println(sent_a);
//  Serial.println(sent_b);
//  Serial.print(recData.check_sum);
  for(int j=0;j<40;j++){
        if(sent_a[j]!=recData.a[j]){
          flag_fail=1;
          Serial.println("flag ro 1 kardam");
          Serial.println(recData.a[j]);
          Serial.println(sent_a[j]);
          }
        
        }
        if(flag_fail==1){
          Serial.println("Failll on content of a");
          
          }
          else{
//            Serial.println("Sucess");
            }
  if(prev_check_sum==recData.check_sum){
    Serial.print("Success");
    
    }
    else{
      Serial.println("fail");
      
      }
  if(flag_fail==0 and sent_b==recData.b[1]){
    Serial.println("the feed back was correct");
    }
//  if(sent_b==recData.b){
//    Serial.println("the feed back was correct");
//    }
  else{
    Serial.println("the feed back was not correct");
    Serial.println();
    Serial.println();
    Serial.println(sent_b);
    Serial.println(recData.b[1]);
  }
  
}

void setup() {
  // put your setup code here, to run once:
  // Init Serial Monitor
  Serial.begin(57600,SERIAL_8E1);
 
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
  
  
  if(Serial.available() > 0 ){
    incomingByte=Serial.read();
    Serial.print("incomingByte");
    Serial.println(incomingByte);
//    incomingString=String(incomingByte);
    if(incomingByte==85){
     i=0;
     Serial.println("finding the begining of the message");
      }
    myData.b[i+2]=incomingByte;
    i++;
//    Serial.println(i);
//    Serial.println(incomingString);
//    Serial.println(myData.a[i-1]);
//    queue.push(incomingByte);

    
//    if(flag_fail==0){
//      myData.b=queue.pop();
//      sent_b=myData.b;
//      esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
//     }
     
    
    }
//    Serial.print("Data a_ghable addad gereftan");
//    Serial.println(myData.a);
    if(i==3){
//      Serial.println(Serial.available());
      if(Serial.available() > 0 ){
          
//          Serial.println("if avali");
          incomingByte=Serial.read();
          myData.b[1]=incomingByte;
//          Serial.println(myData.b[1]);
      }
      else{
//        Serial.println("raft tooye esle");
        Serial.print(Serial.available());
        ///checking

//        if(Serial.available() > 0 ){
//          
////          Serial.println("if avali");
//          incomingByte=Serial.read();
//          myData.b[1]=incomingByte;
////          Serial.println(myData.b[1]);
//          }
//          //juist checking
//          else{
//            if(Serial.available() > 0 ){
//          
////          Serial.println("if avali");
//          incomingByte=Serial.read();
//          myData.b[1]=incomingByte;
////          Serial.println(myData.b[1]);
//          }
          do {
            Serial.print("raft tooye do");
//            Serial.println(Serial.available());
            if(Serial.available() > 0 ){
            incomingByte=Serial.read();
            Serial.print("raft tooye if e do");
            
            myData.b[1]=incomingByte;
            Serial.print(myData.b[1]);
            break;
            }
          
          } while (Serial.available() == 0 );
            
            
          
            
            
          }

        
    
//    Serial.println("after break");
    //just checking//

          for(int j=0;j<32;j++){
          queue.push(myData.a[j]);
          
         }
      
    
    
//     if(flag_fail==0){
//      for(int j=0;j<25;j++){
//        myData.a[j]=queue.pop();
//        
//       }
//            Serial.println("esp_now is going to send");
         for(int j=0;j<40;j++){
          sent_a[j]=myData.a[j];
          
         }
        sent_b=myData.b[1];
     //to see what we are sending
//     for(int j=0;j<32;j++){
//        Serial.print(myData.a[j]);
//       }
//       Serial.println();
//           Serial.println(myData.a);
//           Serial.println(myData.b[1]);
//        for(int j=2;j<50;j++){
//              myData.b[j]=j;
//              
//             }
        CRC32 crc;
//            Serial.println(sizeof(myData));'
        for (size_t i = 2; i < 50; i++)
             {
             crc.update(myData.b[i]);
             } 
        uint32_t checksum = crc.finalize();
        myData.check_sum=checksum;
        prev_check_sum=myData.check_sum;
            esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
           for(int j=0;j<32;j++){
            queue.pop();
           }
           i=0;




    }     
        
//          
//          myData.b[0]=10;
//          myData.a[33]=myData.b[1];
//          myData.a[33]='1';
          //making queue
        
    }
//    }
