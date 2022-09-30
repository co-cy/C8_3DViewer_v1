//
// Created by stf20 on 29.09.2022.
//

#ifndef INC_3DVIEWER_V1_OTHER_H
#define INC_3DVIEWER_V1_OTHER_H

#ifdef __cplusplus
extern "C" {
#endif

// Include external libraries

// Include own libraries
#include "../vector3/vector3.h"

typedef enum status_code_e { OK = 0, BAD, LOW_MEMORY } status_code;

typedef struct list_vector3_s {
  unsigned long int size;
  vector3_t *vectors3;
} list_vector3_t;

typedef struct polygon_s {
  unsigned long int size;
  unsigned long int *vectors3_id;
} polygon_t;

typedef struct list_polygon_s {
  unsigned int long size;
  polygon_t *polygons;
} list_polygon_t;

#ifdef __cplusplus
}
#endif

#endif  // INC_3DVIEWER_V1_OTHER_H
