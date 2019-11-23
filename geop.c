#include <math.h>

#include "geop.h"

struct XYZ
GP_construct_xyz(const double x, const double y, const double z)
{
  struct XYZ new;

  new.x = x;
  new.y = y;
  new.z = z;

  return new;
}

struct XYZW
GP_construct_xyzw(const double x, const double y, const double z, const double w) {
  struct XYZW new;

  new.x = x;
  new.y = y;
  new.z = z;
  new.w = w;

  return new;
}

struct XYZW
GP_xyz_into_xyzw(const struct XYZ xyz, const double w) {
  struct XYZW new;

  new.x = xyz.x;
  new.y = xyz.y;
  new.z = xyz.z;
  new.w = w;

  return new;
}

struct XYZ
GP_xyzw_truncate(const struct XYZW xyzw) {
  struct XYZ new;

  new.x = xyzw.x;
  new.y = xyzw.y;
  new.z = xyzw.z;

  return new;
}

struct M33
GP_m33_from_xyz_rows(const struct XYZ *v1, const struct XYZ *v2, const struct XYZ *v3)
{
  struct M33 m33;

  m33.rc[0][0] = v1->x;
  m33.rc[0][1] = v1->y;
  m33.rc[0][2] = v1->z;

  m33.rc[1][0] = v2->x;
  m33.rc[1][1] = v2->y;
  m33.rc[1][2] = v2->z;

  m33.rc[2][0] = v3->x;
  m33.rc[2][1] = v3->y;
  m33.rc[2][2] = v3->z;

  return m33;
}

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

struct M33
GP_m33_identity()
{
  struct M33 m33;
  GP_m33_set_identity(&m33);
  return m33;
}

void
GP_m33_set_identity(struct M33 *matrix)
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

struct M33
GP_2m33_mul(const struct M33 *restrict m1, const struct M33 *restrict m2)
{
  struct M33 result;
  GP_2m33_mul_into(m1, m2, &result);
  return result;
}

void
GP_2m33_mul_into(
  const struct M33 *restrict m1,
  const struct M33 *restrict m2,
  struct M33 *restrict result)
{
  for(int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      double k0 = m1->rc[i][0] * m2->rc[0][j];
      double k1 = m1->rc[i][1] * m2->rc[1][j];
      double k2 = m1->rc[i][2] * m2->rc[2][j];
      result->rc[i][j] =  k0 + k1 + k2;
    }
  }
}

struct M44
GP_m44_identity()
{
  struct M44 m44;
  GP_m44_set_identity(&m44);
  return m44;
}

void
GP_m44_set_identity(struct M44 *matrix)
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

struct M44
GP_2m44_mul(const struct M44 *restrict m1, const struct M44 *restrict m2)
{
  struct M44 result;
  GP_2m44_mul_into(m1, m2, &result);
  return result;
}

void
GP_2m44_mul_into(
  const struct M44 *restrict left,
  const struct M44 *restrict right,
  struct M44 *restrict result)
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

struct EulerFix
GP_construct_euler_fix(const double yaw, const double pitch, const double roll)
{
  struct EulerFix new;

  new.yaw = yaw;
  new.pitch = pitch;
  new.roll = roll;

  return new;
}

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

double
GP_v_mag(const struct XYZ *vector)
{
  return sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
}

void
GP_v_mut_normalize(struct XYZ *vector)
{
  double magnitude = GP_v_mag(vector);
  vector->x = vector->x == 0 ? 0 : vector->x / magnitude;
  vector->y = vector->y == 0 ? 0 : vector->y / magnitude;
  vector->z = vector->z == 0 ? 0 : vector->z / magnitude;
}

void
GP_v_mut_normalize_margin(struct XYZ *vector, double margin)
{
  double magnitude = GP_v_mag(vector);
  if(abs(magnitude - 1.0) > margin) {
    vector->x = vector->x == 0 ? 0 : vector->x / magnitude;
    vector->y = vector->y == 0 ? 0 : vector->y / magnitude;
    vector->z = vector->z == 0 ? 0 : vector->z / magnitude;
  }
}

double
GP_vv_scalar_product(const struct XYZ *restrict v1, const struct XYZ *restrict v2)
{
  return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

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

struct M33
GP_vvv_gaussian_stub(
  const struct XYZ *restrict t,
  const struct XYZ *restrict s,
  const struct XYZ *restrict n)
{
  return GP_m33_from_xyz_rows(t, s, n);
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
