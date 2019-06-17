/**
 * SYSTEM
 *
 * Drawing system. Carries out the pixel plotting onto the video memory for presentation
 * by another system. Draw system assumes all colour values are 24bit but with 32bits
 * assigned (we ignore the alpha).
 */

# ifndef _DRAW_H_
# define _DRAW_H_

#include "video.h"

/**
 * Represent a 32bit colour value with alpha and retain easy per field access. To be used
 * for writing to raw system memory in the same format as the `SDL_Texture` assigned to the
 * display renderer.
 *
 * NOTE: Set the alpha (rgba[3]) to 255 for full opaqueness. At 0 it is totally tansparent
 *       and the pixel won't be seen.
 *
 * NOTE: The aplha value is ignored on the software side. It only counts when being slurped
 *       up by an `SDL_Texture`.
 */
union RGBA8888 {
  Uint8  rgba[4];
  Uint32 val;
};

/**
 * Raw 32bit memory block used for drawing a frame. The size of each pixel equals an
 * `RGBA8888`. This memory is then slurped by the video system to be displayed.
 */
struct DrawBuffer {
  Uint32 *pixels;
  int bytes;
  int pixel_span;
  int pixel_rows;
};

/**
 * Create a `DrawBuffer` set to NULL.
 */
struct DrawBuffer create_empty_draw_buffer();

/**
 * Initialize an empty `DrawBuffer`. Returns -1 if there was a malloc error. If the draw
 * buffer is already initialized, will attempt to realloc.
 */
int initialize_draw_buffer(struct DrawBuffer *draw_buffer, const size_t x, const size_t y);

/* Bunch of debug/test functions first... */

/**
 * Pixel memory size is implied by the pointer type. Does no bounds checking!
 */
void plot_pixel(
  struct DrawBuffer *draw_buffer,
  const int plot_x,
  const int plot_y,
  const union RGBA8888 colour);

# endif
