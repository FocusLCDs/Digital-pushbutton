#include <Adafruit_GFX.h>    // Core graphics library
#include <ILI9163.h> // Hardware-specific library for ILI9163
#include <SPI.h>
#include "bitmaps.h"

#include <stdint.h>
#include "TouchScreen.h"

#define TFT_CS        10
#define TFT_RST        8 
#define TFT_DC         9

// Software SPI
#define TFT_MOSI 11
#define TFT_SCLK 13  // Clock out
#define TFT_MISO 12


#define YP A1  // analog pin
#define XM A0  // analog pin
#define YM A3   // analog or digital pin
#define XP A2   // analog or digital pin


#define TFT_w 128
#define TFT_h 160

#define BLACK  0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


//Software SPI
//ILI9163 tft = ILI9163(TFT_w, TFT_h, TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST, TFT_MISO);

//Hardware SPI
ILI9163 tft = ILI9163(TFT_w, TFT_h, TFT_CS, TFT_DC, TFT_RST);

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

float p = 3.1415926;
boolean yellow = false;

int16_t pressureThreshhold=100;

void setup(void) {
Serial.begin(115200);

  
Serial.print(F("Hello World!"));
delay(50);

tft.initR();      
uint16_t time = millis();
time = millis() - time;

tft.fillScreen(BLACK);

Serial.println(time, DEC);

tft.fillScreen(WHITE);

//size of bitmap 
int16_t w=122;
int16_t h=80;


#define width 128
#define height 160

//center the bitmap
int16_t x=(width-w)/2;
int16_t y=(height-h)/2;

tft.drawRGBBitmap(x, y, bitmap, w, h);
Serial.println(time, DEC);
  delay(5000);


tft.fillScreen(BLACK);
delay(500);

greenButton();

}



void loop(void) {

TSPoint p = ts.getPoint();

if(yellow){
  if(p.z >pressureThreshhold){
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);
  if(450<=p.x<=600 && 475 <= p.y <=600){
    greenButton();
  }
  }
}

else
{
  if(p.z >pressureThreshhold){
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);
  if(450<=p.x<=600 && 475 <= p.y <=600){
    yellowButton(); 
      }
   }
  }
}


#define buttonRadius 50
#define buttonArea (pi*(buttonRadius*buttonRadius))

#define screenArea (120*160)

void greenButton(){
  tft.drawCircle(60, 80,51,WHITE);
  tft.fillCircle(60,80,50, GREEN);
  tft.fillTriangle(40, 110, 40, 50, 100, 80, WHITE);
  yellow=false;
}

void yellowButton(){
  tft.fillCircle(60,80,50, YELLOW);
  tft.fillRoundRect(32,50,20,60,8,WHITE);
  tft.fillRoundRect(67, 50, 20,60,8,WHITE);
  yellow=true;
}
