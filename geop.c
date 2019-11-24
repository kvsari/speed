#include <math.h>

#include "geop.h"

C3
GP_new_C3(const double x, const double y, const double z)
{
  C3 new;
  
  new.c[0] = x;
  new.c[1] = y;
  new.c[2] = z;
  
  return new;
}

C4
GP_new_C4(const double x, const double y, const double z, const double w)
{
  C4 new;

  new.c[0] = x;
  new.c[1] = y;
  new.c[2] = z;
  new.c[3] = w;
  
  return new;
}

C4
GP_C3_into_C4(const C3 *r, const double w)
{
  C4 new;

  new.c[0] = r->c[0];
  new.c[1] = r->c[1];
  new.c[2] = r->c[2];
  new.c[3] = w;

  return new;
}

C3
GP_C4_truncate(const C4 *r)
{
  C3 new;

  new.c[0] = r->c[0];
  new.c[1] = r->c[1];
  new.c[2] = r->c[2];

  return new;
}

M33
GP_3x3_matrix_from_rows(const C3 *r1, const C3 *r2, const C3 *r3)
{
  M33 matrix;

  matrix.rc[0][0] = r1->c[0];
  matrix.rc[0][1] = r1->c[1];
  matrix.rc[0][2] = r1->c[2];

  matrix.rc[1][0] = r2->c[0];
  matrix.rc[1][1] = r2->c[1];
  matrix.rc[1][2] = r2->c[2];

  matrix.rc[2][0] = r3->c[0];
  matrix.rc[2][1] = r3->c[1];
  matrix.rc[2][2] = r3->c[2];

  return matrix;
}

/*
struct M33
GP_m33_from_xyz_cols(const struct XYZ *v1, const struct XYZ *v2, const struct XYZ *v3)
{
  struct M33 m33;

  m33.rc[0][0] = v1->x;
  m33.rc[1][0] = v1->y;
  m33.rc[2][0] = v1->z;

  m33.rc[0][1] = v2->x;
  m33.rc[1][1] = v2->y;
  m33.rc[2][1] = v2->z;

  m33.rc[0][2] = v3->x;
  m33.rc[1][2] = v3->y;
  m33.rc[2][2] = v3->z;

  return m33;
}
*/

M33
GP_3x3_identity_matrix()
{
  M33 matrix;
  GP_3x3_set_identity(&matrix);
  return matrix;
}

void
GP_3x3_set_identity(M33 *matrix)
{
  matrix->rc[0][0] = 1;
  matrix->rc[0][1] = 0;
  matrix->rc[0][2] = 0;

  matrix->rc[1][0] = 0;
  matrix->rc[1][1] = 1;
  matrix->rc[1][2] = 0;

  matrix->rc[2][0] = 0;
  matrix->rc[2][1] = 0;
  matrix->rc[2][2] = 1;
}

M33
GP_3x3_mul(const M33 *restrict left, const M33 *restrict right)
{
  M33 result;
  GP_3x3_mul_into(left, right, &result);
  return result;
}

void
GP_3x3_mul_into(
  const M33 *restrict left,
  const M33 *restrict right,
  M33 *restrict result)
{
  for(int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      double k0 = left->rc[i][0] * right->rc[0][j];
      double k1 = left->rc[i][1] * right->rc[1][j];
      double k2 = left->rc[i][2] * right->rc[2][j];
      result->rc[i][j] =  k0 + k1 + k2;
    }
  }
}

M44
GP_4x4_identity()
{
  M44 matrix;
  GP_4x4_set_identity(&matrix);
  return matrix;
}

void
GP_4x4_set_identity(M44 *matrix)
{
  matrix->rc[0][0] = 1;
  matrix->rc[0][1] = 0;
  matrix->rc[0][2] = 0;
  matrix->rc[0][3] = 0;

  matrix->rc[1][0] = 0;
  matrix->rc[1][1] = 1;
  matrix->rc[1][2] = 0;
  matrix->rc[1][3] = 0;

  matrix->rc[2][0] = 0;
  matrix->rc[2][1] = 0;
  matrix->rc[2][2] = 1;
  matrix->rc[2][3] = 0;

  matrix->rc[3][0] = 0;
  matrix->rc[3][1] = 0;
  matrix->rc[3][2] = 0;
  matrix->rc[3][3] = 1;
}

