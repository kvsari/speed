// Drawing
#include <stdio.h>
#include <assert.h>

#include "SDL_render.h"

#include "draw.h"

void plot_pixel(
  Uint32 *pixels,
  int span,
  int plot_x,
  int plot_y,
  union RGBA8888 colour)
{
  pixels += plot_y * span + plot_x;
  *pixels = colour.val;
}
