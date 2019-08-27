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

#endif
