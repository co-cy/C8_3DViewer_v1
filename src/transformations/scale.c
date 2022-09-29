//
// Created by stf20 on 29.09.2022.
//

#include "transformations.h"

void object3_scale(vertex3_t shift, object3_t *obj3) {
  for (unsigned long int i = 0; i < obj3->list_vertex3.size; i++) {
    obj3->list_vertex3.vertexes[i].x *= shift.x;
    obj3->list_vertex3.vertexes[i].y *= shift.y;
    obj3->list_vertex3.vertexes[i].z *= shift.z;
  }
}
