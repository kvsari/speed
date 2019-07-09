/**
 * SDL input handling.
 */
#ifndef _INPUT_H_
#define _INPUT_H_

//#include "SDL_events.h"
#include "SDL_scancode.h"

/**
 * A set of binary masks for keeping all keypress state in a `Uint32`.
 */
#define M_I_TURN_LEFT       0x00000001
#define M_I_TURN_RIGHT      0x00000002
#define M_I_LEFT_AIRBRAKE   0x00000004
#define M_I_RIGHT_AIRBRAKE  0x00000008
#define M_I_NOSE_UP         0x00000010
#define M_I_NOSE_DOWN       0x00000020
#define M_I_QUIT            0x80000000

/**
 * Reverse masks for turning that specific bit off.
 */
#define R_I_TURN_LEFT       0xFFFFFFFE
#define R_I_TURN_RIGHT      0xFFFFFFFD
#define R_I_LEFT_AIRBRAKE   0xFFFFFFFB
#define R_I_RIGHT_AIRBRAKE  0xFFFFFFF7
#define R_I_NOSE_UP         0xFFFFFFEF
#define R_I_NOSE_DOWN       0xFFFFFFDF
#define R_I_QUIT            0x7FFFFFFF

/**
 * A linear list of scancodes. Will have to loop through and check each slot.
 *
 * TODO: Implement a hash table.
 */
struct KeyboardMappings {
  SDL_Scancode turn_left;
  SDL_Scancode turn_right;
  SDL_Scancode left_airbrake;
  SDL_Scancode right_airbrake;
  SDL_Scancode nose_up;
  SDL_Scancode nose_down;
  SDL_Scancode quit;
};

struct KeyboardMappings
default_keyboard_mappings();

void
keypress(Uint32 *input_state, const struct KeyboardMappings *k_mappings,
         const SDL_Scancode scancode);

void
keyrelease(Uint32 *input_state, const struct KeyboardMappings *k_mappings,
           const SDL_Scancode scancode);

/**
 * System function: process_input_state
 *
 * Makes sense of the bitfielded `input_state` and makes the necessary changes to the
 * player movement struct.
 *
 * TODO: Add the actual player movement struct.
 */
int
process_input_state(const Uint32 input_state);

#endif
