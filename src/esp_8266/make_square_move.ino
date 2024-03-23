#include <Adafruit_GFX.h>                                               // include Adafruit graphics library
#include <Adafruit_ILI9341.h>                                             // include Adafruit ILI9341 TFT library

#define TFT_CS    D2                                                        // TFT CS  pin is connected to NodeMCU pin D2
#define TFT_RST   D3                                                        // TFT RST pin is connected to NodeMCU pin D3
#define TFT_DC    D4  
#define BUTTON_SW D0                                                      // TFT DC  pin is connected to NodeMCU pin D4

Adafruit_ILI9341 tft = Adafruit_ILI9341 (TFT_CS, TFT_DC, TFT_RST);
int delayTime = 200;

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 320

int cx = DISPLAY_WIDTH / 2;
int cy = DISPLAY_HEIGHT / 2;
int w = 50;

int vx = 10;
int vy = 8;
int buttonState = 0;  // variable for reading the pushbutton status

#define POTENTIOMETER A0 // ALL CAPS DEFINE
int val = 0;
int postion = 0;
int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  tft.begin();
  Serial.begin(9600);
//  tft.fillScreen(ILI9341_WHITE);
  tft.fillScreen(ILI9341_BLACK);
  // tft.fillRect(cx - (w/2),cy - (w/2),w, w, ILI9341_BLUE);
  pinMode(BUTTON_SW, INPUT);
}

int i = 0;
void loop() {
  // put your main code here, to run repeatedly:
  tft.fillRect(sensorValue,DISPLAY_HEIGHT - 50,w, w, ILI9341_BLACK);

  sensorValue = analogRead(POTENTIOMETER);
  sensorValue = map(sensorValue, 12, 1024, 0, DISPLAY_WIDTH - w);
  Serial.println(sensorValue);

  buttonState = digitalRead(BUTTON_SW);
  if (buttonState == 1) {
    i++;
    i %= 4;
  }

  switch(i){
    case 0:
    tft.fillRect(sensorValue,DISPLAY_HEIGHT - 50,w, w, 0x0320 );
    break;
    case 1: 
    tft.fillRect(sensorValue,DISPLAY_HEIGHT - 50,w, w,  0x808080);  
    break; 
    case 2: 
    tft.fillRect(sensorValue,DISPLAY_HEIGHT - 50,w, w,  0x49F1 ); 
    break; 
    case 3: 
    tft.fillRect(sensorValue,DISPLAY_HEIGHT - 50,w, w,  0xFFDE);  
    break; 
  }

  delay(delayTime);
}
