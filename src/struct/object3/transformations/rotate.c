//
// Created by stf20 on 09.10.2022.
//

#include "struct/object3/object3.h"
#include "struct/vector3/vector3.h"


void object3_rotate(object3_t *obj3, vector3_t angle) {
  vector3_add(&obj3->rotate, angle);

  for (unsigned long int i = 0; i < obj3->list_vertex3.size; i += VERTEX_SIZE) {
    vector3_t tmp = {
        obj3->list_vertex3.vertex3[i + 0] - obj3->shift.x,
        obj3->list_vertex3.vertex3[i + 1] - obj3->shift.y,
        obj3->list_vertex3.vertex3[i + 2] - obj3->shift.z
    };

    vector3_rotate(&tmp, angle);
    obj3->list_vertex3.vertex3[i + 0] = tmp.x + obj3->shift.x;
    obj3->list_vertex3.vertex3[i + 1] = tmp.y + obj3->shift.y;
    obj3->list_vertex3.vertex3[i + 2] = tmp.z + obj3->shift.z;
  }
}
