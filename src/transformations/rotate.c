//
// Created by stf20 on 29.09.2022.
//

#include "transformations.h"

void object3_rotate(object3_t *obj3, vector3_t angle) {
  vector3_add(&obj3->rotate, angle);

  obj3->rotate.x = fmod(obj3->rotate.x, 360);
  obj3->rotate.y = fmod(obj3->rotate.x, 360);
  obj3->rotate.z = fmod(obj3->rotate.x, 360);

  for (unsigned long int i = 0; i < obj3->list_vector3.size; i++)
    vector3_rotate(obj3->list_vector3.vectors3 + i, angle);
}

