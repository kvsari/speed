#include <stdbool.h>

#include "camera.h"
#include "geop.h"

void
tsn_normalize(struct Camera *camera, double margin)
{
  GP_v_mut_normalize_margin(&camera->t, margin);
  GP_v_mut_normalize_margin(&camera->s, margin);
  GP_v_mut_normalize_margin(&camera->n, margin);
}

bool
tsn_check_orthogonality(struct Camera *camera, double margin)
{
  double a = GP_vv_scalar_product(&camera->t, &camera->s);
  if(a > margin) { return false; }
  double b = GP_vv_scalar_product(&camera->t, &camera->n);
  if(b > margin) { return false; }
  double c = GP_vv_scalar_product(&camera->s, &camera->n);
  if(c > margin) { return false; }

  return true;
}

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
  tsn_normalize(camera, margin);
}

void
CM_draw_picture(
  struct DrawBuffer *draw_buf,
  struct Camera *camera,
  struct Scene *scene,
  struct Entity *entities,
  //struct XYZ *positions,
  struct Polyhedron **world_transformed,
  struct Polyhedron **camera_transformed,
  size_t asize)
{
  // Objects have already been transformed to world space.

  // 1. Build matrix from n s t params in camera.
  // 2. Apply Guassian elimination on the matrix.
  // 3. Solve for the rotation matrix using the Gaussian eliminated matrix.

  // (1, 2, 3) Do all above steps in one easy peasy function call.
  struct M33 rotation_matrix = GP_vvv_gaussian_stub(&camera->t, &camera->s, &camera->n);

  // 4. Loop through all world space transformed polyhedrons
  for (size_t i = 0; i < asize; ++i) {
    // 4a. We need to loop through our scene... again. Collapsing the two transform loops
    //     (the other from TF_transform_scene_models) would be a good optimization. But for
    //     this game being correct is priority even if it's slow and wasteful.
    uint8_t e_index = scene->entity_indexes[i];    
    struct Entity *entity = &entities[e_index];
    struct Polyhedron *trans = &*world_transformed[entity->transformed];

    // 4b. Translate objects to camera space. The camera is the center of the players world.
    GP_pp_mut_stream_translate(trans->vertex, &camera->position, trans->vertices);

    // 4c. Apply rotation matrix.
    
  }

  // TODO: More stuff!
}
