#include <stdlib.h>

#include "world.h"

struct Scene *
WD_malloc_scene(const uint8_t max_entities)
{
  struct Scene *scene = malloc(sizeof(struct Scene));
  
  scene->entity_indexes = malloc(sizeof(uint8_t) * max_entities);
  scene->entity_count = 0;
  
  return scene;
}

void
WD_free_scene(struct Scene **scene)
{
  free((*scene)->entity_indexes);
  free(*scene);
  *scene = NULL;
}
