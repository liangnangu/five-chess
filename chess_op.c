/*给棋子定位，修正其位置*/
#include<stdio.h>

#include"various.h"


int chess_doing(void)
{
    int rx = (mx-ST_X)%SPACE;//获取棋子在棋盘空格上的位置，距离最近的棋盘线的位置
    int ry = (my-ST_Y)%SPACE;
    int cx = mx - rx;//确定最近棋盘线位置
    int cy = my - ry;
    if((mx < ST_X)||(mx > (ST_X + (X_NUM-1)*SPACE)))//判断是否在棋盘内部（横向）
    {
        return 0;
    }
    if((my < ST_Y)||(my > (ST_Y + (Y_NUM-1)*SPACE)))//判断是否在棋盘内部（竖线）
    {
        return 0;
    }
    if(rx > (SPACE/2))//给棋子重新定位
    {
        cx += SPACE;
    }
    if(ry > (SPACE/2))//棋子重新定位
    {
        cy += SPACE;
    }
    fb_circle(cx,cy,R,0x00345436); 
    return 0;
}
