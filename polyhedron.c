#include <stdlib.h>
#include <string.h>

#include "polyhedron.h"
#include "geop.h"

void
PH_free_polyhedron(struct Polyhedron **polyhedron)
{
  free((*polyhedron)->vertex);
  (*polyhedron)->vertex = NULL;
  (*polyhedron)->vertices = 0;
  free(*polyhedron);
  *polyhedron = NULL;
}

struct Polyhedron *
PH_clone_polyhedron(struct Polyhedron *polyhedron)
{
  struct Polyhedron *clone = malloc(sizeof(struct Polyhedron));
  size_t size = sizeof(struct XYZ) * polyhedron->vertices;
  struct XYZ *vertex = malloc(size);
  clone->vertices = polyhedron->vertices;
  clone->vertex = memcpy(vertex, polyhedron->vertex, size);

  return clone;
}

struct Polyhedron *
PH_construct_cube(const double side_length)
{
  float h_len = side_length / 2;
  float h_neg = h_len * -1;
  struct XYZ *vertex = malloc(sizeof(struct XYZ) * 8);
  struct XYZ *v_inc = vertex;
  
  *v_inc++ = GP_construct_xyz(h_len, h_len, h_neg);
  *v_inc++ = GP_construct_xyz(h_len, h_neg, h_neg);
  *v_inc++ = GP_construct_xyz(h_neg, h_neg, h_neg);
  *v_inc++ = GP_construct_xyz(h_neg, h_len, h_neg);
  *v_inc++ = GP_construct_xyz(h_len, h_len, h_len);
  *v_inc++ = GP_construct_xyz(h_len, h_neg, h_len);
  *v_inc++ = GP_construct_xyz(h_neg, h_neg, h_len);
  *v_inc++ = GP_construct_xyz(h_neg, h_len, h_len);

  struct Polyhedron *polyhedron = malloc(sizeof(struct Polyhedron));

  polyhedron->vertex = vertex;
  polyhedron->vertices = 8;
  
  return polyhedron;
}
