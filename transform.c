#include <math.h>

#include "transform.h"

void
set_euler_rotation_coefficients(double *coefficients, struct EulerFix *rotation);

void
euler_rotate(double *coefficients, struct XYZ *from, struct XYZ *to, size_t count);

void
TF_transform_scene_models(
  struct Scene *restrict scene,
  struct Entity *entities,
  struct XYZ *positions,
  struct EulerFix *orientations,
  struct Polyhedron **polyhedrons,
  struct Polyhedron **transformed,
  size_t asize)
{
  double coefficients[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  
  // We loop through the entities in the scene.  
  for(uint8_t i = 0; i < scene->entity_count; ++i) {
    // we fetch the entity
    uint8_t e_index = scene->entity_indexes[i];    
    struct Entity *entity = &entities[e_index];
    
    // Lookup the position, euler fix, polyhedron model and the transform buff.
    struct XYZ *position = &positions[entity->position];
    struct EulerFix *orientation = &orientations[entity->orientation];
    struct Polyhedron *model = &*polyhedrons[entity->model];
    struct Polyhedron *trans = &*transformed[entity->transformed];

    // Carry out the rotation using the EulerFix.
    set_euler_rotation_coefficients(coefficients, orientation);
    euler_rotate(coefficients, model->vertex, trans->vertex, model->vertices);

    // We carry out the translation using the position.
    GP_pp_mut_stream_translate(position, trans->vertex, trans->vertices);
  }
}

/**
 * Prepare rotation coefficients. This saves on some multiplications when the actual
 * rotations are carried out. The `coefficients` pointer expects a buffer of
 * sizeof(double) * 9 to store all the coefficients.
 *
 * Coefficients are in order from 0 to 8; mx1, my1, mz1, mx2, my2, mz2, mx3, my3, mz3.
 */
void
set_euler_rotation_coefficients(double *coefficients, struct EulerFix *rotation)
{
  double cosy, siny, cosp, sinp, cosr, sinr;

  cosy = cos(rotation->yaw);
  siny = sin(rotation->yaw);
  cosp = cos(rotation->pitch);
  sinp = sin(rotation->pitch);
  cosr = cos(rotation->roll);
  sinr = sin(rotation->roll);

  coefficients[0] = siny * sinp * sinr + cosy * cosr;
  coefficients[1] = cosp * sinr;
  coefficients[2] = siny * cosr - cosy * sinp * sinr;
  coefficients[3] = siny * sinp * cosr - cosy * sinr;
  coefficients[4] = cosp * cosr;
  coefficients[5] = -cosy * sinp * cosr - siny * sinr;
  coefficients[6] = -siny * cosp;
  coefficients[7] = sinp;
  coefficients[8] = cosy * cosp;
}

/**
 * Rotate a stream of XYZ vertices using the pre-computed euler coefficients.
 */
void
euler_rotate(double *coefficients, struct XYZ *from, struct XYZ *to, size_t count)
{
  for(size_t i = 0; i < count; ++i) {
    to->x = from->x*coefficients[0] + from->y*coefficients[1] + from->z*coefficients[2];
    to->y = from->x*coefficients[3] + from->y*coefficients[4] + from->z*coefficients[5];
    to->z = from->x*coefficients[6] + from->y*coefficients[7] + from->z*coefficients[8];
    to++;
    from++;
  }
}
