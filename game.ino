/*
   Frederic Brady Ward LED Matrix Dot Game Manipulation
   Based on the following library:
   GitHub | riyas-org/max7219  https://github.com/riyas-org/max7219
*/
#include <MaxMatrix.h>
int DIN = 7;   // DIN pin of MAX7219 module
int CLK = A3;   // CLK pin of MAX7219 module
int CS = 8;    // CS pin of MAX7219 module
int rotationPin= A0;
int data= 0;
int maxInUse = 1; //How many boards?!

//Dot position variables (r is the x position, too lazy to change)
int r1= 0;
int y1= 0;
int r2= 0;
int y2= 0;
int r3= 0;
int y3= 0;
int r4= 0;
int y4= 0;
int r5= 0;
int y5= 0;

//Dot t/f appeared?
boolean dot1= false;
boolean dot2= false;
boolean dot3= false;
boolean dot4= false;
boolean dot5= false;

int intervalone= 5250;
int intervaltwo= 500;

//Dot appear intervals and last appear time
int appearspeedone= 3600;
int appearspeedtwo= 3000;
int appearspeedthree= 2500;
int appearspeedfour= 2000;
int appearspeedfive= 1800;
unsigned long previousone= 0;
unsigned long previoustwo= 0;
unsigned long previousthree= 0;
unsigned long previousfour= 0;
unsigned long previousfive= 0;

//Dot drop intervals and last drop time
int dropspeedone= 400;
int dropspeedtwo= 350;
int dropspeedthree= 250;
int dropspeedfour= 200;
int dropspeedfive= 150;
unsigned long lastdropone= 0;
unsigned long lastdroptwo= 0;
unsigned long lastdropthree= 0;
unsigned long lastdropfour= 0;
unsigned long lastdropfive= 0;

unsigned long current= 0; //Current time

MaxMatrix m(DIN, CS, CLK, maxInUse);

char sad[] =     {8, 8,             //Creates the sad face for end game
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
  m.setDot(data, 7, true); //Did not give player a y variable as should be stuck to line 7

  //Appear checks for the dots to start dropping are below
  if(current-previousone >= appearspeedone) //Can rinse and repeat these if statements for additional dots
  {
    previousone= current; //Sets the time for the last time the dot appeared
    lastdropone= current; //Resets the time for the drop time
    r1= random(8); //Picks a random spot on x axis to start
    m.setDot(r1, y1, true); //Sets the dot at the top and random spot on x axis
    dot1= true; //Starts drop "loop"
  }
  if(current-previoustwo >= appearspeedtwo)
  {
    previoustwo= current;
    lastdroptwo= current;
    r2= random(8);
    m.setDot(r2, y2, true);
    dot2= true;
  }
  if(current-previousthree >= appearspeedthree)
  {
    previousthree= current;
    lastdropthree=current;
    r3= random(8);
    m.setDot(r3, y3, true);
    dot3= true;
  }
  if(current-previousfour >= appearspeedfour)
  {
    previousfour= current;
    lastdropfour=current;
    r4= random(8);
    m.setDot(r4, y4, true);
    dot4= true;
  }
  if(current-previousfive >= appearspeedfive)
  {
    previousfive= current;
    lastdropfive=current;
    r5= random(8);
    m.setDot(r5, y5, true);
    dot5= true;
  }


  //All of the drop "loops" are below, rinse and repeat these AS WELL AS THE FIRST ONES TO CREATE MORE DOTS, THESE ARE REQUIRED TO HAVE THE DOT DROP DOWN THE SCREEN
  if(dot1) //Checks to see if there is a dot
  {
    if(r1==data && y1==7) //Checks to see if the dot hit the player
    {
      loseGame(); //Runs loseGame function
    }
    else
    {
    m.setDot(r1, y1, true); //Sets the dot if it does not collide with player
    }
    if(current-lastdropone >= dropspeedone) //Checks the drop interval
    {
      lastdropone= current; //Resets the last drop time
      y1++; //Increases the y position of the dot
      if(y1==8) //Checks to see if the dot is off the board
      {
        dot1=false; //Turns off the drop sequence
        y1=0; //Resets the y position of the dot
      }
    }
  }

  if(dot2)
  {
    if(r2==data && y2==7)
    {
      loseGame();
    }
    else
    {
    m.setDot(r2, y2, true);
    }
    if(current-lastdroptwo >= dropspeedtwo)
    {
      lastdroptwo= current;
      y2++;
      if(y2==8)
      {
        dot2=false;
        y2=0;
      }
    }
  }

  if(dot3)
  {
    if(r3==data && y3==7)
    {
      loseGame();
    }
    else
    {
    m.setDot(r3, y3, true);
    }
    if(current-lastdropthree >= dropspeedthree)
    {
      lastdropthree= current;
      y3++;
      if(y3==8)
      {
        dot3=false;
        y3=0;
      }
    }
  }

  if(dot4)
  {
    if(r4==data && y4==7)
    {
      loseGame();
    }
    else
    {
    m.setDot(r4, y4, true);
    }
    if(current-lastdropfour >= dropspeedfour)
    {
      lastdropfour= current;
      y4++;
      if(y4==8)
      {
        dot4=false;
        y4=0;
      }
    }
  }

  if(dot5)
  {
    if(r5==data && y5==7)
    {
      loseGame();
    }
    else
    {
    m.setDot(r5, y5, true);
    }
    if(current-lastdropfive >= dropspeedfive)
    {
      lastdropfive= current;
      y5++;
      if(y5==8)
      {
        dot5=false;
        y5=0;
      }
    }
  }
  
  
}

void dataCheck() //Thought I would use this more often to map the player but runs fairly smooth only being called once
{
  data= analogRead(rotationPin); //Reads rotationPin data
  data= map(data, 0, 1023, 0, 7); //Maps that data
}

void loseGame() //Saves rewriting the code for each dot
{
    current= millis();
    m.clear();
    m.writeSprite(0, 0, sad);
    delay(2000); //Lets you see sadness for 2 seconds
    //Resets all the dots and times
    y1=0;
    y2=0;
    y3=0;
    y4=0;
    dot1=false;
    dot2=false;
    dot3=false;
    dot4=false;
    dot5=false;
    previousone= current;
    previoustwo= current;
    previousthree= current;
    previousfour= current;
    lastdropone= current;
    lastdroptwo= current;
    lastdropthree= current;
    lastdropfour= current;
    lastdropfive= current;
}
