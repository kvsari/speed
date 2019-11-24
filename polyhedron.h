/**
 * Polyhedron definition and some common polyhedron generators.
 *
 * Polyhedron inner space coordinate system is left-handed.
 */

#ifndef _POLYHEDRON_H_
#define _POLYHEDRON_H_

#include <stdint.h> // We eschew SDL2 Uint32 for our lovable C version (which is the same).

#include "geop.h"

/**
 * The face of a polyhedron.
 */
/*
struct PlanarPolygon {
  struct XYZ *vertex;
  Uint32 vertices;
*/

/**
 * A concave polyhedron.
 */
typedef struct Polyhedron {
  C3 *vertex;
  int32_t vertices;
} Polyhedron;

/**
 * Free memory allocated for the `Polyhedron`.
 */
void
PH_free_polyhedron(Polyhedron **polyhedron);

/**
 * Make a deep copy of an existing `Polyhedron`. Mainly to allocate a same size memory
 * chunk with which to store the translated form of a model.
 */
Polyhedron *
PH_clone_polyhedron(Polyhedron *polyhedron);

/**
 * Return a cube with the center oriented at (0, 0, 0). This function allocates memory
 * for the returned `Polyhedron` struct describing the cube.
 */
Polyhedron *
PH_construct_cube(const double side_length);

#endif
