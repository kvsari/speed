/**
 * Speed
 */
#include <stdlib.h>
#include <stdio.h>

#include "SDL.h"
#include "SDL_log.h"
#include "SDL_version.h"

#include "video.h"

void sdl_version_log() {
  SDL_version c, l;  

  SDL_VERSION(&c);
  SDL_GetVersion(&l);

  if ((c.major != l.major) || (c.minor != l.minor) || (c.patch != l.patch)) {
    SDL_Log("SPEED compiled against SDL2 %d.%d.%d linking against %d.%d.%d.\n",
            c.major, c.minor, c.patch, l.major, l.minor, l.patch);
  }
}

int initialize_sdl() {
  if (SDL_Init(0) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL2: %s", SDL_GetError());
    return -1;
  }
  
  if (SDL_InitSubSystem(SDL_INIT_TIMER) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                 "Unable to initialize SDL2 timing system: %s",
                 SDL_GetError());
    return -1;
  }
  
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                 "Failed to initialse SDL2 video system: %s",
                 SDL_GetError());
    return -1;
  }

  return 0;
}

int main(int argc, char **argv) {
  sdl_version_log();

  struct VideoContext v_context;
  
  if (initialize_sdl() != 0) { return 1; }
  if (bring_up_video(&v_context, W320X240) != 0) { return 1; }

  SDL_Delay(5000);

  destroy_video_context(&v_context);
  SDL_Quit();
  return 0;
}
