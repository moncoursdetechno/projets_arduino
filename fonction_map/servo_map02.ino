#include <Servo.h>

int _ABVAR_1_potar = 0 ;
Servo servo_pin_3;

void setup()
{
  servo_pin_3.attach(3);
}

void loop()
{
  _ABVAR_1_potar = analogRead(A0) ;
  servo_pin_3.write( map ( _ABVAR_1_potar , 0 , 1023 , 0 , 180 )  );
}


