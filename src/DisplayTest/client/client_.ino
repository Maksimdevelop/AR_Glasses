
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

byte inp;
int cx = 64, cy = 16;

void setup() 
{
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

}

void loop() 
{
  if (Serial.available()) {
    inp = Serial.read() - '0';
    cx += inp;
    }
  }
  
  display.clearDisplay();
  display.drawCircle(cx, cy, 3, 1);
  display.display();
}
