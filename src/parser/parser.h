#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 1024
#define SIZE_X_Y_Z 3
#define ALLOCATION_ERROR 1

typedef struct Matrix {
  double** matrix;
  int rows;
  int cols;
} matrix_t;

typedef struct facets {
  int* vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct Data {
  int count_of_vertexes;
  int count_of_facets;
  matrix_t matrix_3d;
  polygon_t* polygons;
} data;

// !ATTENTION change to (const char* line_str);
void count_vertexes(char* line_str, data* store);
void count_facets(char* line_str, data* store);
void allocate_memory(data* store);
void free_memory(data* store);
void display_matrix(data store);
void parse_vertexes(char* line_str, data* store, int out_i);
void count_v_in_f(char* line_str, data* store, int out_k);
void fill_vertexes(char* line_str, data* store, int out_k);

#endif  // PARSER_H_