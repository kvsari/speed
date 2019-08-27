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

//--------------------------------------------
// Types
//--------------------------------------------

/**
 * Represent a 32bit colour value with alpha and retain easy per field access. To be used
 * for writing to raw system memory in the same format as the `SDL_Texture` assigned to the
 * display renderer.
 *
 * NOTE: Set the alpha (abgr[3]) to 255 for full opaqueness. At 0 it is totally tansparent
 *       and the pixel won't be seen.
 *
 * NOTE: The aplha value is ignored on the software side. It only counts when being slurped
 *       up by an `SDL_Texture`.
 *
 * NOTE: This union corresponds to SDL_PIXELFORMAT_ABGR8888 which is used on little endian
 *       machines. On big endian, all the colour values will be screwed up!
 */
union ABGR8888 {
  Uint8  abgr[4];
  Uint32 val;
};

/**
 * A 2D line for drawing onto a `DrawBuffer`.
 *
 * NOTE: Try using a union of u16[4] and u64.
 */
struct Line {
  int x0;
  int y0;
  int x1;
  int y1;
};

/**
 * Rectangle for drawing usage with the `DrawBuffer`.
 *
 * NOTE: Try using a union of u16[4] and u64.
 */
struct Rectangle {
  int x;
  int y;
  int w;
  int h;
};

/**
 * Raw 32bit memory block used for drawing a frame. The size of each pixel equals an
 * `RGBA8888`. This memory is then slurped by the video system to be displayed.
 */
struct DrawBuffer {
  Uint32 *pixels;
  int pixel_count;
  int pixel_span;
  int pixel_rows;
};

//--------------------------------------------
// State Management
//--------------------------------------------

/**
 * Create a `DrawBuffer` set to NULL.
 */
struct DrawBuffer
create_empty_draw_buffer();

/**
 * Initialize an empty `DrawBuffer`. Returns -1 if there was a malloc error. If the draw
 * buffer is already initialized, will attempt to realloc.
 */
int
initialize_draw_buffer(struct DrawBuffer *draw_buffer, const size_t x, const size_t y);

/**
 * As the name says.
 */
void
deinitialize_draw_buffer(struct DrawBuffer *draw_buffer);

//--------------------------------------------
// Plotting
//--------------------------------------------

/**
 * Pixel memory size is implied by the pointer type. Does no bounds checking!
 */
void
plot_pixel(
  struct DrawBuffer *draw_buffer,
  const int plot_x,
  const int plot_y,
  const Uint32 colour);

/**
 * Clip a line producing a new line which falls within the supplied `DrawBuffer`. The
 * supplied line is modified. 0 is returned if the clipped line is within the `DrawBuffer`.
 * -1 is returned if the line is completely out of bounds.
 */
int
clip_line(
  const struct DrawBuffer *draw_buffer,
  const struct Rectangle *clip_rect,
  struct Line *line);
  
/**
 * Use a modified Bresenhams line drawing algorithm to plot a line. Does no bounds checks!
 */
void
plot_line(
  struct DrawBuffer *draw_buffer,
  const struct Line *line,
  const Uint32 colour);

/**
 * Plot a rectangle onto the `DrawBuffer`. Doesn't do any clipping.
 */
void
plot_rectangle(
  struct DrawBuffer *draw_buffer,
  const struct Rectangle *rectangle,
  const Uint32 colour);
  

///////////////////////////////////
//   TESTING GRAPHICAL FUNCTIONS //
///////////////////////////////////

/**
 * Draw one frame of snow.
 */
void
snow(struct DrawBuffer *draw_buffer, const Uint32 snow_colour);

/**
 * Simple plasma using expensive sine functions.
 */
void
plasma_01(struct DrawBuffer *draw_buffer);

/**
 * Same as above but use an increment to make it move.
 */
void
plasma_02(struct DrawBuffer *draw_buffer, int inc);

# endif
