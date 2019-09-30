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
struct VideoContext
VD_create_empty_video_context();

/**
 * Setup the window and video card draw context. Also disable any screensaver.
 */
int
VD_bring_up_video(struct VideoContext *v_context, const enum Resolution resolution);

void
VD_destroy_video_context(struct VideoContext *v_context);

/**
 * Transfer whatever is pointed at by `pixels` into the video device. The block of memory
 * `pixels` must be of the same width and height as the resolution that was set for the
 * `VideoContext`. If it's not the exact size undefined behaviour will happen.
 */
void
VD_display(struct VideoContext *v_context, Uint32 *pixels);

#endif
