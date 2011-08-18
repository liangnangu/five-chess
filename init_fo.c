#include<stdio.h>
#include"func.h"
#include<stdlib.h>
#include<sys/ioctl.h>
#include<linux/fb.h>
#include <fcntl.h>
#include<string.h>
#include<sys/mman.h>


fbscr_t fb_v ;// 重新定义结构体变量fb_v
int mx = 0;
int my = 0;
int init_fo(void)
{
    int fd;
    struct  fb_var_screeninfo fb_var;

    fd = open("/dev/fb0",O_RDWR);//注意open的用法open的三个参数

    if(fd < 0)
    {
        perror("open");
        exit(0);
    }
    if(ioctl(fd, FBIOGET_VSCREENINFO, &fb_var))
    {
        perror("ioctl");
        exit(0); 
    }
    printf("w=%d\tl=%d\tbit=%d\n",fb_var.xres,fb_var.yres,fb_var.bits_per_pixel);
    fb_v.w = fb_var.xres;
    fb_v.h = fb_var.yres;
    fb_v.bpp = fb_var.bits_per_pixel;

    fb_v.memo = mmap(NULL,fb_v.w*fb_v.h*fb_v.bpp/8,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0 );  //mmap函数的使用 第一个参数一定为NULL 第二个参数为屏幕大小 第三个参数为宏定义 第四个参数为设置共享 第五个参数为文件指针 第六个参数为0；
    if(fb_v.memo == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }
    memset(fb_v.memo,0,fb_v.w*fb_v.h*fb_v.bpp/8);//初始化内存中的一块区域
/*    int i, j;
    u32_t *p = fb_v.memo;
   for (i = 0; i < 1024; i++)
    {
        for (j = 0; j < 768; j++)
        {
            p[1024*i+j] = 0x00cbc547;// 注意这个地方是用一维数组模拟二维

        }
    }
    */
    return 0;
}
