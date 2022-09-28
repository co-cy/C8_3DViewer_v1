//
// Created by stf20 on 28.09.2022.
//

#ifndef C8_3DVIEWER_V1_0_0_STRUCT_H
#define C8_3DVIEWER_V1_0_0_STRUCT_H

// Include external libraries
#include <stdlib.h>

// Include own libraries

typedef enum status_code_e {
    OK = 0,
    BAD,
    LOW_MEMORY
} status_code;

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

typedef struct object3_s {
    list_vertex3_t list_vertex3;
    list_polygon_t list_polygon;
} object3_t;

void free_object3(object3_t* object3);

#endif //C8_3DVIEWER_V1_0_0_STRUCT_H
