#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// initialize motors
Adafruit_DCMotor *motorL = AFMS.getMotor(1);
Adafruit_DCMotor *motorR = AFMS.getMotor(2);

int speedL = 50;
int speedR = 50;

int sensorL = A0;
int sensorM = A1;
int sensorR = A2;

int thresholdVoltageLow = 100;
int thresholdVoltageHigh = 700;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  Serial.println("pie");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  motorL->setSpeed(speedL);
  motorR->setSpeed(-speedR);
  motorL->run(FORWARD);
  motorR->run(FORWARD);

}

void loop() {

  // test different motor speeds for the right motor
  motorL -> setSpeed(50);
  motorR -> setSpeed(-40);
  delay(3000);
  motorR -> setSpeed(0);
  delay(3000);
  motorR -> setSpeed(-30);
  delay(3000);
  motorR -> setSpeed(0);
  delay(3000);
  motorR -> setSpeed(-20);

  // stop forever (i did this so i wouldnt have to comment out all the real code)
  while(1){
    delay(1000);
  }

  if(analogRead(sensorL)<thresholdVoltageLow){ // left sensor on line -> need to turn left
    Serial.println("left");
    speedL = -50;
    // speedL -= 10;
    // speedR += 10
    Serial.print(" ");
    Serial.print(speedL);
    Serial.print(" ");
    Serial.print(speedR);
    Serial.println("");
  }else if (analogRead(sensorR)<thresholdVoltageLow) {
    Serial.println("right");
    speedR = -50;
    // speedR -= 10;
    // speedL += 10;
    Serial.print(" ");
    Serial.print(speedL);
    Serial.print(" ");
    Serial.print(speedR);
    Serial.println("");
  }else if (analogRead(sensorM)<thresholdVoltageLow){
    Serial.println("middle");
    speedR = 50;
    speedL = 50;
    Serial.print(" ");
    Serial.print(speedL);
    Serial.print(" ");
    Serial.print(speedR);
    Serial.println("");
  }
  
  motorL->setSpeed(speedL);
  motorR->setSpeed(-speedR);
  
  // motorL->setSpeed(100);
  // motorR->setSpeed(100);

  // Serial.print(analogRead(sensorL));
  // Serial.print(" ");
  // Serial.print(analogRead(sensorM));
  // Serial.print(" ");
  // Serial.print(analogRead(sensorR));

  Serial.print(" ");
  Serial.print(speedL);
  Serial.print(" ");
  Serial.print(speedR);
  Serial.println("");

  

  delay(50);

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