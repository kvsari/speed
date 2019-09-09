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
struct Polyhedron {
  struct XYZ *vertex;
  int32_t vertices;
};

/**
 * Free memory allocated for the `Polyhedron`.
 */
void
free_polyhedron(struct Polyhedron **polyhedron);

/**
 * Make a deep copy of an existing `Polyhedron`. Mainly to allocate a same size memory
 * chunk with which to store the translated form of a model.
 */
struct Polyhedron *
clone_polyhedron(struct Polyhedron *polyhedron);

/**
 * Return a cube with the center oriented at (0, 0, 0). This function allocates memory
 * for the returned `Polyhedron` struct describing the cube.
 */
struct Polyhedron *
construct_cube(const double side_length);

#endif
