#include "ePaper.h"

GxEPD2_3C<GxEPD2_420c_1680, GxEPD2_420c_1680::HEIGHT> display(GxEPD2_420c_1680(/*CS*/ SS_PIN, /*DC*/ DC_PIN, /*RST*/ RES_PIN, /*BUSY*/ BUSY_PIN)); // 

SPIClass ePaper_SPI;

void helloWorld();


void setup()
{
  //display.init(115200); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  ePaper_SPI.begin(CLK_PIN,-1,MOSI_PIN,SS_PIN);
  // SPISettings(10000000, MSBFIRST, SPI_MODE0)
  display.init(115200, true, 2, false, ePaper_SPI , SPISettings(10000000, MSBFIRST, SPI_MODE0)); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  helloWorld();
  display.hibernate();
}

const char HelloWorld[] = "We hold these truths to be self-evident, that all men are created equal, that they are endowed by their Creator with certain unalienable Rights, that among these are Life, Liberty and the pursuit of Happiness.";



void loop() {};


void helloWorld()
{
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
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