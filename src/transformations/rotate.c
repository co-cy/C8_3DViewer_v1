//
// Created by stf20 on 29.09.2022.
//

#include "transformations.h"

void object3_rotate(vertex3_t shift, object3_t *obj3) {
  shift.x = fmod(shift.x, 360) * M_PI / 180;
  shift.y = fmod(shift.y, 360) * M_PI / 180;
  shift.z = fmod(shift.z, 360) * M_PI / 180;

  for (unsigned long int i = 0; i < obj3->list_vertex3.size; i++) {
    double x = obj3->list_vertex3.vertexes[i].x;
    double y = obj3->list_vertex3.vertexes[i].y;
    double z = obj3->list_vertex3.vertexes[i].z;

    if (shift.x) {
      obj3->list_vertex3.vertexes[i].y = y * cos(shift.x) + z * sin(shift.x);
      obj3->list_vertex3.vertexes[i].z = -y * sin(shift.x) + z * cos(shift.x);
    }
    if (shift.y) {
      obj3->list_vertex3.vertexes[i].x = x * cos(shift.y) + z * sin(shift.y);
      obj3->list_vertex3.vertexes[i].z = -x * sin(shift.y) + z * cos(shift.y);
    }
    if (shift.z) {
      obj3->list_vertex3.vertexes[i].x = x * cos(shift.z) - y * sin(shift.z);
      obj3->list_vertex3.vertexes[i].y = -x * sin(shift.z) + y * cos(shift.z);
    }
  }
}