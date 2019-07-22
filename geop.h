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

/**
 * Data type for holding either a Point or Vector in 3D space. Changing between
 * 3D points and 3D vectors happens often enough. Therefore just keeping them in the
 * same data struct and leaving it up to context and variable naming to identify.
 */
struct XYZ {
  double x, y, z;
};

struct XYZ
construct_xyz(const double x, const double y, const double z);

/**
 * Sum a vector and vector together.
 */
struct XYZ
vv_sum(const struct XYZ *left, const struct XYZ *right);

/**
 * Multiply a vector and vector together.
 */
struct XYZ
vv_mul(const struct XYZ *left, const struct XYZ *right);

/**
 * Multiple a vector and scalar together.
 *
 */
struct XYZ
vs_mul(const struct XYZ *left, const float scalar);

/**
 * Translate a point by a a translation displacement for each axis.
 */
struct XYZ
pp_trn(const struct XYZ *from, const struct XYZ *by);

#endif
