/**
 * SYSTEM
 *
 * Camera system. It receives a scene of possibly visible entities, the entity index it is
 * attached to (or follows) and the draw buffer. It will make any adjustments to its
 * position (if following an entity and the entity moved for example). It will then carry
 * out a clipped perspective transform on the scene. Then it will render the transform onto
 * the draw buffer.
 */

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <stdint.h>

#include "draw.h"
#include "entity.h"
#include "world.h"
#include "geop.h"

/**
 * Contains state of the camera system.
 *
 * TODO: Add follow/attach parameters (such as rubber banding).
 */
struct Camera {
  uint8_t player_entity;
  struct XYZ position;
};

//void
//move_camera(struct Camera *camera, struct Entity

/**
 * Draw the provided `Scene` using the `Camera` into the `DrawBuffer`. This draw
 * constitutes one frame.
 */
void
draw_picture(
  struct DrawBuffer *draw_buf,
  struct Camera *camera,
  struct Scene *scene,
  struct Entity *entities,
  struct XYZ *positions,
  struct Polyhedron **polyhedrons,
  size_t asize);

#endif
