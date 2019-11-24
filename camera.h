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
 * applied to find the rotation matrix. The `n` vector is the direction the camera is at
 * with the `t` and `s` vectors being the screen orientations on x and y.
 *
 * TODO: Add follow/attach parameters (such as rubber banding).
 */
typedef struct WorldToScreen {
  uint8_t player_entity;
  C3 position;
  C3 t, s, n;
} Camera;

/**
 * Create a new camera at origin with default starting t, s, n.
 */
Camera
CM_default_camera();

/**
 * Carry out normalization and orthoganalization of the t, s, n vectors of the camera if
 * falling outside the error margin.
 */
void
CM_mut_correct_tsn(Camera *camera, double margin);

/**
 * Draw the provided `Scene` using the `Camera` into the `DrawBuffer`. This draw
 * constitutes one frame.
 */
void
CM_draw_picture(
  struct DrawBuffer *draw_buf,
  Camera *camera,
  struct Scene *scene,
  struct Entity *entities,
  //struct XYZ *positions,
  Polyhedron **world_transformed,
  Polyhedron **camera_transformed,
  size_t asize);

#endif
