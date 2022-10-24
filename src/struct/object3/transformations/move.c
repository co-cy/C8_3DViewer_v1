//
// Created by stf20 on 09.10.2022.
//

#include "../object3.h"

void object3_move(object3_t *obj3, vector3_t shift) {
  vector3_add(&obj3->shift, shift);
  object3_update(obj3);
}
