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
