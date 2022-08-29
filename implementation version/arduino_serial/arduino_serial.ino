unsigned long lastTime = 0;  
unsigned long timerDelay = 1000;  // send readings timer

int incomingByte = 0; // for incoming serial data
byte check=1;           //for error detection
int counter_failure=0; //amount of time our communication has failed
byte count_send=1;
byte first_byte_recieved=1;
int i=0;
bool flag_start=0;
byte check_byte=0;
//for checking the delay
unsigned long time_start,time_end;
char string_we_send[]="zthis is the data we are sending";
byte start_byte[]={0x55,0x01,0x02};
//byte start_inv[]={0x55,0x01,0x02};



typedef struct struct_message {
    char a[40]="trying to send these byte";
    byte b[100];
    uint32_t check_sum;
} struct_message;

// Create a struct_message called myData
struct_message myData;


void setup() {
  // put your setup code here, to run once:
  Serial3.begin(57600,SERIAL_8E1);
  Serial2.begin(57600,SERIAL_8E1);
  Serial.begin(57600,SERIAL_8E1);

  
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
      
      for(int i=0;i<200;i++){
        myData.b[i]=i;
        
        }
//      Serial.println(myData.a);
//      Serial3.write(myData.a,26);
//      Serial3.write("zthis is the data we are sending");
      Serial3.flush();
      for(int k=0;k<3;k++){
        Serial3.write(start_byte[k]);
//        Serial3.println(start_byte[k]);
        }
   
//     Serial.print(Serial3.available());
//    if(Serial3.available() > 0 ){
//      while(Serial3.available() > 0){
//        Serial.println("oomad tooooo");
//        incomingByte=Serial3.read();
//        if(incomingByte==85){
//          Serial.println("Beginign pf the sentence");
//          }
//          
//        Serial.print("incomingByte :");
//        Serial.print(incomingByte);
//        Serial.print("  ##");
//  //    incomingString=String(incomingByte);
//        if(incomingByte==85){
//          i=0;
//          Serial.println("finding the begining of the message");
//          }
//       
//  //      break;
//      }
//    }
    
      
      Serial3.write(count_send);
      Serial.println("THE OG");
      Serial.println(count_send);
      count_send++;
//      delay(200);
//      Serial3.write(myData.b,200);
//      if(myData.b==3){
//        
//        time_start = micros();
//        }
      
//    Serial3.print(myData.b);
//     Serial3.println((char)myData.a);
//    }
//       sent_a=myData.a;
//       sent_b=myData.b;
        
//       myData.a=myData.a+1;
//       myData.b=myData.b+1;
//       if(myData.a=='z'){
//          
//          myData.a='a';
//          }
//    if(myData.b==256){
//          myData.b=1;
//       }
//       delay(50);
    
   

    lastTime = millis();
     }
     
    if(Serial2.available() > 0){
        incomingByte = Serial2.read();
        Serial.println("ina ro receiver mide");
        Serial.println(incomingByte);
        myData.b[i+2]=incomingByte;
        if(myData.b[2]!=85){
            if(isspace(myData.b[i])){
                Serial.println("Space");
              
              }
              else{
                Serial.println("Space Situation");
//                Serial.println(isspace(myData.a[i]));
//                Serial.println("White Space Situation");
//                Serial.println(isWhitespace(myData.a[i]));
//                Serial.println(myData.a[0]=='z');
//                Serial.println((char)incomingByte=='z');
//                Serial.println("starts off wrong");
//                Serial.println(myData.a[i]);
//                Serial.println(i);
                
                }
                i=-1;
            
          }
         
        i++;
    //    if(incomingByte==3){
    //        
    //        time_end = micros();
    //        Serial.println();
    //        Serial.println(time_start-time_end);
    //        }
    //    Serial.println("Recieved");
    //    Serial.println(incomingByte);
    //    check=myData.b;
    //    Serial.println("check:");
    //    Serial.println(check);
    //    Serial.println(incomingByte);
        
    
      if(i==3){
        
//        Serial.println(Serial.available());
      if(Serial2.available() > 0 ){
          
          Serial.println("if avali");
          incomingByte=Serial2.read();
          myData.b[1]=incomingByte;
          Serial.println(myData.b[1]);
      }
//      else{
//        Serial.println("raft tooye esle");
//        Serial.println(Serial2.available());
//        ///checking
//          do {
//            Serial.println("raft tooye do");
////            Serial.println(Serial2.available());
//            if(Serial2.available() > 0 ){
//            incomingByte=Serial2.read();
//            Serial.println("raft tooye if e do");
//            
//            myData.b[1]=incomingByte;
//            Serial.println(myData.b[1]);
//            break;
//          }
//          
//          } while (Serial2.available() == 0 );
//      
//      }
//       Serial.println(myData.a);
         int flag_fail=0;
//       for(int j=0;j<32;j++){
//        if(myData.a[j]!=string_we_send[j]){
//          flag_fail=1;
//          Serial.println("flag ro 1 kardam");
//          Serial.println(myData.a[j]);
//          Serial.println(string_we_send[j]);
//          }
//        
//        }
        if(flag_fail==1){
          Serial.println("Failll");
          
          }
          else{
//            Serial.println("Sucess");
            }
       if(count_send-1==1){
        flag_start=1;
//        Serial.println("Cheking starts");
        check_byte=0;
        }
       Serial.println("flag_start");
       Serial.println(flag_start);
       if(flag_start==1){
       Serial.println(check_byte);
        check_byte++;
        if(myData.b[1]==check_byte){
//          Serial.println("Success");
//          Serial.println(myData.b[1]);
//          Serial.println(check_byte);
//          Serial.println(count_send-1);
          }
         else{
          
          Serial.println("fail ,diffrent check_byte abd myData b ????????????????");
          Serial.println(myData.b[1]);
          Serial.println(check_byte);
          Serial.println(count_send-1);
          }
        
        
        }

      
            
          i=0;
       }
       
       
      
  }
  }
