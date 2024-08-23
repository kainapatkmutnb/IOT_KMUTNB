#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32  // Updated to match a 128x32 display
#define OLED_RESET -1 
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Bitmap data (example bitmap of a 16x16 pixel logo)
const unsigned char logo_bmp[] PROGMEM = {
  // Bitmap data for your logo
};

// Dimensions of the logo
#define LOGO_WIDTH 16
#define LOGO_HEIGHT 16

void setup() {
  Serial.begin(9600);
  
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  } else {
    Serial.println("KMUTNB Start Work !!!");
  }

  // Initial display setup
  OLED.display();
  delay(2000); // Pause for 2 seconds
  OLED.clearDisplay();
}

void loop() {
  // Update display with test functions
  testdrawline();      
  testdrawrect();      
  testfillrect();      
  testdrawcircle();    
  testfillcircle();    
  testdrawroundrect(); 
  testfillroundrect(); 
  testdrawtriangle();  
  testfilltriangle();  
  testdrawchar();      
  testdrawstyles();    
  testscrolltext();    
  testdrawbitmap(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT);  // Fix the function call
  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT);     // Fix the function call

  // Invert display colors
  OLED.invertDisplay(true);
  delay(1000);
  OLED.invertDisplay(false);
  delay(1000);
  
  // Animate bitmap
  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT);

  // Delay to avoid too fast refresh rate
  delay(2000);
}

void testdrawline() {
  int16_t i;

  OLED.clearDisplay(); // Clear display buffer

  for(i=0; i<OLED.width(); i+=4) {
    OLED.drawLine(0, 0, i, OLED.height()-1, WHITE);
    OLED.display(); // Update screen with each newly-drawn line
    delay(1);
  }
  for(i=0; i<OLED.height(); i+=4) {
    OLED.drawLine(0, 0, OLED.width()-1, i, WHITE);
    OLED.display();
    delay(1);
  }
  delay(250);

  OLED.clearDisplay();

  for(i=0; i<OLED.width(); i+=4) {
    OLED.drawLine(0, OLED.height()-1, i, 0, WHITE);
    OLED.display();
    delay(1);
  }
  for(i=OLED.height()-1; i>=0; i-=4) {
    OLED.drawLine(0, OLED.height()-1, OLED.width()-1, i, WHITE);
    OLED.display();
    delay(1);
  }
  delay(250);

  OLED.clearDisplay();

  for(i=OLED.width()-1; i>=0; i-=4) {
    OLED.drawLine(OLED.width()-1, OLED.height()-1, i, 0, WHITE);
    OLED.display();
    delay(1);
  }
  for(i=OLED.height()-1; i>=0; i-=4) {
    OLED.drawLine(OLED.width()-1, OLED.height()-1, 0, i, WHITE);
    OLED.display();
    delay(1);
  }
  delay(250);

  OLED.clearDisplay();

  for(i=0; i<OLED.height(); i+=4) {
    OLED.drawLine(OLED.width()-1, 0, 0, i, WHITE);
    OLED.display();
    delay(1);
  }
  for(i=0; i<OLED.width(); i+=4) {
    OLED.drawLine(OLED.width()-1, 0, i, OLED.height()-1, WHITE);
    OLED.display();
    delay(1);
  }

  delay(2000); // Pause for 2 seconds
}

