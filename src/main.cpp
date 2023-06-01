/*
 * @Author: LiTang litang0617@outlook.com
 * @Date: 2023-06-01 17:33:37
 * @LastEditors: LiTang litang0617@outlook.com
 * @LastEditTime: 2023-06-01 19:43:04
 * @FilePath: /ePaper/src/main.cpp
 * @Description: 
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
  display.setRotation(2);
  display.setFont(&FreeSansBold24pt7b);
  display.setTextColor(GxEPD_RED);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 25, 25, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  // uint16_t x = ((display.width() - tbw) / 2) - tbx;
  // uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    // display.setCursor(x, y);
    // display.print(HelloWorld);
    display.setCursor(0,0);
     display.drawExampleBitmap(Bitmap648x480_3, sizeof(BitmapExample1), GxEPD::bm_default | GxEPD::bm_partial_update);
    display.drawBitmap(0,0,Bitmap648x480_3,648,480,GxEPD_BLACK);
    // display.update();
    // display.print(Bitmap648x480_1);
    display.display();
    // delay(30000);
  }
  while (display.nextPage());
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