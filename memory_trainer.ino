#include <Adafruit_NeoPixel.h>

#define rgb 6
#define gameover 1
#define burnrandom 2
#define scankey 3
#define blink 4
int button[]={8,9,10,11,12};//按键引脚
int led[]={2,3,4,5};		//led引脚
int rgbs[4][3];		
int burn[50];	
//int red[50];
//int green[50];
//int blue[50];
int times = 0;
int state = 1;
int keyvalue = 0;
int a = 0;
int b = 0;
int keypress = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, rgb, NEO_RGB + NEO_KHZ800);

void flash1()					//初始化动画
{
  digitalWrite(led[0],LOW);
  strip.setPixelColor(0,255,0,0);
  strip.show();
  delay(100);
  digitalWrite(led[1],LOW);
  strip.setPixelColor(1,255,0,0);
  strip.show();
  delay(100);
  digitalWrite(led[2],LOW);
  strip.setPixelColor(2,255,0,0);
  strip.show();
  delay(100);
  digitalWrite(led[3],LOW);
  strip.setPixelColor(3,255,0,0);
  strip.show();
  delay(100);
  digitalWrite(led[3],HIGH);
  strip.setPixelColor(3,0,0,0);
  strip.show();
  delay(100);
  digitalWrite(led[2],HIGH);
  strip.setPixelColor(2,0,0,0);
  strip.show();
  delay(100);
  digitalWrite(led[1],HIGH);
  strip.setPixelColor(1,0,0,0);
  strip.show();
  delay(100);
  digitalWrite(led[0],HIGH);
  strip.setPixelColor(0,0,0,0);
  strip.show();
}
int flash2()				
{
  int a = 5;
  while(a--)
  {
	digitalWrite(led[0],LOW);
    digitalWrite(led[1],LOW);
  	digitalWrite(led[2],LOW);
 	digitalWrite(led[3],LOW);
    strip.setPixelColor(0,0,255,0);
    strip.setPixelColor(1,0,255,0);
    strip.setPixelColor(2,0,255,0);
    strip.setPixelColor(3,0,255,0);
    strip.show();
  	delay(100);
    digitalWrite(led[0],HIGH);
  	digitalWrite(led[1],HIGH);
  	digitalWrite(led[2],HIGH);
 	digitalWrite(led[3],HIGH);
    strip.setPixelColor(0,0,0,0);
    strip.setPixelColor(1,0,0,0);
    strip.setPixelColor(2,0,0,0);
    strip.setPixelColor(3,0,0,0);
    strip.show();
    delay(100);

  }
}
void setup()
{
  strip.begin();
  strip.show();
  a = 4;
  while(a--)
  { 
     pinMode(led[a],OUTPUT);
     digitalWrite(led[a],HIGH);
  }
  a = 5;
  while(a--)
  {
    pinMode(button[a],INPUT_PULLUP);
  }
  digitalWrite(13,HIGH);
  digitalWrite(6,HIGH);
  pinMode(13,OUTPUT);
  pinMode(6,OUTPUT);
  randomSeed(analogRead(0));
  flash1();
}

void loop()
{
 	if(state == gameover)
    {
        
      	digitalWrite(13,LOW);
        digitalWrite(6,HIGH);
    	times = 0;
        while(digitalRead(button[0]));
      	if(digitalRead(button[0]) == 0)
        {
          	
        	state = burnrandom;
          	
        }
    }
	if(state == burnrandom)
    {
      flash1();
      delay(200);
      digitalWrite(13,HIGH);
      digitalWrite(6,LOW);
      a=4;
      while(a--)
      {
      	b = 3;
        while(b--)
        rgbs[a][b]=int(random(0,255));
      }
    	times++;
      	a = times;
      	while(a--)
        {
        	burn[a]=int(random(1,5));
      //   	red[a]=int(random(0,255));
      //   	green[a]=int(random(0,255));
      //   	blue[a]=int(random(0,255));
        }
        state = blink;
        a = times;
    }
  	if(state == blink)
    {
    	while(a--)
        {
        	digitalWrite(led[burn[a]-1],LOW);
          	strip.setPixelColor(burn[a]-1,rgbs[burn[a]-1][0],rgbs[burn[a]-1][1],rgbs[burn[a]-1][2]);
          	strip.show();
          	delay(200);
          	digitalWrite(led[burn[a]-1],HIGH);
          	strip.setPixelColor(burn[a]-1,0,0,0);
          	strip.show();
          	delay(200);
        }
      	state = scankey;
      	a = times;
    }
  	if(state == scankey)
      
    {
      digitalWrite(13,LOW);
      digitalWrite(6,LOW);
      while(keypress == 0)
        {
        	int i = 1;
  			while(i<5)
  			{
   				if(digitalRead(button[i])==LOW)
  				{
     				delay(20);
      				if(digitalRead(button[i])==LOW)
      				{
        				if(i!=0)
        				{
        					keypress = 1;
        				}
        				keyvalue = i;
      				}
                }
    			i++;
  			}
        }
    	if(keypress == 1)
        {
        	keypress = 0;          	
           	if(burn[--a]!=keyvalue)
            {  
              	state = gameover;
              	flash2();
            }
          	else
            {
            	digitalWrite(led[keyvalue-1],LOW);
              	strip.setPixelColor(burn[a]-1,rgbs[burn[a]-1][0],rgbs[burn[a]-1][1],rgbs[burn[a]-1][2]);
              	strip.show();
              	delay(200);
              	digitalWrite(led[keyvalue-1],HIGH);
              	strip.setPixelColor(burn[a]-1,0,0,0);
              	strip.show();
              	if(a == 0)
            	{
              		delay(500);
            		state = burnrandom;
            	}
            }
          	
        }
    }
  
}


