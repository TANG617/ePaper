/*
 * @Author: LiTang litang0617@outlook.com
 * @Date: 2023-05-28 00:28:22
 * @LastEditors: LiTang litang0617@outlook.com
 * @LastEditTime: 2023-05-28 09:42:37
 * @FilePath: /ePaper/src/ePaper.h
 * @Description: ePaper
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef ePaper

// #include "Ap_29demo.h"
#include "Arduino.h"
#include <SPI.h>


//IO settings
#define  BUSY_PIN 32 
#define  RES_PIN 33
#define MOSI_PIN 18
#define CLK_PIN 23
#define SS_PIN 16
#define DC_PIN 5



#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>

#include <Fonts/FreeMonoBold9pt7b.h>






#define ePaper
#endif