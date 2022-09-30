//
// Created by stf20 on 29.09.2022.
//

#ifndef INC_3DVIEWER_V1_TRANSFORMATIONS_H
#define INC_3DVIEWER_V1_TRANSFORMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

// Include external libraries
#include <math.h>

// Include own libraries
#include "../struct/object3/object3.h"

void object3_move(object3_t *obj3, vector3_t shift);
void object3_rotate(object3_t *obj3, vector3_t angle);
void object3_scale(object3_t *obj3, vector3_t scale);

#ifdef __cplusplus
}
#endif

#endif  // INC_3DVIEWER_V1_TRANSFORMATIONS_H
