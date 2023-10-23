// Define LED pin numbers (replace with actual pin numbers)
const int greenLEDPin = 8;
const int redLEDPin = 9;

// Motor control pins (replace with your L298N connections)
const int motor1A = 2;
const int motor1B = 3;
const int motor2A = 4;
const int motor2B = 5;

void setup() {
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
  front();
  delay(1000);  // Adjust the movement duration
  halt();
  delay(1000);

  right();
  delay(1000);
  halt();
  delay(1000);

  back();
  delay(1000);
  halt();
  delay(1000);

  left();
  delay(1000);
  halt();
  delay(1000);
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
