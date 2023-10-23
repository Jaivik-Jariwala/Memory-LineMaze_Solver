#include <Arduino.h>
#include <LiquidCrystal.h>
#include <PID_v1.h> // Include the PID library

// Define the LCD pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define LED pin numbers (replace with actual pin numbers)
const int greenLEDPin = 8;
const int redLEDPin = 9;

// Define L298 motor driver pins
const int motor1Pin1 = 10; // Connect to IN1 on L298
const int motor1Pin2 = 11; // Connect to IN2 on L298
const int motor2Pin1 = 12; // Connect to IN3 on L298
const int motor2Pin2 = 13; // Connect to IN4 on L298

// Define IR sensor pins
const int irSensor1Pin = A0;
const int irSensor2Pin = A1;
const int irSensor3Pin = A2;
const int irSensor4Pin = A3;
const int irSensor5Pin = A4;
const int irSensor6Pin = A5;

// Define PID parameters
double Setpoint = 0;
double Input = 0;
double Output1 = 0;
double Output2 = 0;
double Kp = 1.0; // Proportional term
double Ki = 0.0; // Integral term
double Kd = 0.0; // Derivative term
PID pid1(&Input, &Output1, &Setpoint, Kp, Ki, Kd, DIRECT);
PID pid2(&Input, &Output2, &Setpoint, Kp, Ki, Kd, DIRECT);

String recordedPath = "";

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("Serial Output:");

  // Adding LED
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  // Set motor pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Initialize serial communication
  Serial.begin(9600);

  // Initialize PID control
  pid1.SetOutputLimits(-255, 255); // Set the output limits for the motors
  pid1.SetMode(AUTOMATIC);
  pid2.SetOutputLimits(-255, 255);
  pid2.SetMode(AUTOMATIC);
}

void loop() {
  // Read IR sensor values
  int sensor1Value = analogRead(irSensor1Pin);
  int sensor2Value = analogRead(irSensor2Pin);
  int sensor3Value = analogRead(irSensor3Pin);
  int sensor4Value = analogRead(irSensor4Pin);
  int sensor5Value = analogRead(irSensor5Pin);
  int sensor6Value = analogRead(irSensor6Pin);

  // Calculate Input based on IR sensor values (adjust as needed)
  Input = sensor1Value - sensor2Value + sensor3Value - sensor4Value + sensor5Value - sensor6Value;

  // Calculate PID control outputs
  pid1.Compute();
  pid2.Compute();

  // Apply the PID control outputs to the motors
  analogWrite(motor1Pin1, abs(Output1));
  analogWrite(motor1Pin2, 0);
  analogWrite(motor2Pin1, abs(Output2));
  analogWrite(motor2Pin2, 0);

  // Check if there is serial data available to read
  if (Serial.available()) {
    // Read the serial data
    char incomingChar = Serial.read();

    // Print the received character to the LCD
    lcd.write(incomingChar);
  }

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
void front() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  // Adjust the delay as needed
  delay(10);
  // Stop the motors
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1);
}

void back() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  // Adjust the delay as needed
  delay(50);
  // Stop the motors
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1);
}

void right() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  // Adjust the delay as needed
  delay(50);
  // Stop the motors
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1);
}

void left() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  // Adjust the delay as needed
  delay(50);
  // Stop the motors
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1);
}

void halt() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(10000);
}

void uTurn() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1000);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(2000);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void GreenLightArea() {
  digitalWrite(greenLEDPin, HIGH);
  delay(10);
  digitalWrite(greenLEDPin, LOW);
}

void RedLightArea() {
  digitalWrite(redLEDPin, HIGH);
  delay(10000);
  digitalWrite(redLEDPin, LOW);
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
