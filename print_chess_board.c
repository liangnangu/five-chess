#include<stdio.h>
#include "various.h"
#include"func.h"
void bga(void)
{
    int i = 0 ;
    int j = 0;
    for (j = 0; j < (fb_v.w-1); j++)
    {
        for (i = 0; i < (fb_v.h-1) ; i++)
        {
            fb_one_pixel(j,i,0x00ffd39b);
        }
    }
}
int chess_board(u32_t color)
{
    int i ;
    for (i = 0; i < Y_NUM; i++)
    {
        fb_line(ST_X, ST_Y+i*SPACE, ST_X+(X_NUM-1)*SPACE, ST_Y+i*SPACE,color);
    }
    for (i = 0; i < X_NUM; i++)
    {
        fb_line(ST_X+i*SPACE, ST_Y, ST_X+i*SPACE, ST_Y+(Y_NUM-1)*SPACE, color);
    }
    return 0;
}
