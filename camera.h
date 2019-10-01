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
#include "polyhedron.h"

/**
 * Contains state of the camera system.
 *
 * Camera orientation is handled with three unit vectors. Guassian elimination needs to be
 * applied to find the rotation matrix.
 *
 * TODO: Add follow/attach parameters (such as rubber banding).
 */
struct Camera {
  uint8_t player_entity;
  struct XYZ position;
  struct XYZ t, s, n;
};

/**
 * Create a new camera at origin with default starting t, s, n.
 */
struct Camera
CM_create_camera();

/**
 * Carry out normalization and orthoganalization of the t, s, n vectors of the camera if
 * falling outside the error margin.
 */
void
CM_mut_correct_tsn(struct Camera *camera, double margin);

/**
 * Draw the provided `Scene` using the `Camera` into the `DrawBuffer`. This draw
 * constitutes one frame.
 */
void
CM_draw_picture(
  struct DrawBuffer *draw_buf,
  struct Camera *camera,
  struct Scene *scene,
  struct Entity *entities,
  struct XYZ *positions,
  struct Polyhedron **transformed,
  size_t asize);

#endif
