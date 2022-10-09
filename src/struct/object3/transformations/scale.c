//
// Created by stf20 on 09.10.2022.
//

#include "struct/object3/object3.h"

void object3_scale(object3_t *obj3, vector3_t scale) {
  if (fabs(scale.x) > 1e-6) obj3->scale.x *= scale.x;
  if (fabs(scale.y) > 1e-6) obj3->scale.y *= scale.y;
  if (fabs(scale.z) > 1e-6) obj3->scale.z *= scale.z;

  double x = obj3->shift.x;
  double y = obj3->shift.y;
  double z = obj3->shift.z;

  for (unsigned long int i = 0; i < obj3->list_vertex3.size; i += VERTEX_SIZE) {
    if (fabs(scale.x) > 1e-6)
      obj3->list_vertex3.vertex3[i + 0] = (obj3->list_vertex3.vertex3[i + 0] - x) * scale.x + x;
    if (fabs(scale.y) > 1e-6)
      obj3->list_vertex3.vertex3[i + 1] = (obj3->list_vertex3.vertex3[i + 1] - y) * scale.y + y;
    if (fabs(scale.z) > 1e-6)
      obj3->list_vertex3.vertex3[i + 2] = (obj3->list_vertex3.vertex3[i + 2] - z) * scale.z + z;
  }
}
