/*
 * @Author: LiTang litang0617@outlook.com
 * @Date: 2023-06-01 17:33:37
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-10-10 15:28:24
 * @FilePath: /ePaper/src/main.cpp
 * @Description: ePaper Partial Update
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include "ePaper.h"
#include "BLE.h"
#include "bitmaps/Bitmaps648x480.h"

// GxEPD2_3C<GxEPD2_420c_1680, GxEPD2_420c_1680::HEIGHT> display(GxEPD2_420c_1680(/*CS*/ SS_PIN, /*DC*/ DC_PIN, /*RST*/ RES_PIN, /*BUSY*/ BUSY_PIN)); // 
GxEPD2_BW<GxEPD2_583_T8, GxEPD2_583_T8::HEIGHT> display(GxEPD2_583_T8(/*CS*/ SS_PIN, /*DC*/ DC_PIN, /*RST*/ RES_PIN, /*BUSY*/ BUSY_PIN)); // 

// SPIClass ePaper_SPI(HSPI);
SPIClass ePaper_SPI(FSPI);
const char HelloWorld[] = "When in the Course of human events, it becomes necessary for one people to dissolve the political bands which have connected them with another, and to assume among the powers of the earth, the separate and equal station to which the Laws of Nature and of Nature's God entitle them, a decent respect to the opinions of mankind requires that they should declare the causes which impel them to the separation.";


void setup()
{
  ePaper_SPI.begin(CLK_PIN,-1,MOSI_PIN,SS_PIN);
  setupBLE("ESP32_BLE");

  display.init(115200, true, 2, false, ePaper_SPI , SPISettings(10000000, MSBFIRST, SPI_MODE0)); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  display.clearScreen();
  // delay(5000);
  display.setRotation(2);
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(0,0);
  // display.drawBitmap(0,0,Bitmap648x480_3,648,480,GxEPD_BLACK);
  // display.display(1);
}




void loop() {
  long now = millis();
  if (now - lastMsg > 100) {
    if (deviceConnected&&rxload.length()>0) {
        Serial.println(rxload);
        display.setTextColor(GxEPD_BLACK);
        display.setFont(&FreeMonoBold9pt7b);
        display.print(rxload);
        display.display(1);
        rxload="";
    }
    if(Serial.available()>0){
        String str=Serial.readString();
        const char *newValue=str.c_str();
        pReadCharacteristic->setValue(newValue);
        pNotifyCharacteristic->setValue(newValue);
        pNotifyCharacteristic->notify();
    }
    if(!deviceConnected)  Serial.println("deviceDisConnected");
    // if(! deviceConnected)
    // {
    //   setupBLE("ESP32_BLE");
    //   delay(100);
    // }
    lastMsg = now;
  }
  }