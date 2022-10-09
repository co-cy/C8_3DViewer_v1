//
// Created by stf20 on 09.10.2022.
//

#include "struct/object3/object3.h"

void object3_move(object3_t *obj3, vector3_t shift) {
  vector3_add(&obj3->shift, shift);

  for (unsigned long int i = 0; i < obj3->list_vertex3.size; i += VERTEX_SIZE) {
    obj3->list_vertex3.vertex3[i + 0] += shift.x;
    obj3->list_vertex3.vertex3[i + 1] += shift.y;
    obj3->list_vertex3.vertex3[i + 2] += shift.z;
  }
}
