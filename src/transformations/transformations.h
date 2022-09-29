//
// Created by stf20 on 29.09.2022.
//

#ifndef INC_3DVIEWER_V1_TRANSFORMATIONS_H
#define INC_3DVIEWER_V1_TRANSFORMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

// Include external libraries
#include "math.h"

// Include own libraries
#include "../struct/object3/object3.h"

void object3_move(vertex3_t shift, object3_t *obj3);
void object3_rotate(vertex3_t angle, object3_t *obj3);
void object3_scale(vertex3_t scale, object3_t *obj3);

#ifdef __cplusplus
}
#endif

#endif  // INC_3DVIEWER_V1_TRANSFORMATIONS_H
