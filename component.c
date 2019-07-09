/**
 * All components used throughout speed.
 */

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

/**
 * Position in 3D space.
 */
struct Position {
  float x;
  float y;
  float z;
};

/**
 * Orientation in 3D space.
 */
struct Orientation {
  // Using euler angles. TODO: Quaternions or axis angle.... Maybie this should be a union?
  float ax;
  float ay;
  float az;
}
  
#endif
