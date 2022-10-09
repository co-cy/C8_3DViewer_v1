//
// Created by stf20 on 29.09.2022.
//

#include "object3.h"

void free_object3(object3_t** object3) {
  if (!(*object3)) return;

  if ((*object3)->list_vertex3.size) free((*object3)->list_vertex3.vertex3);
  if ((*object3)->list_polygon.size) free((*object3)->list_polygon.polygons);

  free((*object3));
}