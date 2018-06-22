/*
      8x8 LED Matrix MAX7219 Example 01
   by Dejan Nedelkovski, www.HowToMechatronics.com
   Based on the following library:
   GitHub | riyas-org/max7219  https://github.com/riyas-org/max7219
*/
#include <MaxMatrix.h>
int DIN = 7;   // DIN pin of MAX7219 module
int CLK = A3;   // CLK pin of MAX7219 module
int CS = 8;    // CS pin of MAX7219 module
int rotationPin= A0;
int data= 0;
int maxInUse = 1;

int r1= 0;
int y1= 0;
int r2= 0;
int y2= 0;
int r3= 0;
int y3= 0;
int r4= 0;
int y4= 0;

int intervalone= 5250;
int intervaltwo= 500;


unsigned long current= 0;
unsigned long previousone= 0;
unsigned long previoustwo= 0;
boolean dot= false;
MaxMatrix m(DIN, CS, CLK, maxInUse);

char sad[] =     {8, 8,
                  B00111100,
                  B01000010,
                  B10110101,
                  B10010001,
                  B10010001,
                  B10110101,
                  B01000010,
                  B00111100
                 };

void setup() {
  Serial.begin(9600);
  m.init(); // MAX7219 initialization
  m.setIntensity(8); // initial led matrix intensity, 0-15
}
void loop() {
  m.clear();
  current= millis();
  dataCheck();
  m.setDot(data, 7, true);
  if(current-previousone >= intervalone)
  {
    previousone= current;
    previoustwo= current;
    r1= random(8);
    m.setDot(r1, 0, true);
    dot= true;
  }
  if(dot)
  {
    if(r1==data && y1==7)
    {
      m.clear();
      m.writeSprite(0, 0, sad);
      delay(2000);
      y1=0;
      dot=false;
      previousone= current;
      previoustwo= current;
    }
    else
    {
    m.setDot(r1, y1, true);
    }
    if(current-previoustwo >= intervaltwo)
    {
      previoustwo= current;
      y1++;
      if(y1==8)
      {
        dot=false;
        y1=0;
      }
    }
  }
  
  
}

void dataCheck()
{
  data= analogRead(rotationPin);
  data= map(data, 0, 1023, 0, 7);
}
