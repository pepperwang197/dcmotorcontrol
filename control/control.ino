#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Initialize motors
Adafruit_DCMotor *motorL = AFMS.getMotor(1);
Adafruit_DCMotor *motorR = AFMS.getMotor(2);

// Base speeds
int baseSpeedL = 31;
int baseSpeedR = 30;
int turnSpeed = 60;        // for sharp turns
int slightTurnSpeed = 40;  // for slight turns
int searchSpeed = 25;      // speed when searching for line

// Line sensors
int sensorL = A0;
int sensorM = A1;
int sensorR = A2;

// Thresholds
int thresholdVoltageLow = 100;

// Turn state
typedef enum {
  NONE,
  RIGHT,
  LEFT
} TurnState;

TurnState turning = NONE;

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }

  Serial.println("Motor Shield found.");

  motorL->setSpeed(baseSpeedL);
  motorR->setSpeed(baseSpeedR);
  motorL->run(FORWARD);
  motorR->run(BACKWARD);
}

void loop() {
  // Read sensors
  bool detectL = analogRead(sensorL) < thresholdVoltageLow;
  bool detectM = analogRead(sensorM) < thresholdVoltageLow;
  bool detectR = analogRead(sensorR) < thresholdVoltageLow;

  // Sharp turn recovery
  if (turning == LEFT && detectM && !detectL) turning = NONE;
  if (turning == RIGHT && detectM && !detectR) turning = NONE;

  // Sharp turns
  if (turning == NONE && detectL && detectM) {
    Serial.println("sharp LEFT turn");
    motorL->setSpeed(turnSpeed);
    motorR->setSpeed(turnSpeed);
    motorL->run(BACKWARD);
    motorR->run(BACKWARD);
    turning = LEFT;
  } else if (turning == NONE && detectR && detectM) {
    Serial.println("sharp RIGHT turn");
    motorL->setSpeed(turnSpeed);
    motorR->setSpeed(turnSpeed);
    motorL->run(FORWARD);
    motorR->run(FORWARD);
    turning = RIGHT;
  }
  // Slight turns and forward
  else if (detectM && !detectL && !detectR) {
    Serial.println("straight");
    motorL->setSpeed(baseSpeedL);
    motorR->setSpeed(baseSpeedR);
    motorL->run(FORWARD);
    motorR->run(BACKWARD);
  } else if (detectL && !detectM) {
    Serial.println("slight LEFT turn");
    motorL->setSpeed(slightTurnSpeed);
    motorR->setSpeed(slightTurnSpeed);
    motorL->run(BACKWARD);
    motorR->run(BACKWARD);
  } else if (detectR && !detectM) {
    Serial.println("slight RIGHT turn");
    motorL->setSpeed(slightTurnSpeed);
    motorR->setSpeed(slightTurnSpeed);
    motorL->run(FORWARD);
    motorR->run(FORWARD);
  }
  // Line lost: search for line
  else if (!detectL && !detectM && !detectR) {
    Serial.println("no line detected - searching");
    if (turning == LEFT || turning == NONE) {
      motorL->setSpeed(searchSpeed);
      motorR->setSpeed(searchSpeed);
      motorL->run(BACKWARD);
      motorR->run(BACKWARD);
    } else if (turning == RIGHT) {
      motorL->setSpeed(searchSpeed);
      motorR->setSpeed(searchSpeed);
      motorL->run(FORWARD);
      motorR->run(FORWARD);
    }
  }

  // Print sensor values for debugging
  Serial.print(detectL); Serial.print(" ");
  Serial.print(detectM); Serial.print(" ");
  Serial.println(detectR);

  delay(50);
}