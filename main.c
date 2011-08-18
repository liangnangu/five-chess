#include<stdio.h>
#include<unistd.h>
#include"func.h"
#include "various.h"

//int chessboard()

int main(int argc, const char *argv[])
{
    init_fo();
//    fb_one_pixel(100,200,0x0000ff00);

//    fb_line(0, 0, fb_v.w-1, fb_v.h-1,0x000000ff);
  //  fb_line(fb_v.w-1, 0, 0, fb_v.h-1,0x000000ff);
  //  fb_line(300, fb_v.h-1,400,0,0x00abcdef);
   // fb_circle(500, 300, 240, 0x00ff0000);
      chess_board(0x000000ff);
      print_chess(0x00d71345);
   // save_bg(512,384);
   // draw_cursor(512,384);
   // sleep(1);
   // restore_bg(512,384);
   // draw_cursor(300,400);
    mouse_doing();
    chess_doing();
    return 0;
}
