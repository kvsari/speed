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

//const double ERROR_MARGIN = 0.00

/**
 * Index constants for when using C3 and C4 as vectors or points outside this module.
 */
#define X 0
#define Y 1
#define Z 2
#define W 3

/**
 * Data type for holding either a Point or Vector in 3D space. Changing between
 * 3D points and 3D vectors happens often enough. Logically a single row of three columns.
 */
typedef struct Matrix_1x3 {
  double c[3];
} C3;

/**
 * Data type for holding either a Point or Vector in 4D space. Changing between
 * points and vectors happens often enough. This type will usually be used as an XYZ that
 * needed to be upscaled for a 4x4 matrix operation before being truncated again.
 * Logically a single row of four columns.
 */
typedef struct Matrix_1x4 {
  double c[4];
} C4;

C3
GP_new_C3(const double x, const double y, const double z);

C4
GP_new_C4(const double x, const double y, const double z, const double w);

C4
GP_C3_into_C4(const C3 *r, const double w);

C3
GP_C4_truncate(const C4 *r);

/**
 * 3x3 row(r) column(c) matrix definition.
 */
typedef struct Matrix_3x3 {
  double rc[3][3];
} M33;

/**
 * Construct a 3x3 matrix from three c3's. Will construct the matrix by placing
 * each c3 as a row downwards.
 */
M33
GP_3x3_matrix_from_rows(const C3 *r1, const C3 *r2, const C3 *r3);

/**
 * Construct a 3x3 matrix from three XYZ vectors. Will construct the matrix by placing
 * each XYZ vector as a column rightwards.
 */
//struct M33
//GP_m33_from_xyz_cols(const struct XYZ *v1, const struct XYZ *v2, const struct XYZ *v3);

/**
 * Create a fresh new 3x3 identity matrix.
 */
M33
GP_3x3_identity_matrix();

/**
 * Transform the input into an identity matrix.
 */
void
GP_3x3_set_identity(M33 *matrix);

/**
 * 3x3 matrix multiplication. Naive.
 */
M33
GP_3x3_mul(const M33 *restrict left, const M33 *restrict right);

/**
 * 3x3 matrix multiplication storing into existing memory. Slightly less naive?
 */
void
GP_3x3_mul_into(
  const M33 *restrict left,
  const M33 *restrict right,
  M33 *restrict result);

/**
 * 4x4 row(r) column(c) matrix definition
 */
typedef struct Matrix_4x4 {
  double rc[4][4];
} M44;

/**
 * Construct a fresh M44 identity matrix.
 */
M44
GP_4x4_identity();

/**
 * Transform the matrix into an identity matrix.
 */
void
GP_4x4_set_identity(M44 *matrix);

/**
 * 4x4 matrix multiplication. Naive.
 */
M44
GP_4x4_mul(const M44 *restrict left, const M44 *restrict right);

/**
 * 4x4 matrix multiplication storing into existing memory. Slightly less naive?
 */
void
GP_4x4_mul_into(
  const M44 *restrict left,
  const M44 *restrict right,
  M44 *restrict result);

/**
 * Orientation in Euler angles yaw, pitch and roll. Angles are in radians. Beware of
 * gimbal lock.
 *
 * THINK: Couldn't this just re-use `XYZ`? I mean the data types are the same...
 */
typedef struct EulerRotationAngles {
  double yaw;
  double pitch;
  double roll;
} Euler;

Euler
GP_construct_euler_fix(const double yaw, const double pitch, const double roll);

/**
 * Sum a vector and vector together.
 */
//struct XYZ
//GP_vv_sum(const struct XYZ *left, const struct XYZ *right);

/**
 * Multiply a vector and vector together.
 */
//struct XYZ
//GP_vv_mul(const struct XYZ *left, const struct XYZ *right);

/**
 * Multiply a vector and scalar together.
 *
 */
//struct XYZ
//GP_vs_mul(const struct XYZ *left, const float scalar);

/**
 * Translate a point by a a translation displacement for each axis.
 */
//struct XYZ
//GP_pp_trn(const struct XYZ *from, const struct XYZ *by);

/**
 * Get the magnitute of a vector.
 */
double
GP_v_mag(const C3 *vector);

/**
 * Normalize a vector in place.
 */
void
GP_v_mut_normalize(C3 *vector);

/**
 * Normalize a vector in place if its magnitude falls outside the error margin.
 */
void
GP_v_mut_normalize_margin(C3 *vector, double margin);

/**
 * Calculate the scalar product of two vectors.
 */
double
GP_vv_scalar_product(const C3 *restrict v1, const C3 *restrict v2);

/**
 * Mutating translation a stream of positions by displacement. Lenght of stream is denoted.
 *
 * NOTE: The stream of XYZ referred to by *pos will be mutated in place.
 */
//void
//GP_pp_mut_stream_translate(struct XYZ *pos, const struct XYZ *disp, size_t length);

//void
//GP_pm44_mut_stream_mul(struct XYZW *

/**
 * Gaussian elimination to find the transformation matrix. Function expects that the `t`,
 * `s` and `n` vectors are orthogonal and of unit length. It will use the identity matrix
 * as the answer to find the rotation matrix.
 *
 * TODO: Warning, this function hasn't been implemented.
 */
M33
GP_vvv_gaussian_eliminate(
  const C3 *restrict t,
  const C3 *restrict s,
  const C3 *restrict n);

/**
 * Stubbed Guassian elimination function. If one assumes that the `t`, `s`, and `n` vectors
 * are not only orthogonal to each other and unit length, but also orthogonal to the plane;
 * we don't need to do any Gaussian elimination. We just build the rotation matrix by
 * arranging the vectors into it columnwise.
 *
 * NOTE: This function is to be eventually replaced by above `GP_vvv_gaussian_elimiate`.
 */
M33
GP_vvv_gaussian_stub(
  const C3 *restrict t,
  const C3 *restrict s,
  const C3 *restrict n);

/**
 * Multiply an XYZ vector by an M33 producing an XYZ vector results.
 */
//struct XYZ
//GP_vm33_mul(const struct XYZ *restrict v, const struct M33 *restrict m);

#endif
