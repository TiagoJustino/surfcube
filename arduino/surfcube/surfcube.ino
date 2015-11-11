#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <Servo.h> 
#include <EEPROM.h>

#define SERVO_MAX_ANGLE 115
#define CUBE_LEGTH 127
#define CUBE_WIDTH 80
#define STEPS_PER_ML 62
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

int stepperDirection = FORWARD;
int stepperSteps = 0;
int stepperCurrentPosition;
unsigned long stepperNextCheck = 0;

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
int LEDBreathingState = RED_MASK & YELLOW_MASK & GREEN_MASK;
int LEDRedValue = 0;
int LEDYellowValue = 0;
int LEDGreenValue = 0;

void setup() {
  Serial.begin(9600);

  AFMS.begin();
  servo.attach(10);
  myStepper->setSpeed(255);

  servo.write(SERVO_MAX_ANGLE);

  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void tide (int tideDirection, int amount) {
  // TODO
}

void checkSerial() {
  String command;
  int val;
  if (Serial.available() > 0) {
    Serial.println("Data received");
    command = Serial.readStringUntil('\n');
    while(Serial.available() == 0) {}
    val = Serial.parseInt();
    Serial.print("command = [");
    Serial.print(command);
    Serial.print("]; val = [");
    Serial.print(val);
    Serial.println("]");
    if (command == "forward") {
      stepperDirection = FORWARD;
      stepperSteps = val;
    } else if (command == "backward") {
      stepperDirection = BACKWARD;
      stepperSteps = val;
    } else if (command == "servo") {
      servoUserTargetAngle = val ? (val % (SERVO_MAX_ANGLE + 1)) : val;
    } else if (command == "frequency") {
      servoFrequency = val;
    } else if (command == "delay") {
      servoDelay = val;
    } else if (command == "tideup") {
      tide(UP, val);
    } else if (command == "tidedown") {
      tide(DOWN, val);
    } else if (command == "breathingstate") {
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
    } else {
      Serial.println("Command not understood!");
    }

    while(Serial.available()) {
      Serial.read();
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
  if(stepperSteps) {
    myStepper->step(1, stepperDirection, SINGLE);
    switch(stepperDirection) {
      case FORWARD:
        ++stepperCurrentPosition;
        break;
      case BACKWARD:
        --stepperCurrentPosition;
    }
    --stepperSteps;
    stepperNextCheck = now + 1;
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
  if(now >= stepperNextCheck) {
    checkStepper();
  }
  if((now >= servoNextCheck) && (stepperSteps == 0)) {
    checkServo();
  }
  if(now >= keepAliveNextCheck) {
    Serial.println("I'm alive");
    keepAliveNextCheck = now + 2000;
  }
  if(LEDBreathingState) {
    updateLED();
  }
}

