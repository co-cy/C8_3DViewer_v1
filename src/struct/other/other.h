//
// Created by stf20 on 29.09.2022.
//

#ifndef INC_3DVIEWER_V1_OTHER_H
#define INC_3DVIEWER_V1_OTHER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum status_code_e { OK = 0, BAD, LOW_MEMORY } status_code;

typedef struct vertex3_s {
  double x;
  double y;
  double z;
} vertex3_t;

typedef struct list_vertex3_s {
  unsigned long int size;
  vertex3_t *vertexes;
} list_vertex3_t;

typedef struct polygon_s {
  unsigned long int size;
  unsigned long int *vertexes3_id;
} polygon_t;

typedef struct list_polygon_s {
  unsigned int long size;
  polygon_t *polygons;
} list_polygon_t;

#ifdef __cplusplus
}
#endif

#endif  // INC_3DVIEWER_V1_OTHER_H
