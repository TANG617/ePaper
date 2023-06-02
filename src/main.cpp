/*
 * @Author: LiTang litang0617@outlook.com
 * @Date: 2023-06-01 17:33:37
 * @LastEditors: LiTang litang0617@outlook.com
 * @LastEditTime: 2023-06-02 13:26:24
 * @FilePath: /ePaper/src/main.cpp
 * @Description: ePaper Partial Update
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include "ePaper.h"
#include "bitmaps/Bitmaps648x480.h"
#include "lvgl.h"



lv_obj_t *screenMain;	//指向所用屏幕的实例化对象
lv_obj_t *labelName;
lv_obj_t *labelTime;
lv_obj_t *labelLocation;
lv_obj_t *labelWeather;
lv_obj_t *labelTemperature;
static const uint16_t screenWidth  = 648;
static const uint16_t screenHeight = 480;
static lv_disp_draw_buf_t draw_buf; //初始化显示缓冲区
static lv_color_t buf_1[screenWidth * 10];//用于LVGL使用的缓冲区

// GxEPD2_3C<GxEPD2_420c_1680, GxEPD2_420c_1680::HEIGHT> display(GxEPD2_420c_1680(/*CS*/ SS_PIN, /*DC*/ DC_PIN, /*RST*/ RES_PIN, /*BUSY*/ BUSY_PIN)); // 
GxEPD2_BW<GxEPD2_583_T8, GxEPD2_583_T8::HEIGHT> display(GxEPD2_583_T8(/*CS*/ SS_PIN, /*DC*/ DC_PIN, /*RST*/ RES_PIN, /*BUSY*/ BUSY_PIN)); // 

// SPIClass ePaper_SPI(HSPI);
SPIClass ePaper_SPI(FSPI);
void helloWorld();
const char HelloWorld[] = "When in the Course of human events, it becomes necessary for one people to dissolve the political bands which have connected them with another, and to assume among the powers of the earth, the separate and equal station to which the Laws of Nature and of Nature's God entitle them, a decent respect to the opinions of mankind requires that they should declare the causes which impel them to the separation.";

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    // uint32_t w = (area->x2 - area->x1 + 1);
    // uint32_t h = (area->y2 - area->y1 + 1);

    // tft.startWrite();
    display.setPartialWindow(0, 0, display.width(), display.height());
    // tft.setAddrWindow(area->x1, area->y1, w, h);
    // display.displayWindow(area->x1, area->y1, w, h);
    // tft.pushColors(&color_p->full, w * h, true);
    // display.drawPixel(x, y, &color_p->full);



    int32_t x, y;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            display.drawPixel(x, y, GxEPD_BLACK);  /* Put a pixel to the display.*/
            color_p++;
        }
    }

    lv_disp_flush_ready(disp);         /* Indicate you are ready with the flushing*/

    // // tft.endWrite();
    // display.display();

    // lv_disp_flush_ready(disp);
}



