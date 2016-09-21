int _ABVAR_1_potar = 0 ;

void setup()
{
  pinMode( 3 , OUTPUT);
}

void loop()
{
  _ABVAR_1_potar = analogRead(A0) ;
  analogWrite(3 , map ( _ABVAR_1_potar , 0 , 1023 , 0 , 255 ) );
}


