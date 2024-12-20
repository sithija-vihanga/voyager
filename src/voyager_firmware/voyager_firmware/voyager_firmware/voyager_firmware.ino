// Author : Sithija Ranaraja

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

#define COMMAND_TIMEOUT 1000

uint8_t servonum = 0;

const int FrontRightencoderA = 6;  // Pin for encoder A
const int FrontRightencoderB = 7;  // Pin for encoder B

const int FrontLeftencoderA = 8;  // Pin for encoder A
const int FrontLeftencoderB = 9;  // Pin for encoder B

const int RearRightencoderA = 4;  // Pin for encoder A
const int RearRightencoderB = 5;  // Pin for encoder B

const int RearLeftencoderA = 2;  // Pin for encoder A
const int RearLeftencoderB = 3;  // Pin for encoder B

int ticksPerRotation       = 994;
int   encoderPosition[4]   = {0, 0, 0, 0};
float wheelRotations[4]    = {0.0, 0.0, 0.0};

String inputString = ""; 
const char delimiter = ','; 

float commands[2] = {0.0, 0.0};

unsigned long command_timestamp;
unsigned long current_timestamp;

void setup() {

  Serial.begin(115200);
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  pinMode(FrontRightencoderA, INPUT);
  pinMode(FrontRightencoderB, INPUT);
  pinMode(FrontLeftencoderA,  INPUT);
  pinMode(FrontLeftencoderB,  INPUT);
  pinMode(RearRightencoderA,  INPUT);
  pinMode(RearRightencoderB,  INPUT);
  pinMode(RearLeftencoderA,   INPUT);
  pinMode(RearLeftencoderB,   INPUT);

  attachInterrupt(digitalPinToInterrupt(FrontRightencoderA),    updateEncoderFrontRight,   CHANGE);
  attachInterrupt(digitalPinToInterrupt(FrontLeftencoderA),     updateEncoderFrontLeft,    CHANGE);
  attachInterrupt(digitalPinToInterrupt(RearRightencoderA),     updateEncoderRearRight,    CHANGE);
  attachInterrupt(digitalPinToInterrupt(RearLeftencoderA),      updateEncoderRearLeft,     CHANGE);

}

void loop() {
  if(Serial.available() > 0)
  {
    command_timestamp = millis();
    inputString = Serial.readStringUntil('\n');

    int startIndex = 0;
    int i = 0;
    int endIndex = inputString.indexOf(delimiter);
    while (endIndex != -1) {
      String element = inputString.substring(startIndex, endIndex);
      commands[i] = element.toInt();
      i = i+1;
      startIndex = endIndex + 1;
      endIndex = inputString.indexOf(delimiter, startIndex);
    }
    Serial.print("commands ");
    Serial.print(commands[0]);
    Serial.print(" , ");
    Serial.println(commands[1]);

    drive(commands[0], commands[1]);
  }
  else
  {
    current_timestamp = millis();
    if (current_timestamp - command_timestamp > COMMAND_TIMEOUT)
    {
      stop();
    }
  }
  
  // for( int angle =0; angle<181; angle +=1){
  //         delay(10);
  //         pwm.setPWM(0, 0, angleToPulse(angle) );
  //   }
  // delay(1000);

  // for (int i = 0; i<4; i++)
  // {
  //   wheelRotations[i] = encoderPosition[i]/(ticksPerRotation + 1e-10);
  // }
  // Serial.print(wheelRotations[0]);
  // Serial.print(" ");
  // Serial.print(wheelRotations[1]);
  // Serial.print(" ");  // Serial.print(wheelRotations[2]);
  // Serial.print(" ");
  // Serial.print(wheelRotations[3]);
  // Serial.println();
  // delay(10);
}







