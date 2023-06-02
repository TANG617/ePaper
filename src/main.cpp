/*
 * @Author: LiTang litang0617@outlook.com
 * @Date: 2023-06-01 17:33:37
 * @LastEditors: LiTang litang0617@outlook.com
 * @LastEditTime: 2023-06-02 11:46:53
 * @FilePath: /ePaper/src/main.cpp
 * @Description: ePaper Partial Update
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include "ePaper.h"
#include "bitmaps/Bitmaps648x480.h"

// GxEPD2_3C<GxEPD2_420c_1680, GxEPD2_420c_1680::HEIGHT> display(GxEPD2_420c_1680(/*CS*/ SS_PIN, /*DC*/ DC_PIN, /*RST*/ RES_PIN, /*BUSY*/ BUSY_PIN)); // 
GxEPD2_BW<GxEPD2_583_T8, GxEPD2_583_T8::HEIGHT> display(GxEPD2_583_T8(/*CS*/ SS_PIN, /*DC*/ DC_PIN, /*RST*/ RES_PIN, /*BUSY*/ BUSY_PIN)); // 

// SPIClass ePaper_SPI(HSPI);
SPIClass ePaper_SPI(FSPI);
void helloWorld();
const char HelloWorld[] = "When in the Course of human events, it becomes necessary for one people to dissolve the political bands which have connected them with another, and to assume among the powers of the earth, the separate and equal station to which the Laws of Nature and of Nature's God entitle them, a decent respect to the opinions of mankind requires that they should declare the causes which impel them to the separation.";

void helloFullScreenPartialMode()
{
  //Serial.println("helloFullScreenPartialMode");
  const char fullscreen[] = "full screen update";
  const char fpm[] = "fast partial mode";
  const char spm[] = "slow partial mode";
  const char npm[] = "no partial mode";
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  if (display.epd2.WIDTH < 104) display.setFont(0);
  display.setTextColor(GxEPD_BLACK);
  const char* updatemode;
  if (display.epd2.hasFastPartialUpdate)
  {
    updatemode = fpm;
  }
  else if (display.epd2.hasPartialUpdate)
  {
    updatemode = spm;
  }
  else
  {
    updatemode = npm;
  }
  // do this outside of the loop
  int16_t tbx, tby; uint16_t tbw, tbh;
  // center update text
  display.getTextBounds(fullscreen, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t utx = ((display.width() - tbw) / 2) - tbx;
  uint16_t uty = ((display.height() / 4) - tbh / 2) - tby;
  // center update mode
  display.getTextBounds(updatemode, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t umx = ((display.width() - tbw) / 2) - tbx;
  uint16_t umy = ((display.height() * 3 / 4) - tbh / 2) - tby;
  // center HelloWorld
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t hwx = ((display.width() - tbw) / 2) - tbx;
  uint16_t hwy = ((display.height() - tbh) / 2) - tby;
  display.firstPage();
  int i=1;
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(hwx, hwy);
    display.print(HelloWorld);
    display.setCursor(utx, uty);
    display.print(fullscreen);
    display.setCursor(umx, umy);
    display.print(updatemode);
    display.display(true);
    i++;
    // delay(500);
    display.setRotation(i%4);
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0,0);
    //  display.drawExampleBitmap(Bitmap648x480_3, sizeof(BitmapExample1), GxEPD::bm_default | GxEPD::bm_partial_update);
    display.drawBitmap(0,0,Bitmap648x480_3,648,480,GxEPD_BLACK);
     display.display(true);
    //  delay(500);
  }
  while (1);
  // Serial.println("helloFullScreenPartialMode done");
}

void setup()
{
  //display.init(115200); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  ePaper_SPI.begin(CLK_PIN,-1,MOSI_PIN,SS_PIN);
  // ePaper_SPI.begin();
  // SPISettings(10000000, MSBFIRST, SPI_MODE0)
  display.init(115200, true, 2, false, ePaper_SPI , SPISettings(10000000, MSBFIRST, SPI_MODE0)); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  // helloWorld();
  // display.setRotation(0);
  // display.setFont(&FreeSansBold24pt7b);
  // display.setTextColor(GxEPD_RED);
  // // int16_t tbx, tby; uint16_t tbw, tbh;
  // // display.getTextBounds(HelloWorld, 25, 25, &tbx, &tby, &tbw, &tbh);
  // // // center the bounding box by transposition of the origin:
  // // uint16_t x = ((display.width() - tbw) / 2) - tbx;
  // // uint16_t y = ((display.height() - tbh) / 2) - tby;
  // display.setFullWindow();
  // display.firstPage();
  // display.drawBitmap(0,0,Bitmap648x480_1,640,480,GxEPD_WHITE);
  // display.hibernate();
  display.clearScreen();
  delay(5000);
  helloFullScreenPartialMode();
  delay(5000);
  display.setRotation(2);
  display.setFont(&FreeSansBold24pt7b);
  display.setTextColor(GxEPD_RED);
  int16_t tbx, tby; uint16_t tbw, tbh;
  // display.getTextBounds(HelloWorld, 25, 25, &tbx, &tby, &tbw, &tbh);
  
  // center the bounding box by transposition of the origin:
  // uint16_t x = ((display.width() - tbw) / 2) - tbx;
  // uint16_t y = ((display.height() - tbh) / 2) - tby;
  // display.setFullWindow();
  uint16_t wh = FreeMonoBold9pt7b.yAdvance;
  uint16_t wy = 110 - wh;
  // display.setPartialWindow(0, wy, display.width(), wh);
  display.firstPage();
  // do
  // {
     display.setPartialWindow(0, 0, display.width(), display.height());
    display.fillScreen(GxEPD_WHITE);
    // display.setCursor(x, y);
    // display.print(HelloWorld);
    display.setCursor(0,0);
    //  display.drawExampleBitmap(Bitmap648x480_3, sizeof(BitmapExample1), GxEPD::bm_default | GxEPD::bm_partial_update);
    display.drawBitmap(0,0,Bitmap648x480_3,648,480,GxEPD_BLACK);
    // display.update();
    // display.print(Bitmap648x480_1);
    display.display();
    // delay(30000);
  // }
  // while (display.nextPage());
}




void loop() {};


void helloWorld()
{
  display.setRotation(0);
  display.setFont(&FreeSansBold24pt7b);
  display.setTextColor(GxEPD_RED);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 25, 25, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());
}