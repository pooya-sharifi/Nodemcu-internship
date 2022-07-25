unsigned long lastTime = 0;  
unsigned long timerDelay = 5;  // send readings timer

int incomingByte = 0; // for incoming serial data
byte check=1;           //for error detection
int counter_failure=0; //amount of time our communication has failed
int count=1;
//for checking the delay
unsigned long time_start,time_end;

typedef struct struct_message {
    char a;
    byte b;
} struct_message;

// Create a struct_message called myData
struct_message myData;


void setup() {
  // put your setup code here, to run once:
  Serial3.begin(250000);
  Serial2.begin(250000);
  Serial.begin(250000);
  myData.a='a';
  myData.b=1;
}

void loop() {
  // put your main code here, to run repeatedly:
  
    if ((millis() - lastTime) > timerDelay) {
    // Set values to send
//    strcpy(myData.a, "THIS IS A CHAR");
       
       // Send message via ESP-NOW
//       Serial.println("miresim inja");
//       esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
//      if( Serial.availableForWrite()){
//      Serial.println("Sending:");
//      Serial.println(myData.b);
      Serial3.write(myData.b);
      if(myData.b==3){
        
        time_start = micros();
        }
      
//    Serial3.print(myData.b);
//     Serial3.println((char)myData.a);
//    }
//       sent_a=myData.a;
//       sent_b=myData.b;
        
       myData.a=myData.a+1;
       myData.b=myData.b+1;
       if(myData.a=='z'){
          
          myData.a='a';
          }
    if(myData.b==256){
          myData.b=1;
       }
//       delay(50);
    
   

    lastTime = millis();
    
     }
     if(Serial2.available() > 0){
    incomingByte = Serial2.read();
    if(incomingByte==3){
        
        time_end = micros();
        Serial.println(time_start-time_end);
        }
//    Serial.println("Recieved");
//    Serial.println(incomingByte);
//    check=myData.b;
//    Serial.println("check:");
//    Serial.println(check);
//    Serial.println(incomingByte);
    
    if(incomingByte==check){
//        Serial.println("Success");
//        Serial.println("number of fails");
//        Serial.println(counter_failure);
        check=check+1;
    
    }
    else{
        Serial.println("Fail");
//        counter_failure=counter_failure+1;
//        Serial.println("number of fails");
//        Serial.println(counter_failure);
       
        check=check+1;
     }

     if(check==255){
    Serial.println(count);
//    Serial.println("***********************");
    count=count+1;
    }
 
  }

  
  }
