#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "SDL_log.h"

#include "video.h"
#include "draw.h"

struct VideoContext create_empty_video_context() {
  struct VideoContext v_context;

  v_context.window = NULL;
  v_context.renderer = NULL;
  v_context.texture = NULL;
  v_context.pixels_wide = 0;
  v_context.pixels_high = 0;
  v_context.pitch_bytes = 0;

  return v_context;
}

int bring_up_video(struct VideoContext *v_context, enum Resolution resolution) {
  int w, h, f;

  switch (resolution) {
  case W320X240 : w = 320, h = 240, f = 0; break;
  case W640X480 : w = 640, h = 480, f = 0; break;
  case W800X600 : w = 800, h = 600, f = 0; break;
  case W1024X768 : w = 1024, h = 768, f = 0; break;
  case W1600X1200 : w = 1600, h = 1200, f = 0; break;
  case F320X240 : w = 320, h = 240, f = SDL_WINDOW_FULLSCREEN; break;
  case F640X480 : w = 640, h = 480, f = SDL_WINDOW_FULLSCREEN; break;
  case F800X600 : w = 800, h = 600, f = SDL_WINDOW_FULLSCREEN; break;
  case F1024X768 : w = 1024, h = 768, f = SDL_WINDOW_FULLSCREEN; break;
  case F1600X1200 : w = 1600, h = 1200, f = SDL_WINDOW_FULLSCREEN; break;
  default : SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Invalid video resolution given.");
    return 1;
  }

  v_context->window = SDL_CreateWindow(
    "SPEED",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    w,
    h,
    f);

  if (v_context->window == NULL) {
    SDL_LogError(
      SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't create window: %s\n",
      SDL_GetError());
    return -1;
  }

  v_context->renderer = SDL_CreateRenderer(
    v_context->window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (v_context->renderer == NULL) {
    SDL_LogError(
      SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't create renderer: %s\n",
      SDL_GetError());
    return -1;
  }
  
  v_context->texture = SDL_CreateTexture(
    v_context->renderer,
    SDL_PIXELFORMAT_RGBA8888, // 4 bytes per pixel fitting into a Uint32.
    SDL_TEXTUREACCESS_STREAMING,
    w,
    h);

  if (v_context->texture == NULL) {
    SDL_LogError(
      SDL_LOG_CATEGORY_APPLICATION,
      "Couldn't create texture: %s\n",
      SDL_GetError());
    return -1;
  }

  v_context->pixels_wide = w; // Also known as the span.
  v_context->pixels_high = h;
  v_context->pitch_bytes = w * sizeof(Uint32); // How many bytes of memory per line.

  SDL_DisableScreenSaver();
  
  return 0;
}

void destroy_video_context(struct VideoContext *v_context) {
  SDL_DestroyTexture(v_context->texture);
  SDL_DestroyRenderer(v_context->renderer);
  SDL_DestroyWindow(v_context->window);
}

void display(struct VideoContext *v_context, Uint32 *pixels) {
  SDL_UpdateTexture(v_context->texture, NULL, pixels, v_context->pitch_bytes);
  SDL_RenderClear(v_context->renderer);
  SDL_RenderCopy(v_context->renderer, v_context->texture, NULL, NULL);
  SDL_RenderPresent(v_context->renderer);
}
