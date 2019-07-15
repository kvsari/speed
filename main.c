/**
 * Speed
 */
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "SDL.h"
#include "SDL_log.h"
#include "SDL_version.h"
#include "SDL_events.h"

#include "video.h"
#include "draw.h"
#include "input.h"

void
sdl_version_log()
{
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

  // Event subsystem is implicitly initialized along with the video subsystem.
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

int
main(int argc, char **argv)
{
  sdl_version_log();
  srand(time(NULL));

  /////////////////////////////////////////////
  //
  // INITIALIZATION
  //
  /////////////////////////////////////////////

  // Setup video
  struct VideoContext v_context = create_empty_video_context();
  if (initialize_sdl() != 0) { return 1; }
  if (bring_up_video(&v_context, W320X240) != 0) { return 1; }
  //if (bring_up_video(&v_context, F640X480) != 0) { return 1; }
  //if (bring_up_video(&v_context, F800X600) != 0) { return 1; }
  //if (bring_up_video(&v_context, F1024X768) != 0) { return 1; }

  // Setup draw buffer to same size of the video surface.
  struct DrawBuffer draw_buf = create_empty_draw_buffer();
  size_t x = v_context.pixels_wide;
  size_t y = v_context.pixels_high;
  if (initialize_draw_buffer(&draw_buf, x, y) != 0) { return 1; }
  
  union ABGR8888 c_red;
  c_red.abgr[0] = 255;
  c_red.abgr[1] = 0;
  c_red.abgr[2] = 0;
  c_red.abgr[3] = 255;

  union ABGR8888 c_green;
  c_green.abgr[0] = 255;
  c_green.abgr[1] = 0;
  c_green.abgr[2] = 255;
  c_green.abgr[3] = 0;

  union ABGR8888 c_blue;
  c_blue.abgr[0] = 255;
  c_blue.abgr[1] = 255;
  c_blue.abgr[2] = 0;
  c_blue.abgr[3] = 0;

  /*
  for (int i = 0; i < 180; ++i) {
    snow(&draw_buf, colour);
    display(&v_context, draw_buf.pixels);
  }
  */

  /*
  struct Line line;
  line.x0 = 30;
  line.y0 = 30;
  line.x1 = 20;
  line.y1 = 20;
  plot_line(&draw_buf, &line, c_red);
  display(&v_context, draw_buf.pixels);
  SDL_Delay(5000);
  */

  /*
  struct Rectangle rectangle;
  rectangle.x = 50;
  rectangle.y = 50;
  rectangle.w = 100;
  rectangle.h = 100;
  plot_rectangle(&draw_buf, &rectangle, c_blue.val);
  display(&v_context, draw_buf.pixels);
  SDL_Delay(5000);
  */

  /*
  struct Line line;
  struct Rectangle rectangle;
  rectangle.x = 80;
  rectangle.y = 50;
  rectangle.w = 150;
  rectangle.h = 150;

  for (int i = 0; i < 300; ++i) {
    line.x0 = rand() % draw_buf.pixel_span;
    line.y0 = rand() % draw_buf.pixel_rows;
    line.x1 = rand() % draw_buf.pixel_span;
    line.y1 = rand() % draw_buf.pixel_rows;

    memset(draw_buf.pixels, 0, draw_buf.pixel_count * sizeof(Uint32));
    plot_line(&draw_buf, &line, c_red.val);
    plot_rectangle(&draw_buf, &rectangle, c_blue.val);
    if (clip_line(&draw_buf, &rectangle, &line) == 0) {
      plot_line(&draw_buf, &line, c_green.val);
    }
    display(&v_context, draw_buf.pixels);
  }
  */

  /*
  struct Line line;
  struct Rectangle rectangle;
  rectangle.x = 80;
  rectangle.y = 50;
  rectangle.w = 150;
  rectangle.h = 150;

  line.x0 = 10;
  line.y0 = 10;
  line.x1 = 200;
  line.y1 = 200;
  
  plot_line(&draw_buf, &line, c_red.val);
  plot_rectangle(&draw_buf, &rectangle, c_blue.val);
  if (clip_line(&draw_buf, &rectangle, &line) == 0) {
    plot_line(&draw_buf, &line, c_green.val);
  }
  display(&v_context, draw_buf.pixels);
  SDL_Delay(5000);
  */

  /*
  plasma_01(&draw_buf);
  display(&v_context, draw_buf.pixels);
  SDL_Delay(5000);
  */

  /*
  for (int i = 0; i < 300; ++i) {
    plasma_02(&draw_buf, i);
    display(&v_context, draw_buf.pixels);
  }
  */

  // Test plasma
  int i = 0;

  struct KeyboardMappings k_mappings = default_keyboard_mappings();
  Uint32 input_state = 0;

  ////////////////////////////////////////////
  //
  //  GAME LOOP
  //
  ////////////////////////////////////////////

  int game_on = 1;
  while(game_on) {

    // Get player events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT : game_on = 0; break;
      case SDL_KEYDOWN :
        keypress(&input_state, &k_mappings, event.key.keysym.scancode);
        break;
      case SDL_KEYUP :
        keyrelease(&input_state, &k_mappings, event.key.keysym.scancode);
        break;
      }
    }

    // Process game state
    game_on = process_input_state(input_state);

    // Test plasma
    plasma_02(&draw_buf, i);
    i++;

    // Render
    display(&v_context, draw_buf.pixels);
  }

  destroy_video_context(&v_context);
  deinitialize_draw_buffer(&draw_buf);
  SDL_Quit();
  return 0;
}
