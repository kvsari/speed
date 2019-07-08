#include "input.h"

struct KeyboardMappings
default_keyboard_mappings()
{
  struct KeyboardMappings km;

  km.turn_left = SDL_SCANCODE_LEFT;
  km.turn_right = SDL_SCANCODE_RIGHT;
  km.left_airbrake = SDL_SCANCODE_A;
  km.right_airbrake = SDL_SCANCODE_D;
  km.nose_up = SDL_SCANCODE_UP;
  km.nose_down = SDL_SCANCODE_DOWN;
  km.quit = SDL_SCANCODE_Q;

  return km;
}

void
keypress(Uint32 *input_state, const struct KeyboardMappings *k_mappings,
         const SDL_Scancode scancode)
{
  if (scancode == k_mappings->turn_left) {
    *input_state |= M_TURN_LEFT;
  }
  
  if (scancode == k_mappings->turn_right) {
    *input_state |= M_TURN_RIGHT;
  }
  
  if (scancode == k_mappings->quit) {
    *input_state |= M_QUIT;
  }
}

void
keyrelease(Uint32 *input_state, const struct KeyboardMappings *k_mappings,
           const SDL_Scancode scancode)
{
  if (scancode == k_mappings->turn_left) {
    *input_state &= R_TURN_LEFT;  
  }
  
  if (scancode == k_mappings->turn_right) {
    *input_state &= R_TURN_RIGHT;
  }
  
  //if (scancode == k_mappings.quit) {
  // }
}

int
process_input_state(const Uint32 input_state)
{
  if (input_state & M_QUIT) {
    return 0;
  }

  return 1;
}
