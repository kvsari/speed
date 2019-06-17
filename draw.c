// Drawing
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "SDL_log.h"

#include "draw.h"

struct DrawBuffer create_empty_draw_buffer() {
  struct DrawBuffer draw_buffer;
  draw_buffer.pixels = NULL;
  draw_buffer.bytes = 0;
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

  draw_buffer->bytes = x * y * sizeof(Uint32);
  draw_buffer->pixel_span = x;
  draw_buffer->pixel_rows = y;

  return 0;
}

void deinitialize_draw_buffer(struct DrawBuffer *draw_buffer) {
  free(draw_buffer->pixels);
  draw_buffer->pixels = NULL;
  draw_buffer->bytes = 0;
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
