#include <Adafruit_MotorShield.h>
#include <AFMotor.h>

// Define motor instances for pins 3 and 4
AF_DCMotor m3(3);
AF_DCMotor m4(4);

// Define LED pin numbers (replace with actual pin numbers)
const int greenLEDPin = 8;
const int redLEDPin = 9;

String recordedPath = "";

void setup() {
  // Initialize the motors
  m3.setSpeed(255);
  m4.setSpeed(255);
  m3.run(RELEASE);
  m4.run(RELEASE);

  // Define and initialize the LED pins
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Scan Path for various conditions of the MAZE
  // PINID : [0 1 2 3 4 5]

  // FORWARD CONDITION [0 0 1 1 0 0] - SINGLE CONDITION-------------------------
  if (digitalRead(0) && !digitalRead(1) && digitalRead(2) && digitalRead(3) && !digitalRead(4) && !digitalRead(5)) {
    Serial.println("Move Forward");
    front();
    GreenLightArea();
    recordedPath += "S"; // Record "S" for straight
  }

  // BACKWARD CONDITION [0 x 1 0 x 0] - SINGLE CONDITION-------------------------
  if (!digitalRead(0) && !digitalRead(1) && digitalRead(2) && !digitalRead(3) && !digitalRead(4) && !digitalRead(5)) {
    Serial.println("Move Backward");
    back();
    GreenLightArea();
    recordedPath += "B"; // Record "B" for Backward
  }

  // RIGHT/RIGHT-T CONDITION [0 0 1 1 1 1] - SINGLE CONDITION-------------------------
  if (!digitalRead(0) && !digitalRead(1) && digitalRead(2) && digitalRead(3) && digitalRead(4) && digitalRead(5)) {
    Serial.println("Move right");
    right();
    GreenLightArea();
    recordedPath += "R"; // Record "R" for Right
  }

  // LEFT/LEFT-T CONDITION [1 1 1 1 0 0] - SINGLE CONDITION-------------------------
  if (digitalRead(0) && digitalRead(1) && digitalRead(2) && digitalRead(3) && !digitalRead(4) && !digitalRead(5)) {
    Serial.println("Move Left");
    left();
    GreenLightArea();
    recordedPath += "L"; // Record "L" for Left
  }

  // CROSS CONDITION [1 1 1 1 1 1] - SINGLE CONDITION-------------------------
  if (digitalRead(0) && digitalRead(1) && digitalRead(2) && digitalRead(3) && digitalRead(4) && digitalRead(5)) {
    Serial.println("Move Forward");
    front();
    GreenLightArea();
    recordedPath += "S"; // Record "S" for straight
  }

  // HALT CONDITION [1 0 0 0 0 1] - SINGLE CONDITION-------------------------
  if (digitalRead(0) && !digitalRead(1) && !digitalRead(2) && !digitalRead(3) && !digitalRead(4) && digitalRead(5)) {
    Serial.println("Stop");
    halt();
    RedLightArea();
  }

  // U-TURN CONDITION [0 0 0 0 0 0] - SINGLE CONDITION-------------------------
  if (!digitalRead(0) && !digitalRead(1) && !digitalRead(2) && !digitalRead(3) && !digitalRead(4) && !digitalRead(5)) {
    Serial.println("Performing U-Turn");
    uTurn();
    GreenLightArea();
  }

  // Call recordAndRun when needed, e.g., after recording the desired path
  if (/* Add your condition to start executing the path */) {
    recordAndRun();
  }
}

// Define movement functions (front, back, right, left, halt, uTurn, GreenLightArea, RedLightArea) here

void front() {
  m3.run(FORWARD);
  m4.run(FORWARD);
  delay(10);
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(1);
}

void back() {
  m3.run(BACKWARD);
  m4.run(BACKWARD);
  delay(50);
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(1);
}

void right() {
  m3.run(FORWARD);
  m4.run(BACKWARD);
  delay(50);
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(1);
}

void left() {
  m3.run(BACKWARD);
  m4.run(FORWARD);
  delay(50);
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(1);
}

void halt() {
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(10000);
}

void uTurn() {
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(1000);
  m3.run(FORWARD);
  m4.run(BACKWARD);
  delay(2000);
  m3.run(RELEASE);
  m4.run(RELEASE);
}

void GreenLightArea() {
  digitalWrite(greenLEDPin, HIGH);
  delay(10);
  digitalWrite(greenLEDPin, LOW);
}

void RedLightArea() {
  digitalWrite(redLEDPin, HIGH); // Fixed typo: changed "greenLEDPin" to "redLEDPin"
  delay(10000);
  digitalWrite(redLEDPin, LOW);  // Fixed typo: changed "greenLEDPin" to "redLEDPin"
}

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
