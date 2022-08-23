#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int x = 128 / 2;
int y = 64 / 2;
int w1x = 120;
int w1y = random(20, 60);
int score = 0;
void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}
void(* resetFunc) (void) = 0;
void loop() {
  display.clearDisplay();
  float vrx = analogRead(A0); // joystick vrx
  float vry = analogRead(A1); // vry
  float sw = analogRead(A2); // sw
  w1x -= 1;
  if (w1x == 0) {
    w1y = random(20, 60);
    w1x = 120;
    score += 1;
  }
  if (x < w1x && x + 10 > w1x && y < w1y) {
    resetFunc();
  }
  if (x < w1x && x + 10 > w1x && y > w1y + 20) {
    resetFunc();
  }
  if (y > 70) {
    resetFunc();
  }
  if (vry < 400) {
    y -= 1;
  }
  else {
    y += 1;
  }
  if (!sw) {
    resetFunc();
  }   
  display.drawRect(w1x, 0, 10, w1y, WHITE);
  display.drawRect(w1x, w1y + 20, 10, 64, WHITE);
  display.drawCircle(x, y, 3, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Score: " + String(score));
  display.display(); 
}
