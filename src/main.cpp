/*
 * @Author: LiTang litang0617@outlook.com
 * @Date: 2023-06-01 17:33:37
 * @LastEditors: LiTang litang0617@outlook.com
 * @LastEditTime: 2023-06-01 18:46:25
 * @FilePath: /ePaper/src/main.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include "ePaper.h"

GxEPD2_3C<GxEPD2_420c_1680, GxEPD2_420c_1680::HEIGHT> display(GxEPD2_420c_1680(/*CS*/ SS_PIN, /*DC*/ DC_PIN, /*RST*/ RES_PIN, /*BUSY*/ BUSY_PIN)); // 

// SPIClass ePaper_SPI(HSPI);
SPIClass ePaper_SPI(FSPI);

void helloWorld();


void setup()
{
  //display.init(115200); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  ePaper_SPI.begin(CLK_PIN,-1,MOSI_PIN,SS_PIN);
  // ePaper_SPI.begin();
  // SPISettings(10000000, MSBFIRST, SPI_MODE0)
  display.init(115200, true, 2, false, ePaper_SPI , SPISettings(10000000, MSBFIRST, SPI_MODE0)); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  helloWorld();
  display.hibernate();
}

const char HelloWorld[] = "When in the Course of human events, it becomes necessary for one people to dissolve the political bands which have connected them with another, and to assume among the powers of the earth, the separate and equal station to which the Laws of Nature and of Nature's God entitle them, a decent respect to the opinions of mankind requires that they should declare the causes which impel them to the separation.";



void loop() {};


void helloWorld()
{
  display.setRotation(0);
  display.setFont(&FreeSansBold9pt7b);
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