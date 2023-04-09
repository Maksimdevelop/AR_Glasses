/*0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&0xff&*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


Adafruit_SSD1306 display(4);
//Adafruit_SSD1306 display(128, 64, &Wire, 4, 400000UL, 100000UL);
const byte NELEMENTS = 8;
const uint16_t WIDTH = 16;
const uint16_t HEIGHT = 16;
bool reset = false;



class drElem
{
  int i1 = 0; 
  int i2 = 0; 
  int i3 = 0; 
  int i4 = 0; 
  int ch = 0;
  String s1 = ""; 
  String s2 = ""; 
  String s3 = "";
  String s4 = "";
  
  
  public: void _init_(int choose, int in1, int in2, int in3, int in4, String st1, String st2, String st3, String st4)
  {
      ch = choose;
      i1 = in1;
      i2 = in2;
      i3 = in3;
      i4 = in4;
      s1 = st1;
      s2 = st2;
      s3 = st3;
      s4 = st4;
  }

  
  //public: void choosenDrawFunction(int funcnum, int i1, int i2, int i3, int i4, String s1, String s2, String s3, String s4){
public: void choosenDrawFunction()
  {
    switch(ch)
    {
      case -1://reset
        reset = true;
        break;
      case 0://nothing
        break;
      case 1://4 strokes
      {
        String temp = s1;
        display.println(temp);
        temp = s2;
        display.println(temp);
        temp = s3;
        display.println(temp);
        temp = s4;
        display.println(temp);
        break;
      }
      case 2://xy stroke
      {
        String temp = s1;
        display.setCursor(i1, i2);
        display.println(temp);
        break;
      }
      case 3://line
      {
        display.drawLine(i1, i2, i3, i4, 1);
        break;
      }
      case 4://rect
      {
        display.drawRect(i1, i2, i3, i4, 1);
        break;
      }
      case 5://fillrect
      {
        display.fillRect(i1, i2, i3, i4, 1);
        break;
      }
      case 6://circle
      {
        display.drawCircle(i1, i2, i3, 1);
        break;
      }
      case 7:
      {
        int cntd = 0;
        uint8_t bitmap[256];
        String bruh = "";
         for (int i = 0; i < s1.length(); i++)
          {
            if (s1[i] != '&')
            {
              bruh += s1[i];
            }
            else
            {
              bitmap[cntd] = bruh.toInt();
              cntd++;
              Serial.write(cntd);
            }
          }
        display.drawBitmap(i1, i2, bitmap, WIDTH, HEIGHT, 1);
        break;
      }
      default:
      {
        break;
      }
    }
  }
};


//NELEMENTS * Режимов
String input = "";
int counter = 0;
drElem elems[NELEMENTS];

//Предустановки
void setup() 
{
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  display.cp437(true);
  for (int i = 0; i < NELEMENTS; i++)
    elems[i] = drElem();
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.flush(); 
  feedback();
}


void loop() 
{
  RESET();
  comporttext();
  draw();
  feedback();
  display.flush(); 
  delay(20);
}


//Отрисовка
void draw()
{
  //Очищаем экран
  display.fillScreen(0x000000);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  //Выводим поэлементно
  for (int i = 0; i < NELEMENTS; i++)
  {
    elems[i].choosenDrawFunction();
  }
  display.display();
}


//Запрос порта
void comporttext()
{
  if (Serial.available())
  {
    String s = Serial.readString();
    String inp_array[9];
    int cnt = 0;
    for (int i = 0; i < s.length(); i++)
    {
      if (s[i] != ':')
      {
        inp_array[cnt] += s[i];
      }
      else
      {
        cnt++;
      }
    }
    elems[counter]._init_(inp_array[0].toInt(), inp_array[1].toInt(),
      inp_array[2].toInt(), inp_array[3].toInt(), inp_array[4].toInt(), inp_array[5], inp_array[6], inp_array[7], inp_array[8]);
    counter++;
  }
}

void RESET()
{
  if (reset)
  {
    counter = 0;
    for (int i = 0; i < NELEMENTS; i++)
    {
      elems[i]._init_(0, 0, 0, 0, 0, "", "", "", "");
    }
    reset = false;
  }
}

void feedback()//обратная связь
{
  digitalWrite(2, HIGH);
  if (digitalRead(3)) {
      Serial.write('1');
    }
    else{
      Serial.write('0');
    }
}
