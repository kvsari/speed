#include "video.h"

void destroy_video_context(struct VideoContext *v_context) {
  SDL_DestroyRenderer(v_context->renderer);
  SDL_DestroyWindow(v_context->window);
}

int bring_up_video(struct VideoContext *v_context, enum Resolution resolution) {
  int w, h, f;

  switch (resolution) {
  case W320X240 : w = 320, h = 240, f = 0; break;
  default : SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Invalid video resolution given.");
    return 1;
  }
  
  SDL_DisableScreenSaver();
  
  if(SDL_CreateWindowAndRenderer(w, h, f, &v_context->window, &v_context->renderer) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s",
                 SDL_GetError());
    return -1;
  }

  return 0;
}
