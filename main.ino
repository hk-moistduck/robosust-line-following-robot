#include <Arduino.h>

// --- Configurations ---
const int r = 2;           // Tire radius `(cm)`
const int boardWidth = 10; // Physical board width `(cm)` / distance of two tires
const int topSpeed = 4;    // Speed of the motors at full power `(cm/s)`

// --- Sensor Pins ---
const int SensorPin[] = {A0, A1, A2, A3, A4, A5}; // Sensors in left to right order

// --- Motor A Pins ---
const int ENA = 5; // PWM pin for speed
const int IN1 = 7; // Direction pin 1
const int IN2 = 6; // Direction pin 2

// --- Motor B Pins ---
const int ENB = 9; // PWM pin for speed
const int IN3 = 4; // Direction pin 3
const int IN4 = 3; // Direction pin 4

// --- Other var to save time and memory ---
int rightSpeed;            // Right tire speed `(cm/s)`
int leftSpeed;             // Left tire speed `(cm/s)`
unsigned long startTime;   // general variable to save local start time of a timer
unsigned long currentTime; // general variable to save local current time of a timer

void setup()
{
    // Set all motor control pins as outputs
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    for (int i = 0; i < 6; i++)
        pinMode(SensorPin[i], INPUT);
}

void loop()
{
    // 1. Move both motors FORWARD at full speed for 2 seconds
    moveForward(255);
    delay(2000);
}

// --- Helper Functions ---

void moveForward(int speed)
{
    // Set speeds (0 to 255)
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);

    // Motor A Forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    // Motor B Forward
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void moveBackward(int speed)
{
    // Set speeds (0 to 255)
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);

    // Motor A Backward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    // Motor B Backward
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void stopMotors()
{
    // Turn off enable pins to cut power/coast to a stop
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void turnLeft(int degree, int innerRadius, int outterSpeed)
{
    // startTime = currentTime = millis();

    rightSpeed = outterSpeed;
    leftSpeed = (innerRadius * outterSpeed) / (innerRadius + boardWidth);

    // int fixedTime = (TWO_PI * innerRadius * degree * 1000) / (rightSpeed * 360);

    // while (millis() - startTime < fixedTime)
    // {
    analogWrite(ENA, leftSpeed);
    analogWrite(ENB, rightSpeed);

    // Motor A Forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    // Motor B Forward
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    // currentTime = millis();
    // }
}

void turnRight(int degree, int innerRadius, int outterSpeed)
{
    // startTime = currentTime = millis();

    leftSpeed = outterSpeed;
    rightSpeed = (innerRadius * outterSpeed) / (innerRadius + boardWidth);

    // int fixedTime = (TWO_PI * innerRadius * degree * 1000) / (rightSpeed * 360);

    // while (millis() - startTime < fixedTime)
    // {
    analogWrite(ENA, leftSpeed);
    analogWrite(ENB, rightSpeed);

    // Motor A Forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    // Motor B Forward
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    // currentTime = millis();
    // }
}