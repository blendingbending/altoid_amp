#include <Adafruit_GFX.h>                                                   // include Adafruit graphics library
#include <Adafruit_ILI9341.h>                                               // include Adafruit ILI9341 TFT library

#define TFT_CS    D2                                                        // TFT CS  pin is connected to NodeMCU pin D2
#define TFT_RST   D3                                                        // TFT RST pin is connected to NodeMCU pin D3
#define TFT_DC    D4                                                        // TFT DC  pin is connected to NodeMCU pin D4

Adafruit_ILI9341 display = Adafruit_ILI9341 (TFT_CS, TFT_DC, TFT_RST);
int delayTime = 200;

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 320

#define GRID_WIDTH 240
#define GRID_HEIGHT 320

#define SQUID 0
#define CRAB 2
#define OCTOPUS 4

int cx = DISPLAY_WIDTH / 2;
int cy = DISPLAY_HEIGHT / 2;

// int w = 16; // cell of the grid
int cell = 2;

int enemy[6][8][12] = {
  {{0,0,0,0,0,1,1,0,0,0,0,0}, // Squid 0
   {0,0,0,0,1,1,1,1,0,0,0,0},
   {0,0,0,1,1,1,1,1,1,0,0,0},
   {0,0,1,1,0,1,1,0,1,1,0,0},
   {0,0,1,1,1,1,1,1,1,1,0,0},
   {0,0,0,0,1,0,0,1,0,0,0,0},
   {0,0,0,1,0,1,1,0,1,0,0,0},
   {0,0,1,0,1,0,0,1,0,1,0,0}},

  {{0,0,0,0,0,1,1,0,0,0,0,0}, // Squid 1
   {0,0,0,0,1,1,1,1,0,0,0,0},
   {0,0,0,1,1,1,1,1,1,0,0,0},
   {0,0,1,1,0,1,1,0,1,1,0,0},
   {0,0,1,1,1,1,1,1,1,1,0,0},
   {0,0,0,1,0,1,1,0,1,0,0,0},
   {0,0,1,0,0,1,1,0,0,1,0,0},
   {0,0,0,1,0,0,0,0,1,0,0,0}},

  {{0,0,0,1,0,0,0,0,1,0,0,0}, // Crab 0
   {0,0,0,0,1,0,0,1,0,0,0,0},
   {0,1,0,1,1,1,1,1,1,0,1,0},
   {0,1,1,1,0,1,1,0,1,1,1,0},
   {0,1,1,1,1,1,1,1,1,1,1,0},
   {0,0,0,1,1,1,1,1,1,0,0,0},
   {0,0,0,1,0,0,0,0,1,0,0,0},
   {0,0,1,0,0,0,0,0,0,1,0,0}},

  {{0,0,0,1,0,0,0,0,1,0,0,0}, // Crab 1
   {0,0,0,0,1,0,0,1,0,0,0,0},
   {0,0,0,1,1,1,1,1,1,0,0,0},
   {0,0,1,1,0,1,1,0,1,1,0,0},
   {0,1,1,1,1,1,1,1,1,1,1,0},
   {0,1,0,1,1,1,1,1,1,0,1,0},
   {0,1,0,1,0,0,0,0,1,0,1,0},
   {0,0,0,0,1,0,0,1,0,0,0,0}},

  {{0,0,0,0,1,1,1,1,0,0,0,0}, // Octopus 0
   {0,1,1,1,1,1,1,1,1,1,1,0},
   {1,1,1,1,1,1,1,1,1,1,1,1},
   {1,1,1,0,0,1,1,0,0,1,1,1},
   {1,1,1,1,1,1,1,1,1,1,1,1},
   {0,0,0,1,1,0,0,1,1,0,0,0},
   {0,0,1,1,0,1,1,0,1,1,0,0},
   {1,1,0,0,0,0,0,0,0,0,1,1}},

  {{0,0,0,0,1,1,1,1,0,0,0,0}, // Octopus 1
   {0,1,1,1,1,1,1,1,1,1,1,0},
   {1,1,1,1,1,1,1,1,1,1,1,1},
   {1,1,1,0,0,1,1,0,0,1,1,1},
   {1,1,1,1,1,1,1,1,1,1,1,1},
   {0,0,1,1,1,0,0,1,1,1,0,0},
   {0,1,1,0,0,1,1,0,0,1,1,0},
   {0,0,1,1,0,0,0,0,1,1,0,0}},
};

// void displayGrid(uint16_t color){
//   for(int i = 0; i < GRID_WIDTH / w; i++) { // i < 10
//     for(int j = 0; j < GRID_HEIGHT / w; j++) { // j < 20
//       tft.drawRect(i * w, j * w, w, w, color);
//     }
//   }
// }

void displayEnemy(int type, uint16_t color, int x, int y) {
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 12; j++) {
      if (enemy[type][i][j] == 1) {
        display.fillRect(x + (j * cell),y + (i * cell), cell, cell, color);
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  display.begin();
  display.fillScreen(ILI9341_BLACK);
}

void loop() {
  // put your main code here, to run repeatedly:
  displayEnemy(0,ILI9341_BLACK, cx, 0);
  displayEnemy(1,ILI9341_WHITE, cx, 0);
  delay(200);
  displayEnemy(0,ILI9341_BLACK, cx, 0);
  displayEnemy(1,ILI9341_WHITE, cx, 0);
  delay(200);

  displayEnemy(2,ILI9341_BLACK, cx, cy);
  displayEnemy(3,ILI9341_WHITE, cx, cy);
  delay(200);
  displayEnemy(2,ILI9341_BLACK, cx, cy);
  displayEnemy(3,ILI9341_WHITE, cx, cy);
  delay(200);

  displayEnemy(4,ILI9341_BLACK, cx, cy + 120);
  displayEnemy(5,ILI9341_WHITE, cx, cy + 120);
  delay(200);
  displayEnemy(5,ILI9341_BLACK, cx, cy + 120);
  displayEnemy(4,ILI9341_WHITE, cx, cy + 120);
  delay(200);
}
