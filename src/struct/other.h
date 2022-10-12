//
// Created by stf20 on 29.09.2022.
//

#ifndef INC_3DVIEWER_V1_OTHER_H
#define INC_3DVIEWER_V1_OTHER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum status_code_e { OK = 0, BAD, LOW_MEMORY } status_code;

typedef struct list_vertex3_s {
  unsigned long count;
  unsigned long size;
  double* vertex3;
} list_vertex3_t;

typedef struct list_polygon_s {
  unsigned long count;
  unsigned long size;
  int* polygons;
} list_polygon_t;

#ifdef __cplusplus
}
#endif

#endif  // INC_3DVIEWER_V1_OTHER_H
