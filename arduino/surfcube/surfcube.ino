#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <Servo.h> 
#include <EEPROM.h>

#define clamp(x, low, high) max(low, min(x, high));

#define SERVO_MAX_ANGLE 115
#define CUBE_LEGTH 127
#define CUBE_WIDTH 80
#define CUBE_BASE_AREA (CUBE_LEGTH * CUBE_WIDTH)
#define STEPS_PER_ML 62
#define STEPPER_MAX_POSITION (STEPS_PER_ML * 300)
#define EEPROM_STEPPER_ADDR 0
#define UP 1
#define DOWN 0
#define RED_PIN 3
#define YELLOW_PIN 5
#define GREEN_PIN 6
#define RED_MASK 1
#define YELLOW_MASK ( 1 << 1 )
#define GREEN_MASK ( 1 << 2 )

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myStepper = AFMS.getStepper(200, 2);
Servo servo;

unsigned long now = 0;

unsigned long serialNextCheck = 0;

int stepperCurrentPosition;
int stepperTargetPosition;

int servoUserTargetAngle = SERVO_MAX_ANGLE;
int servoTargetAngle = SERVO_MAX_ANGLE;
int servoCurrentAngle = SERVO_MAX_ANGLE;
unsigned long servoNextCheck = 0;
unsigned long servoFrequency = 7000;
unsigned long servoDelay = 2;

unsigned long keepAliveNextCheck = 0;

/*
   0 -> OFF
   1 -> red
   2 -> yellow
   3 -> red + yellow
   4 -> green
   5 -> red + green
   6 -> yellow + green
   7 -> red + yellow + green
   */
int LEDBreathingState = 0;

void setup() {
  Serial.begin(9600);

  AFMS.begin();
  servo.attach(10);
  myStepper->setSpeed(255);

  servo.write(SERVO_MAX_ANGLE);

  EEPROM.get(EEPROM_STEPPER_ADDR, stepperCurrentPosition);
  stepperTargetPosition = stepperCurrentPosition;
  /*
  Serial.print("read stepperCurrentPosition from EEPROM: ");
  Serial.println(stepperCurrentPosition);
  */

  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

/*
   mm -> number of milimeters above the minimum.
   */
void tide(int mm) {
  float mm3, ml;

  mm3 = mm * CUBE_BASE_AREA;
  ml = mm3 / 1000;
  stepperTargetPosition = ml * STEPS_PER_ML;
  stepperTargetPosition = clamp(stepperTargetPosition, 0, STEPPER_MAX_POSITION);
}

/*
   Temperature in Celsius
      < 15 green
   15 - 20 green + yellow
   20 - 25 yellow
   25 - 30 yellow + red
   30 >    red
   */
void setTemperature(int temperature) {
  if(temperature <= 15) {
    LEDBreathingState = 1;
  } else if(15 < temperature && temperature <= 20) {
    LEDBreathingState = 3;
  } else if(20 < temperature && temperature <= 25) {
    LEDBreathingState = 2;
  } else if(25 < temperature && temperature <= 30) {
    LEDBreathingState = 6;
  } else if(30 < temperature) {
    LEDBreathingState = 4;
  }
}

void checkSerial() {
  String command;
  int val;
  if (Serial.available() > 0) {
    /*
    Serial.println("Data received");
    */
    command = Serial.readStringUntil('\n');
    while(Serial.available() == 0) {}
    val = Serial.parseInt();
    // Remove new line character after reading the integer.
    Serial.readStringUntil('\n');

    /*
    Serial.print("command = [");
    Serial.print(command);
    Serial.print("]; val = [");
    Serial.print(val);
    Serial.println("]");
    */
    if (command == "forward") {
      stepperTargetPosition += val;
      stepperTargetPosition = clamp(stepperTargetPosition, 0, STEPPER_MAX_POSITION);
    } else if (command == "backward") {
      stepperTargetPosition -= val;
      stepperTargetPosition = clamp(stepperTargetPosition, 0, STEPPER_MAX_POSITION);
    } else if (command == "servo") {
      servoUserTargetAngle = val ? (val % (SERVO_MAX_ANGLE + 1)) : val;
    } else if (command == "frequency") {
      servoFrequency = val;
    } else if (command == "delay") {
      servoDelay = val;
    } else if (command == "tide") {
      tide(val);
    } else if (command == "breathingstate") {
      analogWrite(RED_PIN, 0);
      analogWrite(YELLOW_PIN, 0);
      analogWrite(GREEN_PIN, 0);
      LEDBreathingState = val;
    } else if (command == "red") {
      LEDBreathingState &= ~RED_MASK;
      analogWrite(RED_PIN, val);
    } else if (command == "yellow") {
      LEDBreathingState &= ~YELLOW_MASK;
      analogWrite(YELLOW_PIN, val);
    } else if (command == "green") {
      LEDBreathingState &= ~GREEN_MASK;
      analogWrite(GREEN_PIN, val);
    } else if (command == "ping") {
      Serial.println("pong");
    } else if (command == "setstepperposition") {
      stepperCurrentPosition = clamp(val, 0, STEPPER_MAX_POSITION);
      stepperTargetPosition  = clamp(val, 0, STEPPER_MAX_POSITION);
      EEPROM.put(EEPROM_STEPPER_ADDR, stepperCurrentPosition);
    } else if (command == "temperature") {
      setTemperature(val);
    } else {
      Serial.println("Command not understood!");
    }
  }
  serialNextCheck = now + 1;
}

void checkServo() {
  if(servoCurrentAngle != servoTargetAngle) {
    if(servoCurrentAngle < servoTargetAngle) {
      ++servoCurrentAngle;
    }
    if(servoCurrentAngle > servoTargetAngle) {
      --servoCurrentAngle;
    }
    servo.write(servoCurrentAngle);
    servoNextCheck = now + servoDelay;
  }
  if(servoCurrentAngle == servoTargetAngle) {
    if(servoTargetAngle == SERVO_MAX_ANGLE) {
      servoNextCheck = now + servoFrequency;
    }
    servoTargetAngle = servoTargetAngle == SERVO_MAX_ANGLE ? servoUserTargetAngle : SERVO_MAX_ANGLE;
  }
}

void checkStepper() {
  int stepperDirection;

  if(stepperTargetPosition > stepperCurrentPosition) {
    stepperDirection = FORWARD;
    ++stepperCurrentPosition;
  } else {
    stepperDirection = BACKWARD;
    --stepperCurrentPosition;
  }

  myStepper->step(1, stepperDirection, SINGLE);

  if(stepperCurrentPosition == stepperTargetPosition) {
    EEPROM.put(EEPROM_STEPPER_ADDR, stepperCurrentPosition);
  }
}

int counter = 0;

void updateLED() {
  float val = (exp(sin(now/2000.0*PI)) - 0.36787944)*108.0;
  if(LEDBreathingState & RED_MASK) {
    analogWrite(RED_PIN, val);
  }
  if(LEDBreathingState & YELLOW_MASK) {
    analogWrite(YELLOW_PIN, val);
  }
  if(LEDBreathingState & GREEN_MASK) {
    analogWrite(GREEN_PIN, val);
  }
}

void loop() {
  now = millis();
  if(now >= serialNextCheck) {
    checkSerial();
  }
  if(stepperTargetPosition != stepperCurrentPosition) {
    checkStepper();
  } else if(now >= servoNextCheck) { // Only check servo if stepper has finished.
    checkServo();
  }
  if(LEDBreathingState) {
    updateLED();
  }
}

