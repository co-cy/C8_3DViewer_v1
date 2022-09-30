//
// Created by stf20 on 29.09.2022.
//

#include "transformations.h"

void object3_move(object3_t *obj3, vector3_t shift) {
  vector3_add(&obj3->shift, shift);

  for (unsigned long int i = 0; i < obj3->list_vector3.size; i++)
    vector3_add(obj3->list_vector3.vectors3 + i, shift);
}