void testdrawrect(void) {
  OLED.clearDisplay();

  for(int16_t i=0; i<OLED.height()/2; i+=2) {
    OLED.drawRect(i, i, OLED.width()-2*i, OLED.height()-2*i, WHITE);
    OLED.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}

void testfillrect(void) {
  OLED.clearDisplay();

  for(int16_t i=0; i<OLED.height()/2; i+=3) {
    // The INVERSE color is used so rectangles alternate white/black
    OLED.fillRect(i, i, OLED.width()-i*2, OLED.height()-i*2, INVERSE);
    OLED.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}

void testdrawcircle(void) {
  OLED.clearDisplay();

  for(int16_t i=0; i<max(OLED.width(),OLED.height())/2; i+=2) {
    OLED.drawCircle(OLED.width()/2, OLED.height()/2, i, WHITE);
    OLED.display();
    delay(1);
  }

  delay(2000);
}

void testfillcircle(void) {
  OLED.clearDisplay();

  for(int16_t i=max(OLED.width(),OLED.height())/2; i>0; i-=3) {
    // The INVERSE color is used so circles alternate white/black
    OLED.fillCircle(OLED.width() / 2, OLED.height() / 2, i, INVERSE);
    OLED.display(); // Update screen with each newly-drawn circle
    delay(1);
  }

  delay(2000);
}

void testdrawroundrect(void) {
  OLED.clearDisplay();

  for(int16_t i=0; i<OLED.height()/2-2; i+=2) {
    OLED.drawRoundRect(i, i, OLED.width()-2*i, OLED.height()-2*i,
      OLED.height()/4, WHITE);
    OLED.display();
    delay(1);
  }

  delay(2000);
}

void testfillroundrect(void) {
  OLED.clearDisplay();

  for(int16_t i=0; i<OLED.height()/2-2; i+=2) {
    // The INVERSE color is used so round-rects alternate white/black
    OLED.fillRoundRect(i, i, OLED.width()-2*i, OLED.height()-2*i,
      OLED.height()/4, INVERSE);
    OLED.display();
    delay(1);
  }

  delay(2000);
}

void testdrawtriangle(void) {
  OLED.clearDisplay();

  for(int16_t i=0; i<max(OLED.width(),OLED.height())/2; i+=5) {
    OLED.drawTriangle(
      OLED.width()/2  , OLED.height()/2-i,
      OLED.width()/2-i, OLED.height()/2+i,
      OLED.width()/2+i, OLED.height()/2+i, WHITE);
    OLED.display();
    delay(1);
  }

  delay(2000);
}

void testfilltriangle(void) {
  OLED.clearDisplay();

  for(int16_t i=max(OLED.width(),OLED.height())/2; i>0; i-=5) {
    // The INVERSE color is used so triangles alternate white/black
    OLED.fillTriangle(
      OLED.width()/2  , OLED.height()/2-i,
      OLED.width()/2-i, OLED.height()/2+i,
      OLED.width()/2+i, OLED.height()/2+i, INVERSE);
    OLED.display();
    delay(1);
  }

  delay(2000);
}

void testdrawchar(void) {
  OLED.clearDisplay();

  OLED.setTextSize(1);      // Normal 1:1 pixel scale
  OLED.setTextColor(WHITE); // Draw white text
  OLED.setCursor(0, 0);     // Start at top-left corner
  OLED.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') OLED.write(' ');
    else          OLED.write(i);
  }

  OLED.display();
  delay(2000);
}

void testdrawstyles(void) {
  OLED.clearDisplay();

  OLED.setTextSize(1);             // Normal 1:1 pixel scale
  OLED.setTextColor(WHITE);        // Draw white text
  OLED.setCursor(0,0);             // Start at top-left corner
  OLED.println(F("Hello, world!"));

  OLED.setTextColor(BLACK, WHITE); // Draw black text on white background
  OLED.setTextSize(2);             // 2X-scale text
  OLED.println(F("Hello, world!"));

  OLED.setTextColor(WHITE, BLACK); // Draw white text on black background
  OLED.setTextSize(3);             // 3X-scale text
  OLED.println(F("Hello, world!"));

  OLED.display();
  delay(2000);
}

void testscrolltext(void) {
  OLED.clearDisplay();
  OLED.setTextSize(2); // Draw 2X-scale text
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.println(F("Scrolling text!"));

  OLED.startscrollleft(0x00, 0x0F);
  delay(2000);
  OLED.stopscroll();
  delay(2000);
}

void testdrawbitmap(const unsigned char *bitmap, uint8_t w, uint8_t h) {
  OLED.clearDisplay();

  for(int16_t i=0; i<OLED.width(); i+=6) {
    OLED.drawBitmap(i, 0, bitmap, w, h, WHITE);
    OLED.display();
    delay(100);
  }

  delay(2000);
}

void testanimate(const unsigned char *bitmap, uint8_t w, uint8_t h) {
  OLED.clearDisplay();

  for(int16_t i=0; i<OLED.width(); i+=6) {
    OLED.clearDisplay();
    OLED.drawBitmap(i, (OLED.height()-h)/2, bitmap, w, h, WHITE);
    OLED.display();
    delay(100);
  }

  delay(2000);
}
