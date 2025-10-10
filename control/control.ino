#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// initialize motors
Adafruit_DCMotor *motorL = AFMS.getMotor(1);
Adafruit_DCMotor *motorR = AFMS.getMotor(2);

int speedL = 31;
int speedR = 30;

int sensorL = A0;
int sensorM = A1;
int sensorR = A2;

int thresholdVoltageLow = 100;
int thresholdVoltageHigh = 700;

typedef enum {
  NONE,
  RIGHT,
  LEFT
} TurnState;

TurnState turning = NONE;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  motorL->setSpeed(speedL);
  motorR->setSpeed(speedR);
  motorL->run(FORWARD);
  motorR->run(BACKWARD);

}

void loop() {

  boolean detectL = analogRead(sensorL)<thresholdVoltageLow;
  boolean detectR = analogRead(sensorR)<thresholdVoltageLow;
  boolean detectM = analogRead(sensorM)<thresholdVoltageLow;

  /* ---------------- this stuff does not work -------------- */
  if(turning == LEFT){  // if it is turning left sharply, keep turning until the L sensor is off
    if (detectM && !detectL){
      turning = NONE;
    }
  }else if(turning == RIGHT){ // if it is turning right sharply, keep turning until the R sensor is off
    if (detectM && !detectR){
      turning = NONE;
    }
  }else if (detectL && detectM){ // is it a sharp left turn?
    Serial.println("left middle");
    motorL->run(BACKWARD);
    motorR->run(BACKWARD);
    turning = LEFT;
  }else if (detectR && detectM){ // is it a sharp right turn?
    Serial.println("right middle");
    motorL->run(FORWARD);
    motorR->run(FORWARD);
    turning = RIGHT;
  /* ---------------- this stuff works -------------- */
  }else if (detectM){ // on the line
    Serial.println("middle");
    motorL->run(FORWARD);
    motorR->run(BACKWARD);
  }else if(detectL){ // a little bit left
    Serial.println("left");
    motorL->run(BACKWARD);
    motorR->run(BACKWARD);
  }else if (detectR) { // a little bit right
    Serial.println("right");
    motorL->run(FORWARD);
    motorR->run(FORWARD); // right goes backwards
  }
  
  delay(50);

  Serial.print(detectL);
  Serial.print(" ");
  Serial.print(detectR);
  Serial.print(" ");
  Serial.print(detectM);


  Serial.println("");

  // sample code from example
  /*
   uint8_t i;

  Serial.print("tick");

  motorL->run(FORWARD);
  for (i=0; i<255; i++) {
    motorL->setSpeed(i);
    delay(10);
  }
  for (i=255; i!=0; i--) {
    motorL->setSpeed(i);
    delay(10);
  }

  Serial.print("tock");

  motorL->run(BACKWARD);
  for (i=0; i<255; i++) {
    motorL->setSpeed(i);
    delay(10);
  }
  for (i=255; i!=0; i--) {
    motorL->setSpeed(i);
    delay(10);
  }

  Serial.print("tech");
  motorL->run(RELEASE);
  delay(1000);
  */
 

  


}