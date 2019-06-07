/**
 * Speed
 */
#include <stdlib.h>
#include <stdio.h>

#include "SDL.h"
#include "SDL_log.h"
#include "SDL_version.h"

#include "video.h"
#include "draw.h"

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
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL2: %s\n", SDL_GetError());
    return -1;
  }
  
  if (SDL_InitSubSystem(SDL_INIT_TIMER) != 0) {
    SDL_LogError(
      SDL_LOG_CATEGORY_ERROR,
      "Unable to initialize SDL2 timing system: %sn",
      SDL_GetError());
    return -1;
  }
  
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
    SDL_LogError(
      SDL_LOG_CATEGORY_VIDEO,
      "Failed to initialse SDL2 video system: %s\n",
      SDL_GetError());
    return -1;
  }

  return 0;
}

/*
// Various printouts for debug purposes. Kept here to not clutter main.
void printouts() {
  int rgba8888_size = sizeof(union RGBA8888);
  printf("RGBA8888 size: %d\n", rgba8888_size);

  // Holy crap! I need to refresh my memory on how pointers work! Been too long.
  unsigned int numbers[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  unsigned int *n_ptr = numbers;
  printf("ADDRESS => numbers[0]: %x, n_ptr: %x, &n_ptr: %x\n", &numbers[0], n_ptr, &n_ptr);
  printf("VALUE   => numbers[0]: %d, *n_ptr: %d\n", numbers[0], *n_ptr);
  n_ptr++;
  printf("ADDRESS => numbers[1]: %x, n_ptr: %x, &n_ptr: %x\n", &numbers[1], n_ptr, &n_ptr);
  printf("VALUE   => numbers[1]: %d, *n_ptr: %d\n", numbers[1], *n_ptr);
  n_ptr += 1;
  printf("ADDRESS => numbers[1]: %x, n_ptr: %x, &n_ptr: %x\n", &numbers[1], n_ptr, &n_ptr);
  printf("VALUE   => numbers[1]: %d, *n_ptr: %d\n", numbers[1], *n_ptr);
  n_ptr += 4;
  printf("ADDRESS => numbers[6]: %x, n_ptr: %x, &n_ptr: %x\n", &numbers[6], n_ptr, &n_ptr);
  printf("VALUE   => numbers[6]: %d, *n_ptr: %d\n", numbers[6], *n_ptr);  
}
*/

int main(int argc, char **argv) {
  sdl_version_log();

  struct VideoContext v_context = create_empty_video_context();
  
  if (initialize_sdl() != 0) { return 1; }
  if (bring_up_video(&v_context, W320X240) != 0) { return 1; }

  display_02(&v_context);
  SDL_Delay(5000);

  //printouts();

  destroy_video_context(&v_context);
  SDL_Quit();
  return 0;
}
