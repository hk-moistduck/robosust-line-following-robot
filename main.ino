#include <Arduino.h>

// --- Configurations ---
constexpr uint8_t tireRadius = 2;  // Tire radius `(cm)`
constexpr uint8_t boardWidth = 10; // Physical board width `(cm)` / distance of two tires
constexpr uint8_t topSpeed = 4;    // Speed of the motors at full power `(cm/s)`

// --- Sensor Pins ---
constexpr uint8_t SensorPin[] = {A0, A1, A2, A3, A4, A5}; // Sensors in left to right order

// --- Motor A Pins ---
constexpr uint8_t ENA = 5; // PWM pin for speed
constexpr uint8_t IN1 = 7; // Direction pin 1
constexpr uint8_t IN2 = 6; // Direction pin 2

// --- Motor B Pins ---
constexpr uint8_t ENB = 9; // PWM pin for speed
constexpr uint8_t IN3 = 4; // Direction pin 3
constexpr uint8_t IN4 = 3; // Direction pin 4

void setup()
{
    // Set all motor control pins as outputs
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    for (uint8_t pin : SensorPin)
        pinMode(pin, INPUT);
}

void loop()
{
    // 1. Move both motors FORWARD at full speed for 2 seconds
    moveForward(255);
    delay(2000);
}

// --- Helper Functions ---

inline void setMotorDirection(bool leftForward, bool rightForward)
{
    digitalWrite(IN1, leftForward);
    digitalWrite(IN2, !leftForward);

    digitalWrite(IN3, rightForward);
    digitalWrite(IN4, !rightForward);
}

inline void setMotorSpeed(uint8_t leftMotorSpeed, uint8_t rightMotorSpeed)
{
    analogWrite(ENA, leftMotorSpeed);
    analogWrite(ENB, rightMotorSpeed);
}

inline void moveForward(uint8_t speed)
{
    setMotorSpeed(speed, speed);
    setMotorDirection(true, true);
}

inline void moveBackward(uint8_t speed)
{
    setMotorSpeed(speed, speed);
    setMotorDirection(false, false);
}

inline void stopMotors()
{
    // Turn off enable pins to cut power/coast to a stop
    setMotorSpeed(0, 0);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

// `turnLeft`: `true` if turning left, `false` otherwise
// `innerRadius`: the radius of the circle created by taking the path of the inner tire as tangent to the direction of the turn
// `outerSpeed`: speed of the outer tire with respect to the turning direction
void turn(bool left, uint16_t innerRadius, uint8_t outerSpeed)
{
    uint8_t innerSpeed = (innerRadius * outerSpeed) / (innerRadius + boardWidth);

    if (left)
        setMotorSpeed(innerSpeed, outerSpeed);
    else
        setMotorSpeed(outerSpeed, innerSpeed);

    setMotorDirection(true, true);
}
