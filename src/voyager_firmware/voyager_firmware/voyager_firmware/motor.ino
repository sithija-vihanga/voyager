void drive(int LFrontSpeed, int LRearSpeed, int RFrontSpeed, int RRearSpeed)
{ 
  int L_front_speed_out = mapFloat(L_front_speed_out);
  int R_front_speed_out = mapFloat(R_front_speed_out);
  int L_rear_speed_out  = mapFloat(L_rear_speed_out);
  int R_rear_speed_out  = mapFloat(R_rear_speed_out);


  // Speed Controls
  pwm.setPWM(4, 0, L_front_speed_out ); // Left front
  pwm.setPWM(5, 0, R_front_speed_out ); // Right front
  pwm.setPWM(6, 0, R_rear_speed_out ); // Right rear
  pwm.setPWM(7, 0, L_rear_speed_out ); // Left rear

  if (LFrontSpeed > 0)
  {
    pwm.setPWM(8,  0, 0 );        // Left front - forward
    pwm.setPWM(9,  0, 4000 );
    pwm.setPWM(14, 0, 0 );        // Left rear - forward
    pwm.setPWM(15, 0, 4000 );
    
  }
  else
  {
    pwm.setPWM(8,  0, 4000 );        // Left front - reverse
    pwm.setPWM(9,  0, 0 );
    pwm.setPWM(14, 0, 4000 );        // Left rear - reverse
    pwm.setPWM(15, 0, 0 );
    
  }

  if (RFrontSpeed > 0)
  {

    pwm.setPWM(10, 0, 4000 );       // Right rear - forward
    pwm.setPWM(11, 0, 0 );
    pwm.setPWM(12, 0, 4000 );       // Right front - forward
    pwm.setPWM(13, 0, 0 );
   

  }
  else
  {
    pwm.setPWM(10, 0, 0 );       // Right rear - reverse
    pwm.setPWM(11, 0, 4000 );
    pwm.setPWM(12, 0, 0 );       // Right front - reverse
    pwm.setPWM(13, 0, 4000 );
    
  }

}
void reverse(int speed)
{
  int speed_out = map(speed, 0, 255, 0, 4096);
  // Speed Controls
  pwm.setPWM(4, 0, speed_out );
  pwm.setPWM(5, 0, speed_out );
  pwm.setPWM(6, 0, speed_out );
  pwm.setPWM(7, 0, speed_out );

  // Motor 1 controls
  pwm.setPWM(8,   0, 4000 );
  pwm.setPWM(9,   0, 0 );
  pwm.setPWM(10,  0, 0 );
  pwm.setPWM(11,  0, 4000 );

  //Motor 2 controls
  pwm.setPWM(12, 0, 0 );
  pwm.setPWM(13, 0, 4000 );
  pwm.setPWM(14, 0, 4000 );
  pwm.setPWM(15, 0, 0 );

}

void forward(int speed)
{
  int speed_out = map(speed, 0, 255, 0, 4096);
  // Speed Controls
  pwm.setPWM(4, 0, speed_out );
  pwm.setPWM(5, 0, speed_out );
  pwm.setPWM(6, 0, speed_out );
  pwm.setPWM(7, 0, speed_out );

  // Motor 1 controls
  pwm.setPWM(8,  0, 0 );
  pwm.setPWM(9,  0, 4000 );
  pwm.setPWM(10, 0, 4000 );
  pwm.setPWM(11, 0, 0 );

  // Motor 2 controls
  pwm.setPWM(12, 0, 4000 );
  pwm.setPWM(13, 0, 0 );
  pwm.setPWM(14, 0, 0 );
  pwm.setPWM(15, 0, 4000 );

 }

 void stop()
 {
   // Motor 1 controls
  pwm.setPWM(8,  0, 0 );
  pwm.setPWM(9,  0, 0 );
  pwm.setPWM(10, 0, 0 );
  pwm.setPWM(11, 0, 0 );

  // Motor 2 controls
  pwm.setPWM(12, 0, 0 );
  pwm.setPWM(13, 0, 0 );
  pwm.setPWM(14, 0, 0 );
  pwm.setPWM(15, 0, 0 );
 }

 