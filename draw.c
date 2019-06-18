// Drawing
#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "SDL_log.h"

#include "draw.h"

//const union RGBA8888 colour_black = { .rgba = { 0, 0, 0, 0 } };

struct DrawBuffer create_empty_draw_buffer() {
  struct DrawBuffer draw_buffer;
  draw_buffer.pixels = NULL;
  draw_buffer.pixel_count = 0;
  draw_buffer.pixel_span = 0;
  draw_buffer.pixel_rows = 0;

  return draw_buffer;
}

int initialize_draw_buffer(struct DrawBuffer *draw_buffer, const size_t x, const size_t y) {
  draw_buffer->pixels = realloc(draw_buffer->pixels, x * y * sizeof(Uint32));

  if (draw_buffer->pixels == NULL) {
    int err = errno;
    SDL_LogError(
      SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't create draw software pixel surface; errno: %d, perror: %s\n",
      err,
      strerror(err));
    return -1;
  }

  draw_buffer->pixel_count = x * y;
  draw_buffer->pixel_span = x;
  draw_buffer->pixel_rows = y;

  return 0;
}

void deinitialize_draw_buffer(struct DrawBuffer *draw_buffer) {
  free(draw_buffer->pixels);
  draw_buffer->pixels = NULL;
  draw_buffer->pixel_count = 0;
  draw_buffer->pixel_span = 0;
  draw_buffer->pixel_rows = 0;
}

void plot_pixel(
  struct DrawBuffer *draw_buffer,
  const int plot_x,
  const int plot_y,
  const union RGBA8888 colour)
{
  Uint32 *pixels = draw_buffer->pixels;
  pixels += plot_y * draw_buffer->pixel_span + plot_x;
  *pixels = colour.val;
}

int clip_line(const struct DrawBuffer *draw_buffer, struct Line *line) {
  int x0 = line->x0;
  int y0 = line->y0;
  int x1 = line->x1;
  int y1 = line->y1;
  
  // First, test to see if line is completely outside bounds.
  if(((x0 <= 0) && (x1 <= 0)) ||
     ((x0 >= draw_buffer->pixel_span) && (x1 >= draw_buffer->pixel_span)) ||
     ((y0 <= 0) && (y1 <= 0)) ||
     ((y0 >= draw_buffer->pixel_rows) && (y1 >= draw_buffer->pixel_rows))) {
    return -1;
  }
   
  // Calculate all delta's
  int dx0 = -(x1 - x0);
  int dx1 = (x1 - x0);
  int dy0 = -(y1 - y0);
  int dy1 = (y1 - y0);
  
  int qx0 = x0;
  int qx1 = draw_buffer->pixel_span - x0;
  int qy0 = y0;
  int qy1 = draw_buffer->pixel_rows - y0;
  
  // Test to see if line is outside the bounding box, if so we just leave
  // This test may be unecessary...
  if(((dx0 == 0) && (qx0 < 0)) ||
     ((dx1 == 0) && (qx1 < 0)) ||
     ((dy0 == 0) && (qy0 < 0)) ||
     ((dy1 == 0) && (qy1 < 0))) {
    return -1;
  }

  // Commence line chopping.
  float t0 = 0;
  float t1 = 1;
  float  rx0, rx1, ry0, ry1;

  // Left edge check
  if(dx0 != 0) {
    rx0 = (float) qx0 / dx0;
    if(dx0 < 0)
      t0 = rx0 > t0 ? rx0 : t0;
    else
      t1 = rx0 < t1 ? rx0 : t1;
  }
  
  // Top edge check
  if(dy0 != 0) {
    ry0 = (float) qy0 / dy0;
    if(dy0 < 0)
      t0 = ry0 > t0 ? ry0 : t0;
    else
      t1 = ry0 < t1 ? ry0 : t1;
  }
  
  // Right edge check
  if(dx1 != 0) {
    rx1 = (float) qx1 / dx1;
    if(dx1 < 0)
      t0 = rx1 > t0 ? rx1 : t0;
    else
      t1 = rx1 < t1 ? rx1 : t1;
  }
  
  // Bottom edge check
  if(dy1 != 0) {
    ry1 = (float) qy1 / dy1;
    if(dy1 < 0)
      t0 = ry1 > t0 ? ry1 : t0;
    else
      t1 = ry1 < t1 ? ry1 : t1;
  }
  
  // Line falls outside of the clipping box
  if(t0 > t1)
    return -1;
  
  line->x0 = x0 + floor(t0 * (x1 - x0) + 0.5);
  line->y0 = y0 + floor(t0 * (y1 - y0) + 0.5);
  line->x1 = x0 + floor(t1 * (x1 - x0) + 0.5);
  line->y1 = y0 + floor(t1 * (y1 - y0) + 0.5);

  return 0;
}

void plot_line(
  struct DrawBuffer *draw_buffer,
  const struct Line *line,
  const union RGBA8888 colour)
{
  Uint32 *pixels = draw_buffer->pixels;
  int dx = abs(line->x1 - line->x0);
  int dy = abs(line->y1 - line->y0);
  int stepx0, stepx1, stepy0, stepy1;
  int denominator, numerator, numerator_add, line_pixels;

  // Figure out which direction we're going with the pointer arithmetic. Left or right.
  if (line->x1 >= line->x0) {
    stepx0 = stepx1 = 1;
  } else {
    stepx0 = stepx1 = -1;
  }

  // Ditto for Y coordinate but this time Up or Down (by jumping through the buffer).
  if (line->y1 >= line->y0) {
    stepy0 = stepy1 = draw_buffer->pixel_span;
  } else {
    stepy0 = stepy1 = -1 * draw_buffer->pixel_span;
  }
  
  if(dx >= dy) {
    stepx0 = 0;
    stepy1 = 0;
    denominator = dx;
    numerator = dx / 2;
    numerator_add = dy;
    line_pixels = dx;
  } else {
    stepx1 = 0;
    stepy0 = 0;
    denominator = dy;
    numerator = dy / 2;
    numerator_add = dx;
    line_pixels = dy;
  }
  
  for(int current_pixel = 0; current_pixel <= line_pixels; ++current_pixel) {
    *pixels = colour.val;
    numerator += numerator_add;
    if(numerator >= denominator) {
      numerator -= denominator;
      pixels += stepx0;
      pixels += stepy0;
    }
    pixels += stepx1;
    pixels += stepy1;
  }
}

///////////////////////////////////
//   TESTING GRAPHICAL FUNCTIONS //
///////////////////////////////////

void snow(struct DrawBuffer *draw_buffer, const union RGBA8888 snow_colour) {
  Uint32 *pixels = draw_buffer->pixels;
  memset(pixels, 0, draw_buffer->pixel_count * sizeof(Uint32));
  for (int i = 0; i < draw_buffer->pixel_count; i++) {
    if (rand() % 2 == 0) {
      *pixels = snow_colour.val;
    }
    pixels++;
  }
}
