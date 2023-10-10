/*
 * @Author: LiTang litang0617@outlook.com
 * @Date: 2023-10-10 15:55:02
 * @LastEditTime: 2023-10-10 18:21:13
 * @FilePath: /ePaper/src/currentTime.cpp
 * @Description: 
 */
#include "currentTime.h"

time_t initTimeStamp = 1696933263;
tmElements_t timeInfo;
void updateTime(int currnetTime){
    breakTime(initTimeStamp+currnetTime/1000,timeInfo);
}