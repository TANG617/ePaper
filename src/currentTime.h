/*
 * @Author: LiTang litang0617@outlook.com
 * @Date: 2023-10-10 15:54:55
 * @LastEditTime: 2023-10-10 16:22:14
 * @FilePath: /ePaper/src/currentTime.h
 * @Description: 
 */
#ifndef Time_H
#define Time_H
#include <TimeLib.h>

extern time_t initTimeStamp;
extern tmElements_t timeInfo;
void updateTime(int currnetTime);


#endif