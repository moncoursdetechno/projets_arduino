#include <Wire.h>
#include <rgb_lcd.h>

boolean __ardublockDigitalRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return digitalRead(pinNumber);
}


//libraries at http://duinoedu.com/dl/lib/grove/EDU_LCD_RGB_Backlight_Grove/ 
rgb_lcd monRgb;

void setup()
{
  monRgb.branch();
}

void loop()
{
  if (__ardublockDigitalRead(2))
  {
    monRgb.placerCurseurEn(0,0);
    monRgb.ecrire("acces autorise" );
  }
  else
  {
    monRgb.placerCurseurEn(0,0);
    monRgb.ecrire("saisir code" );
  }
}


