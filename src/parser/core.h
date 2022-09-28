//
// Created by stf20 on 28.09.2022.
//

#ifndef C8_3DVIEWER_V1_0_0_CORE_H
#define C8_3DVIEWER_V1_0_0_CORE_H

// Include external libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include own libraries
#include "../struct/struct.h"

object3_t* parse_object3_from_obj_file(const char* filename);

#endif  // C8_3DVIEWER_V1_0_0_CORE_H
