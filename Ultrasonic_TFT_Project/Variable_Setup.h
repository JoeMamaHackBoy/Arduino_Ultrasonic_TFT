#include <Adafruit_GFX.h>    // Core graphics library
// Initialising the tft Library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
MCUFRIEND_kbv tft ;

// LIST OF AVAILABLE FONTS:
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <FreeDefaultFonts.h>
#include <Fonts/FreeSerifBold12pt7b.h>
#include <Fonts/FreeSansBoldOblique18pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>

//16BIT HEX COLOR CODE:
#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410
#define PURPLE  0x8910
#define YELLOW  0xFFE0
#define SAFE    0x8550
#define DARK_BLUE 0x18F1
#define LIGHT_BLUE 0x0575
#define CREAM 0xEF7D
#define TEST    0x3333 //test color

//DEFINING THE TRIG AND ECHO ULTRASONIC PIN
#define trigPin 30
#define echoPin 31

int buzzerPin = 34;

//led setup pin
int rPin = 22, gPin = 23, bPin = 26;

//variable for statement related
int safeState, riskyState, dangerState;

//ultrasonic output variable:
long duration, distance;//int value
float distance2;//decimals value

void setRGB(int r, int g, int b) // RGB Function Setup
{
  analogWrite(rPin, r);
  analogWrite(gPin, g);
  analogWrite(bPin, b);
}

void tft_msg(int x, int y, int sz, const GFXfont * f, String msg)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(BLACK);
  tft.setTextSize(sz);
  tft.print(msg);
}

void tft_signs(int x, int y, int sz, const GFXfont * f, String msg, uint16_t color)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.print(msg);
}

void startupDisplay()
{
  setRGB(0, 0, 0), delay(200);
  setRGB(255, 0, 0), delay(200);
  setRGB(0, 0, 255), delay(200);
  setRGB(125, 125, 125), delay(200);
  setRGB(255, 255, 255), delay(200);
  tft.fillScreen(BLACK);
  tft.fillRoundRect(10, 5, 230, 40, 5, 0xEF7D);
  //tft.fillRoundRect(250, 5, 50, 10, 3, WHITE);
  int sety = 5;
  for (int z = 0; z < 3; z++)
  {
    tft.fillRoundRect(260, sety, 50, 9, 3, WHITE);
    tft.drawRoundRect(260, sety, 50, 9, 3, GREY);
    sety += 14;
  }
  tft_msg(22, 18, 2, NULL, "By BobWithTech");
  tft.fillRoundRect(10, 50, 300, 60, 5, GREY);
  tft.drawRoundRect(10, 50, 300, 60, 5, 0xEF7D);
  tft.drawRoundRect(11, 51, 298, 58, 5, 0xEF7D);
  tft.drawRoundRect(12, 52, 296, 56, 5, 0xEF7D);
  tft_msg(16, 70, 3, NULL, "DISTANCE:");
  tft.fillRoundRect(10, 118, 200, 30, 5, LIGHT_BLUE);
  tft.drawRoundRect(10, 118, 200, 30, 5, 0xEF7D);
  tft.drawRoundRect(11, 1119, 198, 28, 5, 0xEF7D);
  tft_msg(14, 126, 2, NULL, "STATUS:");
}
// function for simple version of both serial and lcd output display logic
void displayer(int safe, int risky, int danger, float ultradis)
{
  //variable for screen animation setup
  int v = 170, v1 = 190, line1 = 230, line2 = 168, line3 = 285, line4 = 128, lineX1 = 250, lineY1 = 223, lineX2 = 250, lineY2 = 223;

  float scale = ultradis / 75;
  float val_limit = (scale * 150) + 45;
  tft.fillRect(10, 150, 200, 85, BLACK);
  tft.fillRect(14, 182, 18, 18, GREY);//logo animation
  tft.fillRect(32, 170, 10, 42, GREY);//logo animation
  tft.fillRect(180, 70, 127, 24, GREY);// clear number screen
  tft.fillRect(96, 126, 110, 16, LIGHT_BLUE);
  tft.fillRect(220, 112, 86, 124, GREY);//clear symbol

  ultradis = ultradis - 1;
  String dis = String(ultradis);

  if (safe == 1 && risky == 0 && danger == 0 ) {
    for (int x = 0; x <= 5; x++) {
      tft.drawLine(45, 180, 200 , v, WHITE);
      v += 5;
    }
    for (int x = 0; x <= 5; x++) {
      tft.drawLine(45, 200, 200, v1, WHITE);
      v1 += 5;
    }
    tft_msg(180, 70, 3, NULL, dis);
    tft_signs(96, 126, 2, NULL, "SAFE", GREEN);
    for (int n = 0; n <= 12; n++)
    {
      tft.drawLine(line1, line2, lineX1 , lineY1, GREEN);
      tft.drawLine(line3, line4, lineX2, lineY2, GREEN);
      line1 += 1;
      line3 += 1;
      lineX1 += 1;
      lineX2 += 1;
    }
  }
  else if (safe == 0 && risky == 1 && danger == 0) {
    for (int x = 0; x <= 5; x++) {
      tft.drawLine(45, 180, val_limit, v, WHITE);
      v += 5;
    }
    for (int x = 0; x <= 5; x++) {
      tft.drawLine(45, 200, val_limit, v1, WHITE);
      v1 += 5;
    }
    tft.fillRoundRect(val_limit, 170, 8, 45, 3, GREY);
    tft_msg(180, 70, 3, NULL, dis);
    tft_signs(96, 126, 2, NULL, "CAUTION", YELLOW);
    tft.fillRoundRect(245, 118, 35, 75, 30, YELLOW);
    tft.fillCircle(260, 215, 14, YELLOW);
  }
  else if (safe == 0 && risky == 0 && danger == 1)
  {
    for (int x = 0; x <= 5; x++) {
      tft.drawLine(45, 180, val_limit, v, WHITE);
      v += 5;
    }
    for (int x = 0; x <= 5; x++) {
      tft.drawLine(45, 200, val_limit, v1, WHITE);
      v1 += 5;
    }
    tft.fillRoundRect(val_limit, 170, 8, 45, 1, GREY);
    tft_msg(180, 70, 3, NULL, dis);
    tft_signs(96, 126, 2, NULL, "DANGEROUS", RED);
    tft.fillRoundRect(225, 118, 30, 75, 30, RED);
    tft.fillRoundRect(270, 118, 30, 75, 30, RED);
    tft.fillCircle(240, 215, 14, RED);
    tft.fillCircle(285, 215, 14, RED);
    tone(buzzerPin, 950);
  }
}
//Final function
void final_result()
{
  noTone(buzzerPin);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;//integers value
  distance2 = (duration / 2) / 29.1;//decimal value
  if (distance >= 75 || distance <= 0)
  {
    safeState = 1;
    riskyState = 0;
    dangerState = 0;
    setRGB(0, 255, 0);
    displayer(safeState, riskyState, dangerState, distance2);//Displayer Funtion
  }
  else if (distance > 25) {
    safeState = 0;
    riskyState = 1;
    dangerState = 0;
    setRGB(255, 255, 0);
    displayer(safeState, riskyState, dangerState, distance2);
  }
  else
  {
    safeState = 0;
    riskyState = 0;
    dangerState = 1;
    setRGB(255, 0, 0);
    displayer(safeState, riskyState, dangerState, distance2);
  }
}
