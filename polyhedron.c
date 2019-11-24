#include <stdlib.h>
#include <string.h>

#include "polyhedron.h"

void
PH_free_polyhedron(Polyhedron **polyhedron)
{
  free((*polyhedron)->vertex);
  (*polyhedron)->vertex = NULL;
  (*polyhedron)->vertices = 0;
  free(*polyhedron);
  *polyhedron = NULL;
}

Polyhedron *
PH_clone_polyhedron(Polyhedron *polyhedron)
{
  Polyhedron *clone = malloc(sizeof(struct Polyhedron));
  size_t size = sizeof(struct Matrix_1x3) * polyhedron->vertices;
  C3 *vertex = malloc(size);
  clone->vertices = polyhedron->vertices;
  clone->vertex = memcpy(vertex, polyhedron->vertex, size);

  return clone;
}

Polyhedron *
PH_construct_cube(const double side_length)
{
  float h_len = side_length / 2;
  float h_neg = h_len * -1;
  C3 *vertex = malloc(sizeof(struct Matrix_1x3) * 8);
  C3 *v_inc = vertex;
  
  *v_inc++ = GP_new_C3(h_len, h_len, h_neg);
  *v_inc++ = GP_new_C3(h_len, h_neg, h_neg);
  *v_inc++ = GP_new_C3(h_neg, h_neg, h_neg);
  *v_inc++ = GP_new_C3(h_neg, h_len, h_neg);
  *v_inc++ = GP_new_C3(h_len, h_len, h_len);
  *v_inc++ = GP_new_C3(h_len, h_neg, h_len);
  *v_inc++ = GP_new_C3(h_neg, h_neg, h_len);
  *v_inc++ = GP_new_C3(h_neg, h_len, h_len);

  Polyhedron *polyhedron = malloc(sizeof(struct Polyhedron));

  polyhedron->vertex = vertex;
  polyhedron->vertices = 8;
  
  return polyhedron;
}
