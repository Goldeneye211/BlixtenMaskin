#include <Servo.h>

#define trigPinR 12
#define trigPinL 10
#define echoR 11
#define echoL 9

#define irL A0 
#define irR A1 

int powwa = 255;
int enA = 8;
int in1 = 7;
int in2 = 6;

int in3 = 5;
int in4 = 4;
int enB = 3;
int servo = 2;

long duration;
int distance;

int slowTurn = 15;
int fastTurn = 5;

Servo styrServo;
int offset = -18;
int pos = 90+offset;   //KOLLA
int minV = 0;
int maxV = 180;


bool turned = false;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(irR, INPUT);
  pinMode(irL, INPUT);

  pinMode(trigPinR, OUTPUT);
  pinMode(trigPinL, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoR, INPUT); // Sets the echoPin as an INPUT
  pinMode(echoL, INPUT);
  
  styrServo.attach(servo);
  styrServo.write(pos);
  
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed

  analogWrite(enA, powwa);
  analogWrite(enB, powwa);

  delay(5000);
  
  straightAhead();
  
}
void loop() {
  
 // int distanceR = distCalc(true);
  int distanceL = distCalc(false);

  bool leftIR = digitalRead(irL);
  bool rightIR = digitalRead(irR);


  if(distanceL<30 and turned!=true){
    turned = turner();
  }
  else if(turned and distance>15){
    straightAhead(); 
   }
  else{
    stopp();
    delay(10000);
  }
  
}

bool turner(){

  lowRight(); 
  delay(1500);    //Svänga höger
  straightAhead();
  delay(1500);  //
  lowLeft();
  delay(1500);  //
  straightAhead();
  delay(1500);  //
  lowRight();
  delay(1500);  //
  straightAhead();
  delay(2000);  //
  stopp();
  delay(1000);  //Stopp vid linje
  
  return true;
}

void resetSteering(){
  analogWrite(enA, powwa);
  analogWrite(enB, powwa);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void stopp(){
  analogWrite(enA, 0);
  analogWrite(enB, 0);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
}

void straightAhead(){
  //resetSteering();

  analogWrite(enA,powwa);
  analogWrite(enB,powwa);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  styrServo.write(pos);
}

void lowLeft(){
  analogWrite(enA, powwa/2);

  styrServo.write(maxV-(pos/2));
}

void turnLeft(){
  resetSteering();

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  styrServo.write(maxV);
}

void lowRight(){
    analogWrite(enB, powwa*0.75);
    
    styrServo.write(minV+(pos/2));
}
void turnRight(){
  resetSteering();

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  styrServo.write(minV);
  
}

int distCalc(bool TF){ 
// Clears the trigPin condition
  if(TF){
    digitalWrite(trigPinR, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinR,LOW);
    duration =pulseIn(echoR, HIGH);
    
  }
  else{
    digitalWrite(trigPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinL,LOW);
    duration =pulseIn(echoL, HIGH);
  }
  //digitalWrite(trigPin, LOW);
  //delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  //digitalWrite(trigPin, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  //if(TF){
  //  duration = pulseIn(echoR, HIGH);
  //}
  //else{
  //  duration = pulseIn(echoL, HIGH);
  //}

  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");

  return distance;
    
}
