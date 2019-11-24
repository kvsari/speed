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

/**
 * Compute the 3D euler rotation into the provided matrix.
 */
void
TF_set_matrix_rot(M33 *matrix, const Euler *rotation);

/**
 * Construct a 4x4 transformation matrix by pasting a 3x3 matrix into the upper left ij.
 * The assumption is that the 4x4 matrix started as an identity matrix and the last row &
 * column are never modified and remain [0, 0, 0, 1](and transposed).
 */
void
TF_dirty_set_upscale_matrix(M44 *restrict mdest, M33 *restrict mpaste);

/**
 * As `TF_dirty_upscale_matrix` but makes sure to leave the last column and row as 0's with
 * the bottom right being 1. Just a few more memory accesses which aren't necessary if the
 * destination matrix never has its last row and column modified from its identity.
 */
void
TF_clean_set_upscale_matrix(M44 *restrict mdest, M33 *restrict mpaste);

/**
 * Construct a translation matrix from a position XYZ. The source matrix must be in
 * identity form (save for the first three columns of the last row) otherwise incorrect
 * results will be had downstream when it's used in matrix operations.
 */
void
TF_dirty_set_translation_matrix(M44 *mdest, C3 *position);

/**
 * As `TF_dirty_set_translation_matrix` but makes sure `mdest` is an identity matrix.
 */
void
TF_clean_set_translation_matrix(M44 *mdest, C3 *position);

/*
void
TF_euler_transform_scene_models(
  struct Scene *restrict scene,
  struct Entity *entities,
  C3 *positions,
  Euler *orientations,
  Polyhedron **polyhedrons,
  Polyhedron **world_transformed,
  size_t asize);
*/

void
TF_matrix_transform_scene_models(
  struct Scene *restrict scene,
  struct Entity *entities,
  C3 *positions,
  Euler *orientations,
  Polyhedron **polyhedrons,
  Polyhedron **world_transformed,
  size_t asize);
  
#endif
