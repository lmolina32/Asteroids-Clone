// testpoly.c
// this program tests the gfx_polygon and gfx_fill_polygon functions
// it also shows the use of the XPoint struct that is part of Xlib
// (as well as how to set up different fonts)

#include "gfx2.h"
#include <math.h>

int main()
{
  // initialize a point (using X11's XPoint struct)
  XPoint pt = {300,450};

  // set up 3 arrays of points
  XPoint mypts1[] = { {50,60},{400,120},{200,150},{100,100} };
  XPoint mypts2[] = { {550,160},{330,220},{500,450},{650,300},{550,160} };
  XPoint mypts3[] = { {150,160},{300,350},{200,400},{220,350},{100,300} };
  // determine their sizes
  int sz1 = sizeof(mypts1)/sizeof(XPoint);
  int sz2 = sizeof(mypts2)/sizeof(XPoint);
  int sz3 = sizeof(mypts3)/sizeof(XPoint);

  gfx_open(700, 600, "Testing Polygons"); 

  char c = 0;
  while(c != 'q') { 
    gfx_clear(); 

    gfx_color(255,255,255);         // color: white 
    gfx_point(pt.x, pt.y);          // draw the point
    gfx_circle(pt.x, pt.y, 10);     // draw a small circle around it

    // change to a new font, using its full name
    gfx_changefont((char *) "-misc-fixed-bold-r-normal--13-120-75-75-c-70-iso8859-1");
    gfx_text(250, 500, "  notice the point");
    // change to a new font, using its alias
    gfx_changefont((char *) "6x10");
    gfx_text(250, 520, "  (inside the circle)");
    
    // draw the polygons
    gfx_color(255,255,0);           // color: yellow 
    gfx_polygon(mypts1, sz1);       // draw the 1st polygon (open)
    gfx_color(0,255,0);             // color: green
    gfx_polygon(mypts2, sz2);       // draw the 2nd polygon (closed)
    gfx_color(0,255,255);           // color: cyan
    gfx_fill_polygon(mypts3, sz3);  // draw the 3rd polygon (filled)

    gfx_flush();
    c = gfx_wait();
  }
}

