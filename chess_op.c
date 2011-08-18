/*给棋子定位，修正其位置*/
#include<stdio.h>

#include"various.h"

int check(int x,int y)//具体判断
{
    int i = 0;
    int j = 0;
    int count = 1;
    int who = chess_board_array[x+y*X_NUM];
    if(0 == who)
    {
        return 0;
    }
    for (i = 1; i < 5; i++)//横线判断
    {
        if (who == chess_board_array[x+i+y*X_NUM])
        {
             count ++;
        }
        else
        {
            break;
        }
    }
    if(count == 5)
    {
        return who;
    }
        count = 1;
   for (i = 1, j = -1 ; i < 5; i++,j--)//竖线
    {
        if (who == chess_board_array[x+(y+j)*X_NUM])
        {
             count ++;
        }
        else
        {
            break;
        }
    }
    if(count == 5)
    {
        return who;
    }
   for (i = 1, j = -1 ; i < 5; i++,j--)//斜上
    {
        if (who == chess_board_array[x+i+(y+j)*X_NUM])
        {
             count ++;
        }
        else
        {
            break;
        }
    }
    if(count == 5)
    {
        return who;
    }
   for (i = 1, j = 1 ; j < 5; j++,i++)//斜下
    {
        if (who == chess_board_array[x+i+(y+j)*X_NUM])
        {
             count ++;
        }
        else
        {
            break;
        }
    }
    if(count == 5)
    {
        return who;
    }
    return 0;
}
int chess_put(int x, int y)
{
    int i = 0;
    int j = 0; 
    int winner = 0;
    chess_board_array[x+y*X_NUM] = player;//逻辑棋盘刷新
    //逻辑判断赢家
    for (j = 0; j < Y_NUM; j++)
    {
        for (i = 0; i < X_NUM; i++)
        {
            if((winner =  check(i,j)) > 0)
            {
               return winner; 
            }

        }
    }

    return 0;
}

int chess_doing(void)
{
    int rx = (mx-ST_X)%SPACE;//获取棋子在棋盘空格上的位置，距离最近的棋盘线的位置
    int ry = (my-ST_Y)%SPACE;
    int cx = mx - rx;//确定最近棋盘线位置
    int cy = my - ry;
    int winner = 0;
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
    fb_circle(cx,cy,R,current_color);
    winner = chess_put((cx-ST_Y)/SPACE,(cy-ST_Y)/SPACE);//定位数组模拟棋盘的落子点
    if (winner > 0)
    {
        return winner;
    }
    if(current_color == WHITE)//落子后交换选手 切换棋子颜色
    {
        current_color = BLACK;
        player = 1;
    }
    else
    {
        current_color = WHITE;
        player = 2;
    }

    return 0;
}
