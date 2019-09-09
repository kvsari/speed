#include "entity.h"

void
register_player_input(struct Entity *entity, uint8_t index) {
  entity->components |= M_C_PLAYER_INPUT;
  entity->player_input = index;
}

void
deregister_player_input(struct Entity *entity) {
  entity->components &= R_C_PLAYER_INPUT;
}

void
register_position(struct Entity *entity, uint8_t index) {
  entity->components |= M_C_POSITION;
  entity->position = index;
}

void
deregister_position(struct Entity *entity) {
  entity->components &= R_C_POSITION;
}

void
register_model(struct Entity *entity, uint8_t i_model, uint8_t i_translated) {
  entity->components |= M_C_MODEL;
  entity->model = i_model;
  entity->translated = i_translated;
}

void
deregister_model(struct Entity *entity) {
  entity->components &= R_C_MODEL;
}

void
register_orientation(struct Entity *entity, uint8_t index) {
  entity->components |= M_C_ORIENTATION;
  entity->orientation = index;
}

void
derigister_orientation(struct Entity *entity) {
  entity->components &= R_C_ORIENTATION;
}
