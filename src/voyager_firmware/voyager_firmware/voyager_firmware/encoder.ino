void updateEncoderFrontRight() {
  int stateA = digitalRead(FrontRightencoderA);
  int stateB = digitalRead(FrontRightencoderB);

  if (stateA == stateB) {
    encoderPosition[0]++;
  } else {
    encoderPosition[0]--;
  }
}

void updateEncoderFrontLeft() {
  int stateA = digitalRead(FrontLeftencoderA);
  int stateB = digitalRead(FrontLeftencoderB);

  if (stateA == stateB) {
    encoderPosition[1]++;
  } else {
    encoderPosition[1]--;
  }
}

void updateEncoderRearRight() {
  int stateA = digitalRead(RearRightencoderA);
  int stateB = digitalRead(RearRightencoderB);

  if (stateA == stateB) {
    encoderPosition[2]++;
  } else {
    encoderPosition[2]--;
  }
}

void updateEncoderRearLeft() {
  int stateA = digitalRead(RearLeftencoderA);
  int stateB = digitalRead(RearLeftencoderB);

  if (stateA == stateB) {
    encoderPosition[3]++;
  } else {
    encoderPosition[3]--;
  }
}