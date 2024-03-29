/**
 * Speed
 */
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "SDL.h"
#include "SDL_log.h"
#include "SDL_version.h"
#include "SDL_events.h"

#include "video.h"
#include "draw.h"
#include "input.h"
#include "polyhedron.h"
#include "entity.h"
#include "camera.h"
#include "world.h"
#include "transform.h"

const size_t ASIZE = 200;

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
  struct VideoContext v_context = VD_create_empty_video_context();
  if (initialize_sdl() != 0) { return 1; }
  if (VD_bring_up_video(&v_context, W320X240) != 0) { return 1; }
  //if (bring_up_video(&v_context, F640X480) != 0) { return 1; }
  //if (bring_up_video(&v_context, F800X600) != 0) { return 1; }
  //if (bring_up_video(&v_context, F1024X768) != 0) { return 1; }

  // Setup draw buffer to same size of the video surface.
  struct DrawBuffer draw_buf = DR_create_empty_draw_buffer();
  size_t x = v_context.pixels_wide;
  size_t y = v_context.pixels_high;
  if (DR_initialize_draw_buffer(&draw_buf, x, y) != 0) { return 1; }

  // Prepare our rendering states
  Camera camera = CM_default_camera();
  camera.position.c[Z] = -100;
  struct Scene *scene = WD_malloc_scene(ASIZE);

  /*
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
  */  

  ////////////////////////////////////////////
  //
  //  COMPONENT ARRAYS
  //
  ////////////////////////////////////////////

  // Positions in world space
  C3 positions[ASIZE];
  positions[0].c[X] = 0;
  positions[0].c[Y] = 0;
  positions[0].c[Z] = 0;

  // Euler orientations in world space
  Euler orientations[ASIZE];
  orientations[0].yaw   = 0.0;
  orientations[0].pitch = 0.0;
  orientations[0].roll  = 0.0;

  // Use flyweight pattern to re-use the same polyhedrons. We'd better NULL for safety.
  Polyhedron *polyhedrons[ASIZE];
  for(int i = 0; i < ASIZE; ++i) {
    polyhedrons[i] = NULL;
  }
  // Load in some basic shapes
  polyhedrons[0] = PH_construct_cube(1);

  // Transformed polyhedrons (applied position and orientations in world space).
  Polyhedron *world_transformed[ASIZE];
  for(int i = 0; i < ASIZE; ++i) {
    world_transformed[i] = NULL;
  }
  // Prepare our clone for the entity. There must be as many clones (of the right type) for
  // as many entities we have that have models (polyhedrons).
  world_transformed[0] = PH_clone_polyhedron(polyhedrons[0]);

  // Final camera transformed polyhedrons.
  Polyhedron *camera_transformed[ASIZE];
  for(int i = 0; i < ASIZE; ++i) {
    camera_transformed[i] = NULL;
  }
  camera_transformed[0] = PH_clone_polyhedron(polyhedrons[0]);
  
  // The first input is mapped to the local machine. Second input if we ever get to it
  // will be the remote player. Just future proofing and maintaining symmetry.
  struct KeyboardMappings k_mappings = IN_default_keyboard_mappings();
  uint32_t input_states[2] = { 0, 0 };

  ////////////////////////////////////////////
  //
  //  ENTITY SETUP
  //
  ////////////////////////////////////////////
  
  // Once components are loaded into memory, we create entities which are composed of
  // components. These entities will populate our world.

  // Create our entities and zero the id. 
  struct Entity entities[ASIZE];
  for(int i = 0; i < ASIZE; ++i) {
    entities[i].id = 0;
  }

  // Setup a simple entity for our cube
  entities[0].id = 1;
  EN_register_position(&entities[0], 0);    // positions[0]
  EN_register_model(&entities[0], 0, 0);    // polyhedrons[0] & translations[0]
  camera.player_entity = 0; // Tell the camera which entity is the player.

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
        IN_keypress(&input_states[0], &k_mappings, event.key.keysym.scancode);
        break;
      case SDL_KEYUP :
        IN_keyrelease(&input_states[0], &k_mappings, event.key.keysym.scancode);
        break;
      }
    }

    // Process game state
    game_on = IN_process_input_state(input_states[0]);

    // Update the models on the scene...
    TF_matrix_transform_scene_models(
      scene, entities, positions, orientations, polyhedrons, world_transformed, ASIZE);
    
    // Draw what the camera sees.
    CM_draw_picture(
      &draw_buf,
      &camera,
      scene,
      entities,
      //positions,
      world_transformed,
      camera_transformed,
      ASIZE);

    // Render
    VD_display(&v_context, draw_buf.pixels);
  }

  ////////////////////////////////////////////
  //
  //  SHUTDOWN
  //
  ////////////////////////////////////////////

  // Free up polyhdrons
  for (int i = 0; i < ASIZE; ++i) {
    if(polyhedrons[i] != NULL) {
      PH_free_polyhedron(&polyhedrons[i]);
    }
  }
  
  VD_destroy_video_context(&v_context);
  DR_deinitialize_draw_buffer(&draw_buf);
  WD_free_scene(&scene);
  SDL_Quit();
  return 0;
}
