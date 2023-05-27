/*
 * @Author: LiTang litang0617@outlook.com
 * @Date: 2023-05-28 00:30:04
 * @LastEditors: LiTang litang0617@outlook.com
 * @LastEditTime: 2023-05-28 00:30:43
 * @FilePath: /ePaper/src/ePaper.cpp
 * @Description: 
 * 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include "ePaper.h"
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