void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}

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
  lv_log_register_print_cb(my_print);
  //display.init(115200); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  ePaper_SPI.begin(CLK_PIN,5,MOSI_PIN,SS_PIN);
  // ePaper_SPI.begin();
  // SPISettings(10000000, MSBFIRST, SPI_MODE0)
  display.init(115200, true, 1, false, ePaper_SPI , SPISettings(10000000, MSBFIRST, SPI_MODE0)); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  Serial.print("OK");
  delay(1000000000);
  
  
  lv_init();  //初始化lvgl库
  lv_disp_draw_buf_init(&draw_buf, buf_1, NULL, screenWidth * screenHeight); //开启双缓冲



   static lv_disp_drv_t disp_drv;  
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;  /*Set your driver function*/
    disp_drv.draw_buf = &draw_buf;      /*Assign the buffer to the display*/
    lv_disp_drv_register(&disp_drv);    //注册显示屏

    screenMain = lv_obj_create(NULL);    //创建一个实际的屏幕对象
    labelName = lv_label_create(screenMain);
    // labelFans = lv_label_create(screenMain);  
    labelTime = lv_label_create(screenMain);
    labelLocation = lv_label_create(screenMain);
    labelWeather = lv_label_create(screenMain);
    labelTemperature = lv_label_create(screenMain);
    // imgHeadPhoto = lv_img_create(screenMain);


     while(1)
    {
        lv_label_set_long_mode(labelName, LV_LABEL_LONG_WRAP); 
        lv_label_set_text(labelName, "Hello! Yogurt");
        lv_obj_set_size(labelName, 120, 20);
        lv_obj_align(labelName, LV_ALIGN_DEFAULT, 0, 0);
        lv_obj_set_style_text_font(labelName,&lv_font_montserrat_14, 0);

        // lv_label_set_long_mode(labelLocation, LV_LABEL_LONG_WRAP); 
        // lv_label_set_text_fmt(labelLocation, "城市: %s", location);
        // lv_obj_set_size(labelLocation, 120, 20);
        // lv_obj_align(labelLocation, LV_ALIGN_DEFAULT, 0, 40);
        // lv_obj_set_style_text_font(labelLocation,&lv_font_chinese_14, 0);

        // lv_label_set_long_mode(labelWeather, LV_LABEL_LONG_WRAP); 
        // lv_label_set_text_fmt(labelWeather, "天气: %s",weather);
        // lv_obj_set_size(labelWeather, 120, 20);
        // lv_obj_align(labelWeather, LV_ALIGN_DEFAULT, 0, 60);
        // lv_obj_set_style_text_font(labelWeather,&lv_font_chinese_14, 0);

        // lv_label_set_long_mode(labelTemperature, LV_LABEL_LONG_WRAP); 
        // lv_label_set_text_fmt(labelTemperature, "气温: %s度",temperature);
        // lv_obj_set_size(labelTemperature, 120, 20);
        // lv_obj_align(labelTemperature, LV_ALIGN_DEFAULT, 0, 80);
        // lv_obj_set_style_text_font(labelTemperature,&lv_font_chinese_14, 0);

        // lv_img_set_src(imgHeadPhoto, &head_photo);
        // lv_obj_align(imgHeadPhoto, LV_ALIGN_CENTER, 64, 64);
        // lv_obj_set_size(imgHeadPhoto, 60, 60);

        lv_scr_load(screenMain); 

        lv_task_handler();
        vTaskDelay(1);
    }




  
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
  // display.clearScreen();
  // delay(5000);
  // helloFullScreenPartialMode();
  // delay(5000);
  // display.setRotation(2);
  // display.setFont(&FreeSansBold24pt7b);
  // display.setTextColor(GxEPD_RED);
  // int16_t tbx, tby; uint16_t tbw, tbh;
  // display.getTextBounds(HelloWorld, 25, 25, &tbx, &tby, &tbw, &tbh);
  
  // center the bounding box by transposition of the origin:
  // uint16_t x = ((display.width() - tbw) / 2) - tbx;
  // uint16_t y = ((display.height() - tbh) / 2) - tby;
  // display.setFullWindow();
  // uint16_t wh = FreeMonoBold9pt7b.yAdvance;
  // uint16_t wy = 110 - wh;
  // // display.setPartialWindow(0, wy, display.width(), wh);
  // display.firstPage();
  // // do
  // // {
  //    display.setPartialWindow(0, 0, display.width(), display.height());
  //   display.fillScreen(GxEPD_WHITE);
  //   // display.setCursor(x, y);
  //   // display.print(HelloWorld);
  //   display.setCursor(0,0);
  //   //  display.drawExampleBitmap(Bitmap648x480_3, sizeof(BitmapExample1), GxEPD::bm_default | GxEPD::bm_partial_update);
  //   display.drawBitmap(0,0,Bitmap648x480_3,648,480,GxEPD_BLACK);
  //   // display.update();
  //   // display.print(Bitmap648x480_1);
  //   display.display();
  //   // delay(30000);
  // // }
  // // while (display.nextPage());
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