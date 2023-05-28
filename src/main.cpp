#include "ePaper.h"

//IO settings
int BUSY_Pin = 32; 
int RES_Pin = 33; 
int DC_Pin = 5; 
int CS_Pin = 16; 
int SCLK_Pin = 23;
int MOSI_Pin = 18;


void setup() {
   pinMode(BUSY_Pin, INPUT); 
   pinMode(RES_Pin,  OUTPUT);  
   pinMode(DC_Pin,   OUTPUT);    
   pinMode(CS_Pin,   OUTPUT);    
   //SPI
   SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0)); 
   SPI.begin (SCLK_Pin,-1,MOSI_Pin,CS_Pin);  
}

//Tips//
/*When the electronic paper is refreshed in full screen, the picture flicker is a normal phenomenon, and the main function is to clear the display afterimage in the previous picture.
  When the local refresh is performed, the screen does not flash.*/
/*When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is the input mode and the others are the output mode. */
  
void loop() {
   //Full screen refresh
    EPD_init(); //EPD init
    PIC_display(gImage_BW,gImage_R);//EPD_picture1
    EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    delay(20000);    
    
    EPD_init(); //EPD init
    PIC_display(gImage_BW1,gImage_R1);//EPD_picture1
    EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    delay(20000);   
    
    //Clean
    EPD_init(); //EPD init
    PIC_display_Clear();//EPD Clear
    EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    delay(20000); 
    
}
