/*文件内部存放基本元素*/

#include<stdio.h>
#include"various.h"
#include "func.h"
#include<stdlib.h>



int fb_one_pixel(int x, int y, u32_t color)                             //画点
{
    *((u32_t*)fb_v.memo + x + y * fb_v.w) = color;
    return 0;

}
void swap(int *a, int *b)                                              //交换元素
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int fb_line(int x1, int y1, int x2, int y2, u32_t color )             // 画线            
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int p = 0;
    int inc = ((dx*dy) > 0 ? 1 :-1);

    if(abs(dx) > abs(dy))
    {
        if(dx <0)
        {
            swap(&x1, &x2);
            swap(&y1, &y2);
            dx = -dx;
            dy = -dy;
        }
        dy = abs(dy);
        p = 2*dy - dx;
        while(x1 <= x2)
        {
            fb_one_pixel(x1,y1,color);
            x1++;
            if(p < 0)
            {
                p += 2*dy;
            }
            else 
            {
                y1 += inc;
                p += 2*(dy-dx);
           }
        }
     }
        else
        {
            
            if(dy <0)
            {
                swap(&x1, &x2);
                swap(&y1, &y2);
                dx = -dx;
                dy = -dy;
            }
            dx = abs(dx);
            p = 2*dx - dy;
            while(y1 <= y2)
            {
                fb_one_pixel(x1,y1,color);
                y1++;
                if(p < 0)
                {
                    p += 2*dx;
                }
                else 
                {
                    x1 += inc;
                    p += 2*(dx-dy);
                }
            }

        }
        return 0;
    }

    int fb_circle(int x0, int y0, int r, u32_t color)                             //画圆
    {
        
        int x = 0;
        int y = r;
        int p = 3 - 2*r;

        while(x <= y)
        {
            fb_line(x0+x, y0+y, x0-x, y0+y, color );
            fb_line(x0+y, y0+x, x0-y, y0+x, color );
            fb_line(x0+x, y0-y, x0-x, y0-y, color );
            fb_line(x0+y, y0-x, x0-y, y0-x, color );
            if(p < 0)
           {
               p += 4*x + 6;
           }
           else
           {
               p += 4*(x - y)+10;
               y--;
           }
        x++; 
        }
        return 0;
    }
    int  fb_chessboard(u32_t color)                                           //画棋盘
    {
        int i = 0,j = 0;
        int x1 = 100, y1 = 0, x2 = fb_v.w, y2 = 0;  
        if(i <= 25)
        {
            for(i = 0;i <25;i++)
            {
               fb_line( x1,  y1,  x2,  y2, color );
               y1 = (y2+30);
               y2 = y1;
            }
        }
   //     else
        {
            x1 = x2 = 100;
            y1 = 0;
            y2 = fb_v.h;
            for(j = 0; j<29;j++)
            {
                fb_line(x1, y1, x2, y2, color );
                x1 = (x2 + 30);
                x2 = x1;
            }
        }
    return 0;
    }
