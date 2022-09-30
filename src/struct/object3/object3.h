//
// Created by stf20 on 29.09.2022.
//

#ifndef INC_3DVIEWER_V1_OBJECT3_H
#define INC_3DVIEWER_V1_OBJECT3_H

#ifdef __cplusplus
extern "C" {
#endif

// Include external libraries
#include <stdlib.h>

// Include own libraries
#include "../other/other.h"

typedef struct object3_s {
  vector3_t shift;
  vector3_t rotate;
  vector3_t scale;

  list_vector3_t list_vector3;
  list_polygon_t list_polygon;
} object3_t;

object3_t* create_object3();
void free_object3(object3_t* object3);

#ifdef __cplusplus
}
#endif

#endif  // INC_3DVIEWER_V1_OBJECT3_H
