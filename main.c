// Speed
#include <stdlib.h>
#include <stdio.h>

#include "SDL.h"
#include "SDL_log.h"
#include "SDL_version.h"

void sdl_version_print() {
  SDL_version c, l;  

  SDL_VERSION(&c);
  SDL_GetVersion(&l);

  if ((c.major != l.major) || (c.minor != l.minor) || (c.patch != l.patch)) {
    printf("SPEED compiled against SDL2 %d.%d.%d linking against %d.%d.%d.\n",
           c.major, c.minor, c.patch, l.major, l.minor, l.patch);
  }
}

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_TIMER) != 0) {
    printf("Unable to initialize SDL2 timing system: %s", SDL_GetError());
    return 1;
  }

  sdl_version_print();
  

  SDL_Quit();
  return 0;
}
