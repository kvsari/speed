/**
 * Geometric operations
 *
 * We work in cartesian coordinates here.
 *
 * EXTRA: Write a streaming versions of these functions.
 * EXTRA: Write a version which outputs to a provided memory location (pointer).
 *
 * BONUS EXTRA: Use compiler SIMD intrinsics? Perhaps for next project...
 */

#ifndef _GEOP_H_
#define _GEOP_H_

#include <stdlib.h>
#include <stdbool.h>

/**
 * Data type for holding either a Point or Vector in 3D space. Changing between
 * 3D points and 3D vectors happens often enough. Therefore just keeping them in the
 * same data struct and leaving it up to context and variable naming to identify.
 */
struct XYZ {
  double x, y, z;
};

struct XYZ
GP_construct_xyz(const double x, const double y, const double z);

/**
 * Orientation in Euler angles yaw, pitch and roll. Angles are in radians. Beware of
 * gimbal lock.
 *
 * THINK: Couldn't this just re-use `XYZ`? I mean the data types are the same...
 */
struct EulerFix {
  double yaw;
  double pitch;
  double roll;
};

struct EulerFix
GP_construct_euler_fix(const double yaw, const double pitch, const double roll);

/**
 * Sum a vector and vector together.
 */
struct XYZ
GP_vv_sum(const struct XYZ *left, const struct XYZ *right);

/**
 * Multiply a vector and vector together.
 */
struct XYZ
GP_vv_mul(const struct XYZ *left, const struct XYZ *right);

/**
 * Multiply a vector and scalar together.
 *
 */
struct XYZ
GP_vs_mul(const struct XYZ *left, const float scalar);

/**
 * Translate a point by a a translation displacement for each axis.
 */
struct XYZ
GP_pp_trn(const struct XYZ *from, const struct XYZ *by);

/**
 * Get the magnitute of a vector.
 */
double
GP_v_mag(const struct XYZ *vector);

/**
 * Normalize a vector in place.
 */
void
GP_v_mut_normalize(struct XYZ *vector);

/**
 * Normalize a vector in place if it falls outside the error margin.
 */
void
GP_v_mut_normalize_margin(struct XYZ *vector, double margin);

/**
 * Mutating translation a stream of positions by displacement. Lenght of stream is denoted.
 *
 * NOTE: The stream of XYZ referred to by *pos will be mutated in place.
 */
void
GP_pp_mut_stream_translate(struct XYZ *pos, const struct XYZ *disp, size_t length);

#endif
