/**
 * SYSTEM
 *
 * Drawing system. Carries out the pixel plotting onto the video memory for presentation
 * by another system.
 */

# ifndef _DRAW_H_
# define _DRAW_H_

#include "video.h"

// Bunch of debug/test functions first...

void plot_pixel_01(
  struct VideoContext *v_context,
  Uint32 x,
  Uint32 y,
  Uint8 r,
  Uint8 g,
  Uint8 b);



# endif
