/**
 * Video handling. Create/Destroy SDL2 window and renderer
 */
#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "SDL_log.h"
#include "SDL_video.h"
#include "SDL_render.h"

/**
 * Contains all video handles. To be passed throughout the program as its needed.
 */
struct VideoContext {
  SDL_Window   *window;
  SDL_Renderer *renderer;
};

enum Resolution { W320X240, W640X480, W800X600, W1024X768, W1600X1200,
                  F320X240, F640X480, F800X600, F1024X768, F1600X1200};

/**
 * Setup the window and video card draw context. Also disable any screensaver.
 */
int bring_up_video(struct VideoContext *v_context, enum Resolution resolution);

void destroy_video_context(struct VideoContext *v_context);

#endif
