//
// Created by stf20 on 29.09.2022.
//

#include "transformations.h"

void object3_scale(object3_t *obj3, vector3_t scale) {
  vector3_add(&obj3->scale, scale);

  double x = obj3->shift.x;
  double y = obj3->shift.y;
  double z = obj3->shift.z;

  for (unsigned long int i = 0; i < obj3->list_vector3.size; i++) {
    obj3->list_vector3.vectors3[i].x =
        (obj3->list_vector3.vectors3[i].x - x) * scale.x + x;
    obj3->list_vector3.vectors3[i].y =
        (obj3->list_vector3.vectors3[i].y - y) * scale.x + y;
    obj3->list_vector3.vectors3[i].z =
        (obj3->list_vector3.vectors3[i].z - z) * scale.x + z;
  }
}
