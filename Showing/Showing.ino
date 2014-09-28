 #include<Servo.h>
#include<CTS.h>
#include<HerkuleX.h>
#include<GPS.h>

#define RX 0
#define TX 1
#define MOTORID 219

void insert(float a);
//void lift(float a);

CTS CTS1;
GPS gpsEx;
Servo Carsteer;
float rsangle = 0;
int motor = 2;
int val = 0;
int data=0;
int center=120;
int preloc = 200;
int sonar1 = 47;
int sonardist1 = 100;
int offset = 0;

void setup(){ 
  delay(3000);
//  Serial.begin(9600);
  HerkuleX.begin(57600, RX, TX);  
  delay(10);
  // Torque ON
  HerkuleX.torqueOn(MOTORID);
  if (HerkuleX.getStatus(MOTORID) != HERKULEX_STATUS_OK) {
    HerkuleX.clear(MOTORID);  // If there is an error dectected, clear it
  }
  HerkuleX.moveAngle(MOTORID, -30, 100, HERKULEX_LED_GREEN | HERKULEX_LED_BLUE | HERKULEX_LED_RED);
  delay(1000);
  
  Serial3.begin(115200);
  Carsteer.attach(3);
  pinMode(2,OUTPUT);
  delay(1000);
  for(int i = 56; i <= 104 ; i++){
    analogWrite(motor, i);
    delay(10);
  }
  analogWrite(motor, 170);
  delay(1000);
  analogWrite(motor, 190);
  delay(1000);
  analogWrite(motor, 181);
  delay(1000);
  
  pinMode(sonar1, INPUT);
}

void loop(){
  if (HerkuleX.getStatus(MOTORID) != HERKULEX_STATUS_OK) {
    HerkuleX.clear(MOTORID);  // If there is an error dectected, clear it
  }
  HerkuleX.moveAngle(MOTORID, 150, 100, HERKULEX_LED_GREEN | HERKULEX_LED_BLUE | HERKULEX_LED_RED);
  delay(1000);
  while(sonardist1>10){
    sonardist1 = gpsEx.liftsonar(sonar1);
    val = CTS1.location();
//    Serial.println(val);
//    if(val!=200){
//      preloc = val;
//    }
//    if(val==200&&preloc!=200){
//      insert(201); 
//    }      
    insert(val);
  }
  if (HerkuleX.getStatus(MOTORID) != HERKULEX_STATUS_OK) {
    HerkuleX.clear(MOTORID);  // If there is an error dectected, clear it
  }
  HerkuleX.moveAngle(MOTORID, -30, 100, HERKULEX_LED_GREEN | HERKULEX_LED_BLUE | HERKULEX_LED_RED);
  delay(100000);
  sonardist1 = 100;
    
}

void insert(float rsangle){
  if(-40<rsangle&&rsangle<40){
    Carsteer.write(90-offset);
    delay(100);
    analogWrite(motor, 188);
    delay(100);
  }
  else if(40<rsangle&&rsangle<120){
    Carsteer.write(70-offset);
    delay(100);
    analogWrite(motor, 175);
    delay(300);
    Carsteer.write(110-offset);
    delay(100); 
    analogWrite(motor, 175);
    delay(300);
    Carsteer.write(90-offset);
    delay(100);
    analogWrite(motor, 188);
    delay(400);
  }
  else if(-120<rsangle&&rsangle<-40){
    Carsteer.write(110-offset);
    delay(100); 
    analogWrite(motor, 175);    
    delay(300);
    Carsteer.write(70-offset);
    delay(100);
    analogWrite(motor, 175);
    delay(300);
    Carsteer.write(90-offset);
    delay(100);
    analogWrite(motor, 188);
    delay(400);    
  }
  else if (rsangle == 200){
    Carsteer.write(90-offset);
    delay(100);
    analogWrite(motor, 181);
    delay(100);
  }
  else{
    Carsteer.write(90-offset);
    delay(100);
    analogWrite(motor, 175);
    delay(100);
  }
}
