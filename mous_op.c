#include<stdio.h>
#include"various.h"
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

#define X___   0x00f173ac
#define T___   0x00000001
#define BORD   0x002b4490
#define C_W    10
#define C_H    17

static u32_t coursor_pixel[C_W*C_H]=   ///这个结构体划出了鼠标的形状
{
    BORD,T___,T___,T___,T___,T___,T___,T___,T___,T___,
    BORD,BORD,T___,T___,T___,T___,T___,T___,T___,T___,
    BORD,X___,BORD,T___,T___,T___,T___,T___,T___,T___,
    BORD,X___,X___,BORD,T___,T___,T___,T___,T___,T___,
    BORD,X___,X___,X___,BORD,T___,T___,T___,T___,T___,
    BORD,X___,X___,X___,X___,BORD,T___,T___,T___,T___,
    BORD,X___,X___,X___,X___,X___,BORD,T___,T___,T___,
    BORD,X___,X___,X___,X___,X___,X___,BORD,T___,T___,
    BORD,X___,X___,X___,X___,X___,X___,X___,BORD,T___,
    BORD,X___,X___,X___,X___,X___,X___,X___,X___,BORD,
    BORD,X___,X___,X___,X___,X___,BORD,BORD,BORD,BORD,
    BORD,X___,X___,BORD,X___,X___,BORD,T___,T___,T___,
    BORD,X___,BORD,T___,BORD,X___,X___,BORD,T___,T___,
    BORD,BORD,T___,T___,BORD,X___,X___,BORD,T___,T___,
    T___,T___,T___,T___,T___,BORD,X___,X___,BORD,T___,
    T___,T___,T___,T___,T___,BORD,X___,X___,BORD,T___,
    T___,T___,T___,T___,T___,T___,BORD,BORD,T___,T___,
};


u32_t bg[C_W*C_H]={};
int draw_cursor(int x, int y)  //在屏幕上打印出鼠标的图形
{
    int i = 0;
    int j = 0;
    save_bg(mx, my);
    for (j = 0; j < C_H; j++)
    {
        for (i = 0; i < C_W; i++)
        {
            fb_one_pixel(x+i,y+j,coursor_pixel[i+j*C_W]);
        }
    }
    return 0;
}

int save_bg(int x, int y) // 保存背景颜色
{
    int i = 0;
    int j = 0;
    for (j = 0; j < C_H; j++)
    {
        for (i = 0; i < C_W; i++)
        {
            bg[i+j*C_W] = *((u32_t *)fb_v.memo+x+i+(y+j)*fb_v.w);
        }
    }
    return 0;
}

int restore_bg(int x, int y)//恢复背景颜色
{
    int i = 0;
    int j = 0;
    for (j = 0; j < C_H; j++)
    {
        for (i = 0; i < C_W; i++)
        {
            fb_one_pixel(x+i,y+j,bg[i+j*C_W]);
        }
    }
    return 0;
}

int get_mose_info(int fd ,mouse_event *p)//读取鼠标信息
{
    char buf[8];
    int n = 0;
    n = read(fd ,buf,3);
    if(n > 0)
    {
        p->dx = buf[1];
        p->dy = -buf[2];
        p->button = (buf[0] & 0x07);
    }
    return n;
}

int mouse_doing(void) //鼠标工作
{
    int fd = 0;
    mouse_event m_e;
    int press_do = 0;
    char flag;
    fd = open("/dev/input/mice",O_RDWR|O_NONBLOCK);
    if(fd == -1)
    {
        perror("mice");
        exit(0);
    }

    mx = fb_v.w/2; 
    my = fb_v.h/2;
    draw_cursor(mx, my);


    while(1)
    {
        if(get_mose_info(fd,&m_e)>0)
        {
            restore_bg(mx,my);
              mx+=m_e.dx;                 //鼠标寻址
              my+=m_e.dy;                  // 
              if(mx < 0)                  //修正鼠标水平移动
               {mx = 0;}                  //
              if(mx > (fb_v.w - C_W))     //
              {mx = fb_v.w - C_W;}          //
              if(my < 0)                  //
               {my = 0;}                  //
              if(my > (fb_v.h - C_H))     //
              {my = fb_v.h - C_H;}        //
            switch(m_e.button)            //
            {
                case 0:                  //
                if(press_do == 1)          //
                {
                    press_do = 0;           //
                  //  fb_circle(mx,my,R,0x00aabbcc);
                    flag = chess_doing();
                }
                if(press_do == 2)
                {
                    
                }
                if(press_do == 4)
                {
                }
                break;
                case 1:
                press_do = 1;
                break;
                case 2:
                press_do = 2;
                break;
                case 4:
                press_do = 4;
                break;
                default:break; 
            }
            draw_cursor(mx,my);
            if (flag > 0)
            {
                printf("who player %d wine\n",flag);
                break;
            }
        }
    }
    close(fd);
    return 0;
}
