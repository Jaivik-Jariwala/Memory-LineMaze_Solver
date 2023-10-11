// Motor A
int motorPin1 = 2; // Motor 1, Input A
int motorPin2 = 3; // Motor 1, Input B

// Motor B
int motorPin3 = 4; // Motor 2, Input A
int motorPin4 = 5; // Motor 2, Input B

void setup() {
  // Define motor control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop() {
  // Move forward at a custom speed and duration
  moveForward(255, 2000); // Speed: 255 (0-255), Duration: 2000 milliseconds
  
  // Stop
  stopMotors();
  delay(1000); // Stop for 1 second
  
  // Turn left at a custom speed and duration
  turnLeft(255, 1000); // Speed: 255 (0-255), Duration: 1000 milliseconds
  
  // Stop
  stopMotors();
  delay(1000); // Stop for 1 second
  
  // Turn right at a custom speed and duration
  turnRight(255, 1000); // Speed: 255 (0-255), Duration: 1000 milliseconds
  
  // Stop
  stopMotors();
  delay(1000); // Stop for 1 second
}

void moveForward(int speed, unsigned long duration) {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(duration);
  stopMotors();
}

void turnLeft(int speed, unsigned long duration) {
  digitalWrite(motorPin1, LOW);
  analogWrite(motorPin2, speed);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(duration);
  stopMotors();
}

void turnRight(int speed, unsigned long duration) {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  analogWrite(motorPin4, speed);
  delay(duration);
  stopMotors();
}

void stopMotors() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}
