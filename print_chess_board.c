#include<stdio.h>
#include "various.h"
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
