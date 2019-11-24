#include <stdbool.h>

#include "camera.h"

void
tsn_normalize(Camera *camera, double margin)
{
  GP_v_mut_normalize_margin(&camera->t, margin);
  GP_v_mut_normalize_margin(&camera->s, margin);
  GP_v_mut_normalize_margin(&camera->n, margin);
}

bool
tsn_check_orthogonality(Camera *camera, double margin)
{
  double a = GP_vv_scalar_product(&camera->t, &camera->s);
  if(a > margin) { return false; }
  double b = GP_vv_scalar_product(&camera->t, &camera->n);
  if(b > margin) { return false; }
  double c = GP_vv_scalar_product(&camera->s, &camera->n);
  if(c > margin) { return false; }

  return true;
}

Camera
CM_default_camera()
{
  Camera camera;
  
  camera.position.c[X] = 0;
  camera.position.c[Y] = 0;
  camera.position.c[Z] = 0;
  
  camera.t.c[X] = 1;
  camera.t.c[Y] = 0;
  camera.t.c[Z] = 0;
  
  camera.s.c[X] = 0;
  camera.s.c[Y] = 1;
  camera.s.c[Z] = 0;
  
  camera.n.c[X] = 0;
  camera.n.c[Y] = 0;
  camera.n.c[Z] = 1;

  return camera;
}

void
CM_mut_correct_tsn(Camera *camera, double margin)
{
  tsn_normalize(camera, margin);
}

void
CM_draw_picture(
  struct DrawBuffer *draw_buf,
  Camera *camera,
  struct Scene *scene,
  struct Entity *entities,
  //struct XYZ *positions,
  Polyhedron **world_transformed,
  Polyhedron **camera_transformed,
  size_t asize)
{
  // Objects have already been transformed to world space.

  // 1. Build matrix from n s t params in camera.
  // 2. Apply Guassian elimination on the matrix.
  // 3. Solve for the rotation matrix using the Gaussian eliminated matrix.

  // (1, 2, 3) Do all above steps in one easy peasy function call.
  M33 rotation_matrix = GP_vvv_gaussian_stub(&camera->t, &camera->s, &camera->n);

  // 4. Loop through all world space transformed polyhedrons
  for (size_t i = 0; i < asize; ++i) {
    // 4a. We need to loop through our scene... again. Collapsing the two transform loops
    //     (the other from TF_transform_scene_models) would be a good optimization. But for
    //     this game being correct is priority even if it's slow and wasteful.
    uint8_t e_index = scene->entity_indexes[i];    
    struct Entity *entity = &entities[e_index];
    Polyhedron *trans = &*world_transformed[entity->transformed];

    // 4b. Translate objects to camera space. The camera is the center of the players world.
    //GP_pp_mut_stream_translate(trans->vertex, &camera->position, trans->vertices);

    // 4c. Apply rotation matrix.
    
  }

  // TODO: More stuff!
}
