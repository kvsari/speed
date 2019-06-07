/**
 * SYSTEM
 *
 * Drawing system. Carries out the pixel plotting onto the video memory for presentation
 * by another system.
 */

# ifndef _DRAW_H_
# define _DRAW_H_

#include "video.h"

/**
 * Represent a 32bit colour value with alpha and retain easy per field access. To be used
 * with `SDL_Surface` surfaces.
 *
 * NOTE: Set the alpha (rgba[3]) to 255 for full opaqueness. At 0 it is totally tansparent
 *       and the pixel won't be seen.
 */
union RGBA8888 {
  Uint8  rgba[4];
  Uint32 val;
};

/* Bunch of debug/test functions first... */

/**
 * Pixel size is implied by the pointer type. Does no bounds checking!
 */
void plot_pixel(
  Uint32 *pixels,
  int span,
  int plot_x,
  int plot_y,
  union RGBA8888 colour);

# endif
