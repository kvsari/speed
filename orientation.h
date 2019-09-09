/**
 * COMPONENT
 *
 * 3D orientation.
 */

#ifndef _ORIENTATION_H_
#define _ORIENTATION_H_

/**
 * Orientation in Euler angles yaw, pitch and roll. Angles are in radians. Beware of
 * gimbal lock.
 */
struct EulerFix {
  double yaw;
  double pitch;
  double roll;
};



#endif
