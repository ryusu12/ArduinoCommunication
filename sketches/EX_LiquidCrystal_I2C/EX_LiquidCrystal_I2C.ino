#include <Wire.h>
#include <LiquidCrystal_I2C.h> //LiquidCrystal 라이브러리
LiquidCrystal_I2C lcd(0x20, 16, 2) //lcd 객체선언

void setup()
{
  lcd.init(); //lcd 초기화
}

void loop()
{
  lcd.backlight(); //백라이트 켬
  lcd.setCursor(2, 0);
  lcd.print("Hello world");
  delay(1000);
  lcd.noBacklight();   //백라이트 끔
  lcd.clear();         //내용을 모두 지운 후 (0,0)으로 커서 이동
  delay(1000);
}
