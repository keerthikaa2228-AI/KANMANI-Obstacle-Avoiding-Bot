#include <Servo.h>

// Motor pins
int motor1Pin1 = 8;
int motor1Pin2 = 9;
int motor2Pin1 = 10;
int motor2Pin2 = 11;

// Ultrasonic pins
int trigPin = 6;
int echoPin = 7;

// Servo pin
int servoPin = 5;
Servo myServo;

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servoPin);
  myServo.write(90); // center
  Serial.begin(9600);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // cm
}

void loop() {

  myServo.write(90); // center
  delay(300);
  long distance = getDistance();

  if (distance < 15) {
    stopMotors();
    delay(500);

    // Check right
    myServo.write(0);
    delay(500);
    long rightDist = getDistance();

    // Check left
    myServo.write(180);
    delay(500);
    long leftDist = getDistance();

    // Decide direction
    if (rightDist > leftDist) {
      turnRight();
      delay(700);
    } else {
      turnLeft();
      delay(700);
    }
  } else {
    moveForward();
  }
}

// Motor functions
void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void turnRight() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnLeft() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

