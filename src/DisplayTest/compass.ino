#include <Wire.h> // подключаем I2C библиотеку
#define addr 0x1E // I2C 7-битный адрес датчика HMC5883

void setup() {
    Serial.begin(115200); // инициализация последовательного порта 
    Wire.begin(); // инициализация I2C
  
    // Задаём режим работы датчика HMC5883:
    Wire.beginTransmission(addr);
    Wire.write(0x00); // выбираем регистр управления CRA (00)
    Wire.write(0x70); // записываем в него 0x70 [усреднение по 8 точкам, 15 Гц, нормальные измерения]
    Wire.write(0xA0); // записываем в регистр CRB (01) 0xA0 [чувствительность = 5]
    Wire.write(0x00); // записываем в регистр Mode (02) 0x00 [бесконечный режим измерения]
    Wire.endTransmission();
    Serial.write("hhh");
}

void loop() { 
  
  Wire.beginTransmission(addr);
  Wire.write(0x03); // переходим к регистру 0x03
  Wire.endTransmission();
  
  Wire.requestFrom(addr, 6); // запрашиваем 6 байтов
  while( Wire.available() )  
  { 
    int h = Wire.read(); // старший байт значения по оси X
    int l = Wire.read(); // младший байт значения по оси X
    int x = word(h, l);  // объединяем в двухбайтовое число

    int y = Wire.read(); // старший байт значения по оси Y
    y = y << 8; // сдвигаем влево на 8 битов
    y = y | Wire.read(); // объединяем с младшим байтом по OR

    int z = Wire.read() << 8; // читаем байт и сдвигаем влево на 8 битов
    z |= Wire.read(); // сокращённый синтаксис операции OR

    Serial.write("X = ");  
    Serial.write(x); 
    Serial.write("\n");  
    Serial.write("Y = ");  
    Serial.write(y); 
    Serial.write("\n"); 
    Serial.write("Z = ");  
    Serial.write(z); 
    Serial.write("\n");    
  }
    delay(100);
}
