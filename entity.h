#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <stdint.h>

#include "polyhedron.h"

/**
 * A set of binary masks for whether a component is flagged active for the `Entity`.
 */
#define M_C_PLAYER_INPUT       0x00000001
#define M_C_POSITION           0x00000002
#define M_C_ORIENTATION        0x00000004
#define M_C_MODEL              0x00000008
/*
#define M_NOSE_UP         0x00000010
#define M_NOSE_DOWN       0x00000020
#define M_QUIT            0x80000000
*/

/**
 * Reverse masks for turning that specific bit off.
 */
#define R_C_PLAYER_INPUT       0xFFFFFFFE
#define R_C_POSITION           0xFFFFFFFD
#define R_C_ORIENTATION        0xFFFFFFFB
#define R_C_MODEL              0xFFFFFFF7
/*
#define R_NOSE_UP         0xFFFFFFEF
#define R_NOSE_DOWN       0xFFFFFFDF
#define R_QUIT            0x7FFFFFFF
*/

/**
 * Entity struct. To be used in my naive, beginner, ECS.
 *
 * Component indexes are `Uint8` values. Whether a component for the entity exists or not
 * is specified in the `components` flag. Starting from leftmost
 *
 * An `id` of 0 is a sentinel value indicating that the `Entity` uninitialized.
 */
struct Entity {
  uint32_t id;
  uint32_t components;

  /* Component indexes. Ordered from the leftmost of the `components` flag. */
  uint8_t player_input; // Future proof multiple inputs in case of network play inspiration.
  uint8_t position;
  uint8_t orientation;
  uint8_t model;
  uint8_t transformed;
};

void
register_player_input(struct Entity *entity, uint8_t index);

void
deregister_player_input(struct Entity *entity);

void
register_position(struct Entity *entity, uint8_t index);

void
deregister_position(struct Entity *entity);

void
register_model(struct Entity *entity, uint8_t i_model, uint8_t i_transformed);

void
deregister_model(struct Entity *entity);

void
register_orientation(struct Entity *entity, uint8_t index);

void
deregister_orientation(struct Entity *entity);


#endif
