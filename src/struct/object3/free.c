//
// Created by stf20 on 29.09.2022.
//

#include "object3.h"

void free_object3(object3_t* object3) {
  if (!object3) return;

  if (object3->list_vector3.size) free(object3->list_vector3.vectors3);

  if (object3->list_polygon.size) {
    for (unsigned long i = object3->list_polygon.size;
         i < object3->list_polygon.size; i++) {
      if (object3->list_polygon.polygons[i].size)
        free(object3->list_polygon.polygons[i].vectors3_id);
    }

    free(object3->list_polygon.polygons);
  }

  free(object3);
}