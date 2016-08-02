#include <Keypad.h>

//libraries at http://duinoedu.com/dl/lib/grove/EDU_Keypad_Dupont/ 
Keypad keypad;

void setup()
{
  keypad.brancher(2,8);
  keypad.activerInfos();
  keypad.writePassword("1234");
  pinMode( 13 , OUTPUT);
}

void loop()
{
  if (keypad.testPasswordOk())
  {
    digitalWrite(13 , HIGH);
    delay( 5000 );
  }
  else
  {
    digitalWrite(13 , LOW);
  }
}


