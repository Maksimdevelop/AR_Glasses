#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//Экземпляр "дисплея"
//https://adafruit.github.io/Adafruit_SSD1306/html/class_adafruit___s_s_d1306.html)
Adafruit_SSD1306 display(4);


//Преднастройки
void setup() 
{
  //Бодрейт
  Serial.begin(115200);
  //Запуск экрана
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}


//Метод-цикл
void loop() 
{
  //ПОПРОБУЙ ТАК!
  refresh();
  if(Serial.available())
  {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.display();
    delay(100);
    //display.println(Serial.read());
  }
}


//Очистить экран
void refresh()
{
  display.flush();
  display.clearDisplay();
  display.setCursor(0,0);
}
