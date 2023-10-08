#include<Adafruit_MotorShield.h>
#include <AFMotor.h>
/*
this will state the motor is sync-properly to all movements
install&Include Adafruit Motor Shield V2 Library
*/

// instance for motor var (pin)
AF_DCMotor m3(3);
AF_DCMotor m4(4);

//instance for LED
const int greenLEdPin = ;
const int redLEDPin = ;

String path;

void setup() {
// put your setup code here, to run once:
  
  // Adding LED
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  
  // function for setting up pinmode for Motor from 14 to 20
  for (int i = 14; i<20; i++){
    pinMode(i, INPUT);
  }

  //speed of motor here var(speed in rpm)
  m3.setSpeed(300);
  m4.setSpeed(300);
  m3.run(RELEASE);
  m4.run(RELEASE);
}

void loop() {
  
  //initalise serial monitor
  Serial.begin(9600);
  for(int i=14; i<20; i++)
  {
    Serial.print("Pin");
    Serial.println("i");
    Serial.println(" = ");
    Serial.println(digitalRead(i));
  }//output of above code-block will be Pin 14 = 1/0

// Scan Path for various conditions of the MAZE
// PINID : [14 15 16 17 18 19]

  // FORWARD CONDITION [0 0 1 1 0 0] - SINGLE CONDITION-------------------------
  if (digitalRead(14) && !digitalRead(15) && digitalRead(16) && digitalRead(17) && !digitalRead(18) && !digitalRead(19)){
    Serial.println("Move Forward")
    front();
    GreenLightArea();
  }

  // BACKWARD CONDITION [0 x 1 0 x 0] - SINGLE CONDITION-------------------------
  if (!digitalRead(14) && !digitalRead(15) && digitalRead(16) && !digitalRead(17) && !digitalRead(18) && !digitalRead(19)){
    Serial.println("Move Backward")
    back();
    GreenLightArea();
  }

  // RIGHT/RIGHT-T CONDITION [0 0 1 1 1 1] - SINGLE CONDITION-------------------------
  if (!digitalRead(14) && !digitalRead(15) && digitalRead(16) && digitalRead(17) && digitalRead(18) && digitalRead(19)){
    Serial.println("Move Left")
    Left();
    GreenLightArea();
  }

  // LEFT/LEFT-T CONDITION [1 1 1 1 0 0] - SINGLE CONDITION-------------------------
  if (digitalRead(14) && digitalRead(15) && digitalRead(16) && digitalRead(17) && !digitalRead(18) && !digitalRead(19)){
    Serial.println("Move Left")
    Left();
    GreenLightArea();
  }

  // CROSS CONDITION [1 1 1 1 1 1] - SINGLE CONDITION-------------------------
  if (digitalRead(14) && digitalRead(15) && digitalRead(16) && digitalRead(17) && digitalRead(18) && digitalRead(19)){
    Serial.println("Move Forward")
    front();
    GreenLightArea();
  }

  // HALT CONDITION [1 0 0 0 0 1] - SINGLE CONDITION-------------------------
  if (digitalRead(14) && !digitalRead(15) && !digitalRead(16) && !digitalRead(17) && !digitalRead(18) && digitalRead(19)){
    Serial.println("Stop")
    halt();
    RedLightArea();
  }

  // U-TURN CONDITION [0 0 0 0 0 0] - SINGLE CONDITION-------------------------
  if (!digitalRead(14) && !digitalRead(15) && !digitalRead(16) && !digitalRead(17) && !digitalRead(18) && !digitalRead(19)){
    Serial.println("Performing U-Turn");
    uTurn();
    GreenLightArea();
  }

// incase of left-hand Follow
  // T CONDITION [1 0 1 1 0 0] - SINGLE CONDITION-------------------------
  if (digitalRead(14) && !digitalRead(15) && digitalRead(16) && digitalRead(17) && !digitalRead(18) && !digitalRead(19)){
    Serial.println("Move Left");
    Left();
    GreenLightArea();
  }

/* incase of Using Right-hand Follow
  // T CONDITION [1 0 1 1 0 0] - SINGLE CONDITION-------------------------
  if (digitalRead(14) && !digitalRead(15) && digitalRead(16) && digitalRead(17) && !digitalRead(18) && !digitalRead(19)){
    Serial.println("Move Right");
    Right();
    GreenLightArea();
  } */

//Basic Movements : front(), Right(), back(), Left(), halt(), U-Turn;
}

/* 
Function defined
Motor : Front , Back , Right , Left , halt , U-turn , 
LED : GreenLED , RedLED
*/
//front(), back(), Right(), Left()
void front(){
  m3.run(FORWARD);
  m4.run(FORWARD);
  delay(10);
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(1);
}
void Back(){
  m3.run(BACKWARD);
  m4.run(BACKWARD);
  delay(50);
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(1);
}
void right(){
  m3.run(FORWARD);
  m4.run(BACKWARD);
  delay(50);
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(1);
}
void left(){
  m3.run(BACKWARD);
  m4.run(FORWARD);
  delay(50);
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(1);
}
void halt(){
  m3.run(RELEASE)
  m4.run(RELEASE)
  delay(10000)
}
void UTurn(){
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(1000);
  m3.run(FORWARD);
  m4.run(BACKWARD);
  delay(2000);
  m3.run(RELEASE);
  m4.run(RELEASE);
}
void GreenLightArea(){
  digitalWrite(greenLEDPin, HIGH);
  delay(10);
  digitalWrite(greenLEDPin, LOW);
}
void RedLightArea(){
  digitalWrite(greenLEDPin, HIGH);
  delay(10000);
  digitalWrite(greenLEDPin, LOW);
}