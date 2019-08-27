/**
 * 3D world for all entities.
 */

#ifndef _WORLD_H_
#define _WORLD_H_

#include <stdint.h>

/**
 * World state.
struct World {

}
*/

/**
 * A chunk of the world centered on a designated entity. This chunk is intended to be made
 * visible by perspective projection. This struct is meant to be re-used.
 *
 * Contains an array of entity indexes which are within the scene.
 */
struct Scene {
  uint8_t *entity_indexes;
  uint8_t entity_count;
};

struct Scene *
malloc_scene(const uint8_t max_entities);

void
free_scene(struct Scene **scene);

#endif
