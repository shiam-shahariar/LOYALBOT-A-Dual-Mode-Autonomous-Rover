#include <Servo.h>
#include <NewPing.h>

// ================= MODES =================
#define OBJECT_FOLLOWING_MODE  1
#define OBSTACLE_AVOIDING_MODE 2

int currentMode = OBJECT_FOLLOWING_MODE;   // Default mode = Mode 1

// ================= PINS =================
#define MODE_BUTTON_PIN 2

#define SERVO_PIN 3
#define ULTRASONIC_SENSOR_TRIG 11
#define ULTRASONIC_SENSOR_ECHO 12

#define TOP_IR_SENSOR_RIGHT A3
#define TOP_IR_SENSOR_LEFT  A2

// Right motor
int enableRightMotor = 5;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;

// Left motor
int enableLeftMotor = 6;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;

NewPing mySensor(ULTRASONIC_SENSOR_TRIG, ULTRASONIC_SENSOR_ECHO, 400);
Servo myServo;

// ================= BUTTON DEBOUNCE =================
bool lastButtonState = HIGH;
bool currentButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

// ================= SETUP =================
void setup()
{
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(TOP_IR_SENSOR_RIGHT, INPUT);
  pinMode(TOP_IR_SENSOR_LEFT, INPUT);

  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);   // Button connected to GND

  myServo.attach(SERVO_PIN);
  myServo.write(90);

  rotateMotor(0, 0);
}

// ================= BUTTON MODE SWITCH =================
void checkModeButton()
{
  bool reading = digitalRead(MODE_BUTTON_PIN);

  if (reading == LOW && lastButtonState == HIGH)
  {
    if (millis() - lastDebounceTime > debounceDelay)
    {
      if (currentMode == OBJECT_FOLLOWING_MODE)
      {
        currentMode = OBSTACLE_AVOIDING_MODE;
      }
      else
      {
        currentMode = OBJECT_FOLLOWING_MODE;
      }

      rotateMotor(0, 0);
      delay(200);

      lastDebounceTime = millis();
    }
  }

  lastButtonState = reading;
}

// ================= MODE 1: OBJECT FOLLOWING =================
void objectFollowingControl()
{
  int distance = mySensor.ping_cm();

  int rightIR = digitalRead(TOP_IR_SENSOR_RIGHT);
  int leftIR  = digitalRead(TOP_IR_SENSOR_LEFT);

  // Object detected more on left side
  if (rightIR == LOW && leftIR == HIGH)
  {
    rotateMotor(80, 200);     // Turn left
  }

  // Object detected more on right side
  else if (rightIR == HIGH && leftIR == LOW)
  {
    rotateMotor(200, 80);     // Turn right
  }

  // Object in front and proper distance
  else if (distance >= 10 && distance <= 30)
  {
    rotateMotor(150, 150);    // Move forward
  }

  // Object too close
  else if (distance > 0 && distance < 10)
  {
    rotateMotor(-120, -120);  // Move backward
  }

  // No object found
  else
  {
    rotateMotor(0, 0);        // Stop
  }
}

// ================= MODE 2: OBSTACLE AVOIDING =================
void obstacleAvoidingControl()
{
  int distance = mySensor.ping_cm();

  if (distance > 0 && distance < 20)
  {
    rotateMotor(0, 0);
    delay(300);

    rotateMotor(-180, -180);  // Move backward
    delay(300);

    rotateMotor(0, 0);
    delay(200);

    // Look left
    myServo.write(180);
    delay(500);
    int distanceLeft = mySensor.ping_cm();

    // Look right
    myServo.write(0);
    delay(500);
    int distanceRight = mySensor.ping_cm();

    // Center servo
    myServo.write(90);
    delay(300);

    // If no reading, assume blocked
    if (distanceLeft == 0) distanceLeft = 400;
    if (distanceRight == 0) distanceRight = 400;

    if (distanceLeft >= distanceRight)
    {
      rotateMotor(-180, 180);   // Turn left
    }
    else
    {
      rotateMotor(180, -180);   // Turn right
    }

    delay(500);

    rotateMotor(0, 0);
    delay(100);
  }
  else
  {
    rotateMotor(150, 150);      // Move forward
  }
}

// ================= MOTOR CONTROL =================
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  rightMotorSpeed = constrain(rightMotorSpeed, -255, 255);
  leftMotorSpeed  = constrain(leftMotorSpeed, -255, 255);

  // Right motor
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  }
  else
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  // Left motor
  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  }
  else
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}

// ================= MAIN LOOP =================
void loop()
{
  checkModeButton();

  if (currentMode == OBJECT_FOLLOWING_MODE)
  {
    objectFollowingControl();
  }
  else if (currentMode == OBSTACLE_AVOIDING_MODE)
  {
    obstacleAvoidingControl();
  }
}