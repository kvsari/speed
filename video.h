/**
 * Video handling. Create/Destroy SDL2 window and renderer
 */
#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "SDL_video.h"
#include "SDL_render.h"
#include "SDL_surface.h"

/**
 * Contains all video handles. To be passed throughout the program as it's needed.
 */
struct VideoContext {
  Uint32       *pixels;
  SDL_Texture  *texture;
  SDL_Renderer *renderer;
  int          pixels_wide;
  int          pixels_high;
  int          pixel_bytes;
  int          pitch_bytes;
  SDL_Window   *window;
};

enum Resolution { W320X240, W640X480, W800X600, W1024X768, W1600X1200,
                  F320X240, F640X480, F800X600, F1024X768, F1600X1200};

/**
 * Convenience function to return a NULL initialized `VideoContext`.
 */
struct VideoContext create_empty_video_context();

/**
 * Setup the window and video card draw context. Also disable any screensaver.
 */
int bring_up_video(struct VideoContext *v_context, enum Resolution resolution);

void destroy_video_context(struct VideoContext *v_context);

void display_01(struct VideoContext *v_context);

void display_02(struct VideoContext *v_context);

#endif
