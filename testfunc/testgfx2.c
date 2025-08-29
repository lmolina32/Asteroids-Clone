// testgfx2.c
// a simple example to test some of gfx2's new geometric functions

#include "gfx2.h"

int main()
{
  gfx_open(600, 400, "testing some new gfx2 functions");
  gfx_clear();

  gfx_color(0,200,100);
  gfx_ellipse(100,50,30,20);

  gfx_color(200,100,50);
  gfx_arc(300,150,50,150,75,130);
  gfx_rectangle(100,100,150,50);

  gfx_color(0,200,50);
  gfx_fill_rectangle(100,300,150,50);

  gfx_color(0,255,255);
  gfx_fill_arc(300,150,200,200,20,100);

  gfx_flush();

  while( gfx_wait() != 'q' );

  return 0;
}

