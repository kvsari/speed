/**
 * 3D Object (polyhedron) transformation. Done on entities that have models to transform.
 */

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <stdlib.h>

#include "geop.h"
#include "world.h"
#include "entity.h"
#include "polyhedron.h"

void
transform_scene_models(
  struct Scene *restrict scene,
  struct Entity *entities,
  struct XYZ *positions,
  struct EulerFix *orientations,
  struct Polyhedron **polyhedrons,
  struct Polyhedron **transformed,
  size_t asize);
  
#endif
