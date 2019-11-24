#include <math.h>

#include "transform.h"

/*
void
set_euler_rotation_coefficients(double *coefficients, struct EulerFix *rotation);

void
euler_rotate(double *coefficients, C3 *from, C3 *to, size_t count);
*/

void
set_yaw_rot_matrix(M33 *matrix, double yaw);

void
set_pitch_rot_matrix(M33 *matrix, double pitch);

void
set_roll_rot_matrix(M33 *matrix, double roll);

/*
void
TF_euler_transform_scene_models(
  struct Scene *restrict scene,
  struct Entity *entities,
  struct XYZ *positions,
  struct EulerFix *orientations,
  struct Polyhedron **polyhedrons,
  struct Polyhedron **world_transformed,
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
    struct Polyhedron *trans = &*world_transformed[entity->transformed];

    // Carry out the rotation using the EulerFix.
    set_euler_rotation_coefficients(coefficients, orientation);
    euler_rotate(coefficients, model->vertex, trans->vertex, model->vertices);

    // We carry out the translation using the position.
    GP_pp_mut_stream_translate(trans->vertex, position, trans->vertices);
  }
}
*/

void
TF_matrix_transform_scene_models(
  struct Scene *restrict scene,
  struct Entity *entities,
  C3 *positions,
  Euler *orientations,
  Polyhedron **polyhedrons,
  Polyhedron **world_transformed,
  size_t asize)
{
  M33 rotation_matrix_3x3;
  M44 rotation_matrix_4x4 = GP_4x4_identity();
  M44 translation_matrix = GP_4x4_identity();
  M44 transform_matrix;
  
  for(uint8_t i = 0; i < scene->entity_count; ++i) {
    uint8_t e_index = scene->entity_indexes[i];    
    struct Entity *entity = &entities[e_index];
    C3 *position = &positions[entity->position];
    Euler *orientation = &orientations[entity->orientation];
    Polyhedron *model = &*polyhedrons[entity->model];
    Polyhedron *trans = &*world_transformed[entity->transformed];

    TF_set_matrix_rot(&rotation_matrix_3x3, orientation);
    TF_clean_set_upscale_matrix(&rotation_matrix_4x4, &rotation_matrix_3x3);
    TF_clean_set_translation_matrix(&translation_matrix, position);
    GP_4x4_mul_into(&rotation_matrix_4x4, &translation_matrix, &transform_matrix);
  }
}

/**
 * Prepare rotation coefficients. This saves on some multiplications when the actual
 * rotations are carried out. The `coefficients` pointer expects a buffer of
 * sizeof(double) * 9 to store all the coefficients.
 *
 * Coefficients are in order from 0 to 8; mx1, my1, mz1, mx2, my2, mz2, mx3, my3, mz3.
 */
/*
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
*/

/**
 * Rotate a stream of XYZ vertices using the pre-computed euler coefficients.
 */
/*
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
*/

void
set_yaw_rot_matrix(M33 *matrix, double yaw)
{ 
  double cosy = cos(yaw);
  double siny = sin(yaw);
  
  matrix->rc[0][0] = cosy;
  matrix->rc[0][1] = 0;
  matrix->rc[0][2] = -siny;

  matrix->rc[1][0] = 0;
  matrix->rc[1][1] = 1;
  matrix->rc[1][2] = 0;

  matrix->rc[2][0] = siny;
  matrix->rc[2][1] = 0;
  matrix->rc[2][2] = cosy;
}

void
set_pitch_rot_matrix(M33 *matrix, double pitch)
{ 
  double cosp = cos(pitch);
  double sinp = sin(pitch);
  
  matrix->rc[0][0] = 1;
  matrix->rc[0][1] = 0;
  matrix->rc[0][2] = 0;

  matrix->rc[1][0] = 0;
  matrix->rc[1][1] = cosp;
  matrix->rc[1][2] = sinp;

  matrix->rc[2][0] = 0;
  matrix->rc[2][1] = -sinp;
  matrix->rc[2][2] = cosp;
}

void
set_roll_rot_matrix(M33 *matrix, double roll)
{
  double cosr = cos(roll);
  double sinr = sin(roll);
  
  matrix->rc[0][0] = cosr;
  matrix->rc[0][1] = -sinr;
  matrix->rc[0][2] = 0;

  matrix->rc[1][0] = sinr;
  matrix->rc[1][1] = cosr;
  matrix->rc[1][2] = 0;

  matrix->rc[2][0] = 0;
  matrix->rc[2][1] = 0;
  matrix->rc[2][2] = 1;
}

void
TF_set_matrix_rot(M33 *matrix, const Euler *rotation)
{
  M33 y_matrix, p_matrix, r_matrix, yp_matrix;
  set_yaw_rot_matrix(&y_matrix, rotation->yaw);
  set_pitch_rot_matrix(&p_matrix, rotation->pitch);
  set_roll_rot_matrix(&r_matrix, rotation->roll);

  GP_3x3_mul_into(&y_matrix, &p_matrix, &yp_matrix);
  GP_3x3_mul_into(&yp_matrix, &r_matrix, matrix);
}

void
TF_dirty_set_upscale_matrix(M44 *restrict mdest, M33 *restrict mpaste)
{
  mdest->rc[0][0] = mpaste->rc[0][0];
  mdest->rc[0][1] = mpaste->rc[0][1];
  mdest->rc[0][2] = mpaste->rc[0][2];

  mdest->rc[1][0] = mpaste->rc[1][0];
  mdest->rc[1][1] = mpaste->rc[1][1];
  mdest->rc[1][2] = mpaste->rc[1][2];

  mdest->rc[2][0] = mpaste->rc[2][0];
  mdest->rc[2][1] = mpaste->rc[2][1];
  mdest->rc[2][2] = mpaste->rc[2][2];
}

void
TF_clean_set_upscale_matrix(M44 *restrict mdest, M33 *restrict mpaste)
{
  mdest->rc[0][0] = mpaste->rc[0][0];
  mdest->rc[0][1] = mpaste->rc[0][1];
  mdest->rc[0][2] = mpaste->rc[0][2];
  mdest->rc[0][3] = 0;

  mdest->rc[1][0] = mpaste->rc[1][0];
  mdest->rc[1][1] = mpaste->rc[1][1];
  mdest->rc[1][2] = mpaste->rc[1][2];
  mdest->rc[0][3] = 0;

  mdest->rc[2][0] = mpaste->rc[2][0];
  mdest->rc[2][1] = mpaste->rc[2][1];
  mdest->rc[2][2] = mpaste->rc[2][2];
  mdest->rc[2][3] = 0;

  mdest->rc[3][0] = 0;
  mdest->rc[3][1] = 0;
  mdest->rc[3][2] = 0;
  mdest->rc[3][3] = 1;
}

void
TF_dirty_set_translation_matrix(M44 *mdest, C3 *position)
{
  mdest->rc[3][0] = position->c[X];
  mdest->rc[3][1] = position->c[Y];
  mdest->rc[3][2] = position->c[Z];
}

void
TF_clean_set_translation_matrix(M44 *mdest, C3 *position)
{
  GP_4x4_set_identity(mdest);
  TF_dirty_set_translation_matrix(mdest, position);
}
