#include "Arduino.h"
#include <SPI.h>
#include "Ap_29demo.h"

//IO settings
int BUSY_Pin = 32; 
int RES_Pin = 33; 
int DC_Pin = 5; 
int CS_Pin = 16; 
// SCLK--GPIO23
// MOSI---GPIO18


#define EPD_W21_CS_0 digitalWrite(CS_Pin,LOW)
#define EPD_W21_CS_1 digitalWrite(CS_Pin,HIGH)
#define EPD_W21_DC_0  digitalWrite(DC_Pin,LOW)
#define EPD_W21_DC_1  digitalWrite(DC_Pin,HIGH)
#define EPD_W21_RST_0 digitalWrite(RES_Pin,LOW)
#define EPD_W21_RST_1 digitalWrite(RES_Pin,HIGH)
#define isEPD_W21_BUSY digitalRead(BUSY_Pin)
//400*300///////////////////////////////////////

#define MONOMSB_MODE 1
#define MONOLSB_MODE 2 
#define RED_MODE     3

#define MAX_LINE_BYTES 50// =400/8
#define MAX_COLUMN_BYTES  300

#define ALLSCREEN_GRAGHBYTES  15000

////////FUNCTION//////
void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char command);
void EPD_W21_WriteCMD(unsigned char command);
//EPD
void EPD_init(void);//Electronic paper initialization
void EPD_Update(void);
void EPD_sleep(void);

//Display 
void EPD_Display(unsigned char *BW_Image,unsigned char *R_Image);
void PIC_display_Clear(void);

void setup() {
   pinMode(BUSY_Pin, INPUT); 
   pinMode(RES_Pin, OUTPUT);  
   pinMode(DC_Pin, OUTPUT);    
   pinMode(CS_Pin, OUTPUT);    
   //SPI
   SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0)); 
   SPI.begin ();  
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
    delay(2000);    
    
    EPD_init(); //EPD init
    PIC_display(gImage_BW1,gImage_R1);//EPD_picture1
    EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    delay(2000);   
    
    //Clean
    EPD_init(); //EPD init
    PIC_display_Clear();//EPD Clear
    EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    delay(2000); 
    while(1);
}



///////////////////EXTERNAL FUNCTION////////////////////////////////////////////////////////////////////////
//////////////////////SPI///////////////////////////////////
void SPI_Write(unsigned char value)                                    
{                                                           
    SPI.transfer(value);

}

void EPD_W21_WriteCMD(unsigned char command)
{
  EPD_W21_CS_0;                   
  EPD_W21_DC_0;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}
void EPD_W21_WriteDATA(unsigned char data)
{
  EPD_W21_CS_0;                   
  EPD_W21_DC_1;   // data write
  SPI_Write(data);
  EPD_W21_CS_1;
}


/////////////////EPD settings Functions/////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//SSD1683
void EPD_init(void)
{
    EPD_W21_RST_0;  // Module reset      
    delay(10); //At least 10ms delay 
    EPD_W21_RST_1; 
    delay(10); //At least 10ms delay  
    
    Epaper_READBUSY();    //waiting for the electronic paper IC to release the idle signal
    EPD_W21_WriteCMD(0x12);     //SWRESET
    Epaper_READBUSY();  //waiting for the electronic paper IC to release the idle signal
  
    EPD_W21_WriteCMD(0x01);  // Set MUX as 300
    EPD_W21_WriteDATA(0x2B);           
    EPD_W21_WriteDATA(0x01);
    EPD_W21_WriteDATA(0x00); 

    EPD_W21_WriteCMD(0x11);  // Data entry mode
    EPD_W21_WriteDATA(0x01);   
    
    EPD_W21_WriteCMD(0x44); 
    EPD_W21_WriteDATA(0x00); // RAM x address start at 0
    EPD_W21_WriteDATA(0x31); // RAM x address end at 31h(49+1)*8->400
    EPD_W21_WriteCMD(0x45); 
    EPD_W21_WriteDATA(0x2B);   // RAM y address start at 12Bh     
    EPD_W21_WriteDATA(0x01);
    EPD_W21_WriteDATA(0x00); // RAM y address end at 00h     
    EPD_W21_WriteDATA(0x00);
    
    EPD_W21_WriteCMD(0x3C); // board
    EPD_W21_WriteDATA(0x01); // 

    EPD_W21_WriteCMD(0x18);
    EPD_W21_WriteDATA(0X80);

    EPD_W21_WriteCMD(0x4E); 
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteCMD(0x4F); 
    EPD_W21_WriteDATA(0x2B);
    EPD_W21_WriteDATA(0x01);
}
//////////////////////////////All screen update////////////////////////////////////////////


void PIC_display(const unsigned char *BW_datas,const unsigned char *R_datas)
{
   unsigned int i;  
  EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     EPD_W21_WriteDATA(*BW_datas);
      BW_datas++;
   }
  EPD_W21_WriteCMD(0x26);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     EPD_W21_WriteDATA(~(*R_datas));
      R_datas++;
   }
  //update
  EPD_Update();  
}

/////////////////////////////////////////////////////////////////////////////////////////
void EPD_Update(void)
{   
  EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();   

}

void EPD_sleep(void)
{  
 EPD_W21_WriteCMD(0x10); //enter deep sleep
 EPD_W21_WriteDATA(0x01); 
  delay(100);
}
void Epaper_READBUSY(void)
{ 
  while(1)
  {   //=1 BUSY
     if(isEPD_W21_BUSY==0) break;
  }  
}

void PIC_display_Clear(void)
{
   unsigned int i;  
  EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     EPD_W21_WriteDATA(0xff);
   }
  EPD_W21_WriteCMD(0x26);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     EPD_W21_WriteDATA(0x00);
   }
  //update
  EPD_Update(); 
}

//////////////////////////////////END//////////////////////////////////////////////////
