#pragma once
#include<Windows.h>
//用户交互，坐标定位，颜色改变

//windows APi 字体颜色
#define redFont	244
#define blackFont 240
#define blueFont 241
#define greenFont 242

//定义坐标移动的方向
#define Up 0
#define Down 1
#define Left 2
#define Right 3

//界面上的坐标与实际控制台窗口界面的转换
#define pos_x(i) (1 + i * 10)
#define pos_y(j) (4 + 4 * j)	

//实际控制台坐标与界面坐标
#define _pos_x(i) (i-1)/10
#define _pos_y(i) (i-4)/4
void gotoXY(int x, int y);    //坐标定位
void setColor(int wAttributes);  //选择控制台字体颜色
bool  IsKeyDown(int key);    //键是否按下
void HideCursor();        //隐藏光标
void ChangeTitle(const char* str);