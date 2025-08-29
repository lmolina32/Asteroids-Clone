// testcursors.c
// simple program to test some of the available cursors
//   ( see file: /usr/include/X11/cursorfont.h )

#include "gfx2.h"

int main()
{
  gfx_open(500, 500, "testing mouse cursors"); 
  gfx_clear();

  gfx_text(100,100,"press one of these keys to change the cursor (q to quit):");
  gfx_text(150,125," a  w  g  h  p  t  = ");

  char c;   
  while(1) { 
    c = gfx_wait();

    // try a few cursors
    if (c == 'a') gfx_changecursor(XC_arrow);
    if (c == 'w') gfx_changecursor(XC_watch);
    if (c == 'g') gfx_changecursor(XC_gumby);
    if (c == 'h') gfx_changecursor(XC_hand1);
    if (c == 'p') gfx_changecursor(XC_pencil);
    if (c == 't') gfx_changecursor(XC_heart);
    if (c == '=') gfx_changecursor(XC_crosshair);

    // quit
    if (c == 'q')  break;
  }

  return 0;
}

