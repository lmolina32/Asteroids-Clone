// testfont.c
// testing fonts
//   (see file:  /usr/share/X11/fonts/misc/fonts.alias )

#include "gfx2.h"

int main()
{
  // try one of these two fonts below, or try some others from the fonts.alias file

  char *thefont = "-misc-fixed-bold-r-normal--13-120-75-75-c-70-iso8859-1";
  // char *thefont = "12x24";

  char *mytext = "I am in the CSE department";   // the string to display

  gfx_open(600, 400, "My window"); 
  gfx_clear();
  gfx_color(255,255,255); 

  gfx_changefont(thefont);   // set the new font

  while(1) { 
    gfx_text(100, 200, mytext);

    if (gfx_wait() == 'q') break;
  }

  return 0;
}

