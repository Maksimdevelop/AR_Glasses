#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//Пин сброса
Adafruit_SSD1306 display(4);


//Преднастройки
void setup() 
{
  //Бодрейт
  Serial.begin(115200);
  //Запуск экрана
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}


//Метод-цикл
void loop() 
{
  //display.flush(); — возможно надо вычищать поток с дисплеем
  if(Serial.available())
  {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.display();
    delay(100);
    //display.println(Serial.read());
  }
}
