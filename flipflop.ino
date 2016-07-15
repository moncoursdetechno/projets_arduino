boolean __ardublockDigitalRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return digitalRead(pinNumber);
}



void setup()
{
  pinMode( 8 , OUTPUT);
  pinMode( 7 , OUTPUT);
}

void loop()
{
  if (__ardublockDigitalRead(2))
  {
    digitalWrite(8 , HIGH);
    digitalWrite(7 , LOW);
  }
  else
  {
    digitalWrite(8 , LOW);
    digitalWrite(7 , HIGH);
  }
}


