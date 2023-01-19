#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Экран
Adafruit_SSD1306 display(128, 64, &Wire, -1);

//Побайтовый массив на вывод 
//(zeenarg): ОН ВИДАТЬ САМЫЙ ЖИРНЫЙ В ОПЕРАТИВКЕ, И НЕ ВИЖУ НИ ОДНОГО МЕТОДА КУДА ЕГО МОЖНО ЗАПИХНУТЬ)
//(zeenarg): https://adafruit.github.io/Adafruit_SSD1306/html/class_adafruit___s_s_d1306.html)
/*static const byte image_data_Saraarray[64]=
{
0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,
0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,
0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,
0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe
};*/


//Предварительный настройки
void setup() 
{
  //Бодрейт
  Serial.begin(115200);

  //Проверка связи с экраном
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    //Вывод ошибки.
    Serial.println(F("SSD1306 allocation failed"));
    //Уходим в небытье
    //(zeenarg): ТАК ПРИВЫЧНЕЙ, КОГДА ЧЕРЕЗ WHILE, А В БЕСК. ЦИКЛЫ НУЖНО ХОТЯ БЫ ЧТО-ТО КИНУТЬ
    while(true)
    {
      delay(500);
      Serial.println(F("I'am here"));
    }
  }
  delay(2000); 

  //Чистим, пишем, кидаем на экран
  display.clearDisplay();
  display.write("Hello World!");
  display.display();
}


//Повтор
void loop() 
{
  delay(500);
}
