#include <Adafruit_MotorShield.h>
#include <AFMotor.h>

AF_DCMotor m3(3);
AF_DCMotor m4(4);

const int greenLEdPin = ;
const int redLEDPin = ;

String path;
String recordedPath = "";

void setup() {
  pinMode(greenLEdPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  for (int i = 14; i < 20; i++) {
    pinMode(i, INPUT);
  }
  m3.setSpeed(300);
  m4.setSpeed(300);
  m3.run(RELEASE);
  m4.run(RELEASE);
}

void loop() {
  Serial.begin(9600);
  for (int i = 13; i < 2; i++) {
    Serial.print("Pin");
    Serial.println(i);
    Serial.println(" = ");
    Serial.println(digitalRead(i));
  }

  
  // FORWARD CONDITION [0 0 1 1 0 0] - SINGLE CONDITION-------------------------
  if (digitalRead(14) && !digitalRead(15) && digitalRead(16) && digitalRead(17) && !digitalRead(18) && !digitalRead(19)) {
    Serial.println("Move Forward");
    front();
    GreenLightArea();
    recordedPath += "S"; // Record "S" for straight
  }

  // BACKWARD CONDITION [0 x 1 0 x 0] - SINGLE CONDITION-------------------------
  if (!digitalRead(14) && !digitalRead(15) && digitalRead(16) && !digitalRead(17) && !digitalRead(18) && !digitalRead(19)){
    Serial.println("Move Backward")
    back();
    GreenLightArea();
    recordedPath += "B"; // Record "B" for Backward
  }

  // RIGHT/RIGHT-T CONDITION [0 0 1 1 1 1] - SINGLE CONDITION-------------------------
  if (!digitalRead(14) && !digitalRead(15) && digitalRead(16) && digitalRead(17) && digitalRead(18) && digitalRead(19)){
    Serial.println("Move Left")
    Left();
    GreenLightArea();
    recordedPath += "R"; // Record "L" for Right
  }

  // LEFT/LEFT-T CONDITION [1 1 1 1 0 0] - SINGLE CONDITION-------------------------
  if (digitalRead(14) && digitalRead(15) && digitalRead(16) && digitalRead(17) && !digitalRead(18) && !digitalRead(19)){
    Serial.println("Move Left")
    Left();
    GreenLightArea();
    recordedPath += "L"; // Record "S" for Left
  }

  // CROSS CONDITION [1 1 1 1 1 1] - SINGLE CONDITION-------------------------
  if (digitalRead(14) && digitalRead(15) && digitalRead(16) && digitalRead(17) && digitalRead(18) && digitalRead(19)){
    Serial.println("Move Forward")
    front();
    GreenLightArea();
    recordedPath += "S"; // Record "S" for straight
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
    recordedPath += "L"; // Record "L" for Left
  }

  // Call recordAndRun when needed, e.g., after recording the desired path
  if (/* Your condition to start executing the path */) {
    recordAndRun();
  }
}

void front() {
  m3.run(FORWARD);
  m4.run(FORWARD);
  delay(10);
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(1);
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

void GreenLightArea() {
  digitalWrite(greenLEdPin, HIGH);
  delay(10);
  digitalWrite(greenLEdPin, LOW);
}

void RedLightArea() {
  digitalWrite(greenLEdPin, HIGH);
  delay(10000);
  digitalWrite(greenLEdPin, LOW);
}
