import processing.serial.*;

Serial serial;
int a = 1;

void setup(){
  background(#FFFFFF);
  rect(100, 0, 200, 200);
  rect(0, 0, 100, 200);
  size(200, 200);
  serial = new Serial(this, Serial.list()[0], 9600);
}

void draw()
{
  serial.write(a);
  print(a);
  delay(200);
}

void mouseClicked(){
  if (mouseX < 100) a = 1;
  else a = 2;
}
