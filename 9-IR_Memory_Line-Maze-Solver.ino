mn0#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include <AFMotor.h>
#include <LiquidCrystal.h>

// Define the LCD pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define LED pin numbers (replace with actual pin numbers)
const int greenLEDPin = 8;
const int redLEDPin = 9;

// Motor instance for pins 3 and 4
AF_DCMotor m3(3);
AF_DCMotor m4(4);

String recordedPath = "";

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("Serial Output:");

  // Adding LED
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  // Function for setting up pinmode for Motor from 13 to 21
  for (int i = 13; i < 22; i++) {
    pinMode(i, INPUT);
  }

  // Speed of motors (adjust as needed)
  m3.setSpeed(300);
  m4.setSpeed(300);
  m3.run(RELEASE);
  m4.run(RELEASE);
  
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
void loop() {
  // Check if there is serial data available to read
  if (Serial.available()) {
    // Read the serial data
    char incomingChar = Serial.read();

    // Print the received character to the LCD
    lcd.write(incomingChar);
  }

// Scan Path for various conditions of the MAZE
// PINID : [13 14 15 16 17 18 19 20 21]

  // FORWARD CONDITION [1 0 0 0 1 0 0 0 1] - SINGLE CONDITION-------------------------
  if (digitalRead(13) && !digitalRead(14) && !digitalRead(15) && !digitalRead(16) && digitalRead(17) && !digitalRead(18) && !digitalRead(19) && !digitalRead(20) && digitalRead(21)){
    Serial.println("Move Forward")
    front();
    GreenLightArea();
    recordedPath += "S"; // Record "S" for straight
  }

/*  // BACKWARD CONDITION [] - SINGLE CONDITION-------------------------
  if (!digitalRead(14) && !digitalRead(15) && digitalRead(16) && !digitalRead(17) && !digitalRead(18) && !digitalRead(19)){
    Serial.println("Move Backward")
    back();
    GreenLightArea();
    recordedPath += "B"; // Record "B" for Backward
  }
*/
  // RIGHT CONDITION [0 0 0 0 1 1 1 0 1] - SINGLE CONDITION-------------------------
  if (!digitalRead(13) && !digitalRead(14) && !digitalRead(15) && !digitalRead(16) && digitalRead(17) && digitalRead(18) && digitalRead(19) && !digitalRead(20) && digitalRead(21)){
    Serial.println("Move right")
    right();
    GreenLightArea();
    // dont add no path exist becoz recordedPath += "R"; // Record "L" for Right
  }

  // RIGHT T  CONDITION[1 0 0 0 1 1 1 0 1] - SINGLE CONDITION-------------------------
  if (digitalRead(13) && !digitalRead(14) && !digitalRead(15) && !digitalRead(16) && digitalRead(17) && digitalRead(18) && digitalRead(19) && !digitalRead(20) && digitalRead(21)){
    Serial.println("Move front")
    front();
    recordedPath += "L"; // Record "S" for Left
    GreenLightArea();
  }

/* in right recursive

  // RIGHT T  CONDITION[1 0 0 0 1 1 1 0 1] - SINGLE CONDITION-------------------------
  if (digitalRead(13) && !digitalRead(14) && !digitalRead(15) && !digitalRead(16) && digitalRead(17) && digitalRead(18) && digitalRead(19) && !digitalRead(20) && digitalRead(21)){
    Serial.println("Move front")
    right();
    GreenLightArea();
    recordedPath += "R"; // Record "L" for Right
  }

*/

  // LEFT CONDITION [0 0 1 1 1 0 0 0 1] - SINGLE CONDITION-------------------------
  if (!digitalRead(13) && !digitalRead(14) && digitalRead(15) && digitalRead(16) && digitalRead(17) && !digitalRead(18) && !digitalRead(19) && !digitalRead(20) && digitalRead(21)){
    Serial.println("Move Left")
    Left();
    GreenLightArea();
    // recordedPath += "L"; // Record "S" for Left
  }

  // LEFT-T CONDITION [1 0 1 1 1 0 0 0 1] - SINGLE CONDITION-------------------------
  if (digitalRead(13) && !digitalRead(14) && digitalRead(15) && digitalRead(16) && digitalRead(17) && !digitalRead(18) && !digitalRead(19) && !digitalRead(20) && digitalRead(21)){
    Serial.println("Move Left")
    Left();
    GreenLightArea();
    recordedPath += "L"; // Record "S" for Left
  }

/*
    in left recursive
  // LEFT-T CONDITION [1 0 1 1 1 0 0 0 1] - SINGLE CONDITION-------------------------
  if (digitalRead(13) && !digitalRead(14) && digitalRead(15) && digitalRead(16) && digitalRead(17) && !digitalRead(18) && !digitalRead(19) && !digitalRead(20) && digitalRead(21)){
    Serial.println("Move Left")
    front();
    GreenLightArea();
  }

*/

  // CROSS CONDITION [1 0 1 1 1 1 1 0 1] - SINGLE CONDITION-------------------------
  if (digitalRead(13) && !digitalRead(14) && digitalRead(15) && digitalRead(16) && digitalRead(17) && digitalRead(18) && digitalRead(19) && !digitalRead(20) && digitalRead(21)){
    Serial.println("Move Forward")
    front();
    GreenLightArea();
    recordedPath += "S"; // Record "S" for straight
  }

  // HALT CONDITION [0 1 0 1 0 1 0 1 0] - SINGLE CONDITION-------------------------
  if (!digitalRead(13) && digitalRead(14) && !digitalRead(15) && digitalRead(16) && !digitalRead(17) && digitalRead(18) && !digitalRead(19) && digitalRead(20) && !digitalRead(21)){
    Serial.println("Stop")
    halt();
    RedLightArea();

  }

  // U-TURN CONDITION [0 0 0 0 1 0 0 0 1] - SINGLE CONDITION-------------------------
  if (!digitalRead(13) && !digitalRead(14) && !digitalRead(15) && !digitalRead(16) && digitalRead(17) && !digitalRead(18) && !digitalRead(19) && !digitalRead(20) && digitalRead(21)){
    Serial.println("Performing U-Turn");
    uTurn();
    GreenLightArea();
  }

// incase of left-hand Follow
  // T CONDITION [0 0 1 1 1 1 1 0 1] - SINGLE CONDITION-------------------------
  if (!digitalRead(13);&& !digitalRead(14) && digitalRead(15) && digitalRead(16) && digitalRead(17) && digitalRead(18) && digitalRead(19) && !digitalRead(20) && digitalRead(21)){
    Serial.println("Move Left");
    Left();
    GreenLightArea();
    recordedPath += "L"; // Record "L" for Left
  }

/* // incase of left-hand Follow
  // T CONDITION [0 0 1 1 1 1 1 0 1] - SINGLE CONDITION-------------------------
  if (!digitalRead(13);&& !digitalRead(14) && digitalRead(15) && digitalRead(16) && digitalRead(17) && digitalRead(18) && digitalRead(19) && !digitalRead(20) && digitalRead(21)){
    Serial.println("Move Right");
    Right();
    GreenLightArea();
  } */

  // Call recordAndRun when needed, e.g., after recording the desired path  
  if (/* Your condition to start executing the path */) {
    recordAndRun();
  }
}

// Check if there is serial data available to read
  if (Serial.available()) {
    // Read the serial data
    char incomingChar = Serial.read();

    // Print the received character to the LCD
    lcd.write(incomingChar);
  }

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
// Define other movement functions (back, right, left, halt, uTurn, GreenLightArea, RedLightArea) here

void recordAndRun() {
  String shortestPath = shortPath(recordedPath);
  executePath(shortestPath);
}

String shortPath(String path) {
  String substitutions[][2] = {
    {"LBL", "S"},
    {"LBS", "R"},
    {"RBL", "B"},
    {"SBS", "B"},
    {"SBL", "R"},
    {"LBR", "B"}
  };

  for (int i = 0; i < sizeof(substitutions) / sizeof(substitutions[0]); i++) {
    path.replace(substitutions[i][0], substitutions[i][1]);
  }

  return path;
}
+-  
void executePath(String path) {
  for (int i = 0; i < path.length(); i++) {
    char move = path.charAt(i);

    if (move == 'L') {
      left();
    } else if (move == 'R') {
      right();
    } else if (move == 'B') {
      uTurn();
    } else if (move == 'S') {
      front();
    }

    delay(1000); // Adjust the delay time as needed
  }
}
