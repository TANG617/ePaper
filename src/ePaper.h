/*
 * @Author: LiTang litang0617@outlook.com
 * @Date: 2023-05-28 00:28:22
 * @LastEditors: LiTang litang0617@outlook.com
 * @LastEditTime: 2023-05-28 00:41:30
 * @FilePath: /ePaper/src/ePaper.h
 * @Description: ePaper
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef ePaper

//IO settings
extern int BUSY_Pin; 
extern int RES_Pin; 
extern int DC_Pin; 
extern int CS_Pin; 
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




#include "Ap_29demo.h"
#include "Arduino.h"
#include <SPI.h>
#include <pgmspace.h>
////////FUNCTION//////
void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char command);
void EPD_W21_WriteCMD(unsigned char command);
//EPD
void EPD_init(void);//Electronic paper initialization
void EPD_Update(void);
void EPD_sleep(void);
void Epaper_READBUSY(void);

//Display 
void EPD_Display(unsigned char *BW_Image,unsigned char *R_Image);
void PIC_display_Clear(void);
void PIC_display(const unsigned char *BW_datas,const unsigned char *R_datas);
#define ePaper
#endif