M44
GP_4x4_mul(const M44 *restrict left, const M44 *restrict right)
{
  M44 result;
  GP_4x4_mul_into(left, right, &result);
  return result;
}

void
GP_4x4_mul_into(
  const M44 *restrict left,
  const M44 *restrict right,
  M44 *restrict result)
{
  for(int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      double k0 = left->rc[i][0] * right->rc[0][j];
      double k1 = left->rc[i][1] * right->rc[1][j];
      double k2 = left->rc[i][2] * right->rc[2][j];
      double k3 = left->rc[i][3] * right->rc[3][j];
      result->rc[i][j] =  k0 + k1 + k2 + k3;
    }
  }
}

Euler
GP_construct_euler_fix(const double yaw, const double pitch, const double roll)
{
  Euler new;

  new.yaw = yaw;
  new.pitch = pitch;
  new.roll = roll;

  return new;
}

/*
struct XYZ
GP_vv_sum(const struct XYZ *left, const struct XYZ *right)
{
  struct XYZ result;

  result.x = left->x + right->x;
  result.y = left->y + right->y;
  result.z = left->z + right->z;

  return result;
}

struct XYZ
GP_vv_mul(const struct XYZ *left, const struct XYZ *right)
{
  struct XYZ result;

  result.x = left->x * right->x;
  result.y = left->y * right->y;
  result.z = left->z * right->z;

  return result;
}

struct XYZ
GP_vs_mul(const struct XYZ *left, const float scalar)
{
  struct XYZ result;

  result.x = left->x * scalar;
  result.y = left->y * scalar;
  result.z = left->z * scalar;

  return result;
}

struct XYZ
GP_pp_trn(const struct XYZ *from, const struct XYZ *by)
{
  struct XYZ result;

  result.x = from->x + by->x;
  result.y = from->y + by->y;
  result.z = from->z + by->z;

  return result;
}
*/

double
GP_v_mag(const C3 *vector)
{
  double x2 = vector->c[X] * vector->c[X];
  double y2 = vector->c[Y] * vector->c[Y];
  double z2 = vector->c[Z] * vector->c[Z];
  return sqrt(x2 + y2 + z2);
}

void
GP_v_mut_normalize(C3 *vector)
{
  double magnitude = GP_v_mag(vector);
  vector->c[X] = vector->c[X] == 0 ? 0 : vector->c[X] / magnitude;
  vector->c[Y] = vector->c[Y] == 0 ? 0 : vector->c[Y] / magnitude;
  vector->c[Z] = vector->c[Z] == 0 ? 0 : vector->c[Z] / magnitude;
}

void
GP_v_mut_normalize_margin(C3 *vector, double margin)
{
  double magnitude = GP_v_mag(vector);
  if(abs(magnitude - 1.0) > margin) {
    vector->c[X] = vector->c[X] == 0 ? 0 : vector->c[X] / magnitude;
    vector->c[Y] = vector->c[Y] == 0 ? 0 : vector->c[Y] / magnitude;
    vector->c[Z] = vector->c[Z] == 0 ? 0 : vector->c[Z] / magnitude;
  }
}

double
GP_vv_scalar_product(const C3 *restrict v1, const C3 *restrict v2)
{
  return v1->c[X] * v2->c[X] + v1->c[Y] * v2->c[Y] + v1->c[Z] * v2->c[Z];
}

/*
void
GP_pp_mut_stream_translate(struct XYZ *pos, const struct XYZ *disp, size_t length)
{
  for(size_t i = 0; i < length; ++i) {
    pos->x += disp->x;
    pos->y += disp->y;
    pos->z += disp->z;
    pos++;
  }
}
*/

M33
GP_vvv_gaussian_stub(
  const C3 *restrict t,
  const C3 *restrict s,
  const C3 *restrict n)
{
  return GP_3x3_matrix_from_rows(t, s, n);
}

/*
struct XYZ
GP_vm33_stream_mul(const struct XYZ *restrict v, const struct M33 *restrict m)
{
  struct XYZ result;

  result.x = v->x * m->rc[0][0] + v->y * m->rc[1][0] + v->z * m->rc[2][0];
  result.y = v->x * m->rc[0][0] + v->y * m->rc[1][0] + v->z * m->rc[2][0];
  result.z = v->x * m->rc[0][0] + v->y * m->rc[1][0] + v->z * m->rc[2][0];
}
*/
