#include "camera.h"

struct Camera
CM_create_camera()
{
  struct Camera camera;
  camera.position.x = 0;
  camera.position.y = 0;
  camera.position.z = 0;
  camera.t.x = 1;
  camera.t.y = 0;
  camera.t.z = 0;
  camera.s.x = 0;
  camera.s.y = 1;
  camera.s.z = 0;
  camera.n.x = 0;
  camera.n.y = 0;
  camera.n.z = 1;

  return camera;
}

void
CM_mut_correct_tsn(struct Camera *camera, double margin)
{
  GP_v_mut_normalize_margin(&camera->t, margin);
  GP_v_mut_normalize_margin(&camera->s, margin);
  GP_v_mut_normalize_margin(&camera->n, margin);
}

void
CM_draw_picture(
  struct DrawBuffer *draw_buf,
  struct Camera *camera,
  struct Scene *scene,
  struct Entity *entities,
  struct XYZ *positions,
  struct Polyhedron **transformed,
  size_t asize)
{
  // Objects have already been transformed to world space.

  // 1. Translate objects to camera space. The camera is to be the center of the 'world'.

  // 2. Build matrix from n s t params in camera.

  // 3. Apply Guassian elimination on the matrix.

  // 4. Solve for the rotation matrix using the Gaussian eliminated matrix.

  // 5. Apply rotation matrix.

  // TODO: More stuff!
}
