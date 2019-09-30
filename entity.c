#include "entity.h"

void
EN_register_player_input(struct Entity *entity, uint8_t index)
{
  entity->components |= M_C_PLAYER_INPUT;
  entity->player_input = index;
}

void
EN_deregister_player_input(struct Entity *entity)
{
  entity->components &= R_C_PLAYER_INPUT;
}

void
EN_register_position(struct Entity *entity, uint8_t index)
{
  entity->components |= M_C_POSITION;
  entity->position = index;
}

void
EN_deregister_position(struct Entity *entity)
{
  entity->components &= R_C_POSITION;
}

void
EN_register_model(struct Entity *entity, uint8_t i_model, uint8_t i_transformed)
{
  entity->components |= M_C_MODEL;
  entity->model = i_model;
  entity->transformed = i_transformed;
}

void
EN_deregister_model(struct Entity *entity)
{
  entity->components &= R_C_MODEL;
}

void
EN_register_orientation(struct Entity *entity, uint8_t index)
{
  entity->components |= M_C_ORIENTATION;
  entity->orientation = index;
}

void
EN_derigister_orientation(struct Entity *entity)
{
  entity->components &= R_C_ORIENTATION;
}
