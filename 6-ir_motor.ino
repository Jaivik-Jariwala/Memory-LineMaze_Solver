// Define LED pin numbers (replace with actual pin numbers)
const int greenLEDPin = 8;
const int redLEDPin = 9;

// Motor control pins (replace with your L298N connections)
const int motor1A = 2;
const int motor1B = 3;
const int motor2A = 4;
const int motor2B = 5;

void setup() {

      // Function for setting up pinmode for Motor from 13 to 21
  for (int i = 13; i < 22; i++) {
    pinMode(i, INPUT);
  }
  
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  // Initialize serial communication
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

}

void front() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void back() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

void right() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

void left() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void halt() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  delay(1000);  // Adjust the halt duration
}

void GreenLightArea() {
  digitalWrite(greenLEDPin, HIGH);
  delay(10);
  digitalWrite(greenLEDPin, LOW);
}

void RedLightArea() {
  digitalWrite(redLEDPin, HIGH);
  delay(10000);  // Adjust the duration the red LED is on
  digitalWrite(redLEDPin, LOW);
}
