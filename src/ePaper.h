/*
 * @Author: LiTang litang0617@outlook.com
 * @Date: 2023-05-28 00:28:22
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-10-10 19:27:45
 * @FilePath: /ePaper/src/ePaper.h
 * @Description: ePaper
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef ePaper

// #include "Ap_29demo.h"
#include "Arduino.h"
#include <SPI.h>


// //IO settings
// #define  BUSY_PIN 4 
// #define  RES_PIN  7
// #define  DC_PIN   6
// #define  SS_PIN   10
// #define  CLK_PIN  3
// #define  MOSI_PIN 2


#define  BUSY_PIN 0
#define  RES_PIN  1
#define  DC_PIN   2
#define  SS_PIN   3
#define  CLK_PIN  9
#define  MOSI_PIN 10






#include <GxEPD2_BW.h>
// #include <GxEPD2_3C.h>

#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/HarmonyFonts/HarmonyOS_Sans_Bold60pt7b.h>






#define ePaper
#endif