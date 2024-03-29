#include "input.h"

struct KeyboardMappings
IN_default_keyboard_mappings()
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
IN_keypress(Uint32 *input_state, const struct KeyboardMappings *k_mappings,
            const SDL_Scancode scancode)
{
  if (scancode == k_mappings->turn_left) {
    *input_state |= M_I_TURN_LEFT;
  }
  
  if (scancode == k_mappings->turn_right) {
    *input_state |= M_I_TURN_RIGHT;
  }
  
  if (scancode == k_mappings->quit) {
    *input_state |= M_I_QUIT;
  }
}

void
IN_keyrelease(Uint32 *input_state, const struct KeyboardMappings *k_mappings,
              const SDL_Scancode scancode)
{
  if (scancode == k_mappings->turn_left) {
    *input_state &= R_I_TURN_LEFT;  
  }
  
  if (scancode == k_mappings->turn_right) {
    *input_state &= R_I_TURN_RIGHT;
  }
  
  //if (scancode == k_mappings.quit) {
  // }
}

int
IN_process_input_state(const Uint32 input_state)
{
  if (input_state & M_I_QUIT) {
    return 0;
  }

  return 1;
}
