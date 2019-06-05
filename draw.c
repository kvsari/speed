// Drawing
#include <stdio.h>
#include <assert.h>

#include "SDL_render.h"

#include "draw.h"

void plot_pixel_01(
  struct VideoContext *v_context,
  Uint32 x,
  Uint32 y,
  Uint8 r,
  Uint8 g,
  Uint8 b)
{
  void *pixels;
  int pitch;

  // We'll just assume it works and not bother checking the return value.
  SDL_LockTexture(v_context->texture, NULL, &pixels, &pitch);

  // sanity check that the pixels_wide * pixel_bytes == pitch;
  assert(pitch == v_context->pitch_bytes);

  Uint32 colour = (r << 24) | (g << 16) | (b << 8);  

  //printf("PITCH: %d\n", pitch);

  //(Uint32 *)

  SDL_UnlockTexture(v_context->texture);
}
