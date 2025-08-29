// xstructex1.c
// simple example to showcase Xlib's
//   XPoint and XSegment structs

#include "gfx2.h"

int main()
{
  XPoint pt = {150, 150};
  XSegment seg = {200, 100, 250, 200};

  gfx_open(400, 300, "My window");
  gfx_color(255, 255, 255); 

  while(1) {
    gfx_clear();

    gfx_point(pt.x, pt.y);
    gfx_line(seg.x1, seg.y1, seg.x2, seg.y2);

    gfx_flush(); 
    if (gfx_wait() == 'q') break;
  }

  return 0;
}

