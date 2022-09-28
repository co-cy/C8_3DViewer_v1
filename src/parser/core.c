//
// Created by stf20 on 28.09.2022.
//

#include "core.h"

void parse_size_from_obj_file(FILE *file, object3_t* object3);
void parse_data_from_obj_file(FILE *file, object3_t* object3);
void parse_vertex3_from_obj_file(FILE *file, list_vertex3_t* list_vertex3);
void parse_polygon_from_obj_file(FILE *file, list_polygon_t *list_polygon);

object3_t* parse_object3_from_obj_file(const char* filename) {
  FILE* file;
  if (fopen_s(&file, filename, "r")) return NULL;

  object3_t* new_object = calloc(1, sizeof(object3_t));
  if (!new_object) exit(LOW_MEMORY);

  parse_size_from_obj_file(file, new_object);
  fseek(file, SEEK_SET, 0);

  parse_data_from_obj_file(file, new_object);

  return new_object;
}

void parse_size_from_obj_file(FILE* file, object3_t* object3) {
  object3->list_vertex3.size = 0;
  object3->list_polygon.size = 0;

  const int SIZE = 1024 * 1024;
  char buff[SIZE];

  while (fgets(buff, SIZE, file))
    if (buff[0] == 'v' && buff[1] == ' ')
      object3->list_vertex3.size++;
    else if (buff[0] == 'f' && buff[1] == ' ')
      object3->list_polygon.size++;

  object3->list_vertex3.vertexes =
      calloc(object3->list_vertex3.size, sizeof(vertex3_t));
  if (!object3->list_vertex3.vertexes) exit(LOW_MEMORY);

  object3->list_polygon.polygons =
      calloc(object3->list_polygon.size, sizeof(polygon_t));
  if (!object3->list_polygon.polygons) exit(LOW_MEMORY);
}

void parse_data_from_obj_file(FILE* file, object3_t* object3) {
  parse_vertex3_from_obj_file(file, &object3->list_vertex3);
  parse_polygon_from_obj_file(file, &object3->list_polygon);
}

void parse_vertex3_from_obj_file(FILE* file, list_vertex3_t* list_vertex3) {
  const int SIZE = 1024;
  char buff[SIZE];

  for (unsigned int i = 0; i < list_vertex3->size; i++) {
    fgets(buff, SIZE, file);

    vertex3_t vertex3;
    sscanf_s(buff + 2, "%Lf%Lf%Lf", &vertex3.x, &vertex3.y, &vertex3.z);

    list_vertex3->vertexes[i] = vertex3;
  }
}

void parse_polygon_from_obj_file(FILE* file, list_polygon_t* list_polygon) {
  const int SIZE = 1024 * 1024;
  char buff[SIZE];

  for (unsigned int i = 0; i < list_polygon->size; i++) {
    fgets(buff, SIZE, file);
    if (buff[0] == 'f' && buff[1] == ' ') {
      char* tmp = buff + 1;

      list_polygon->polygons[i].size = 0;
      for (; *tmp; tmp++)
        if (*tmp == ' ' && *(tmp + 1)) list_polygon->polygons[i].size++;

      list_polygon->polygons[i].vertexes3_id =
          calloc(list_polygon->polygons[i].size, sizeof(unsigned long int));
      if (!list_polygon->polygons[i].vertexes3_id) exit(LOW_MEMORY);

      tmp = buff + 2;
      for (unsigned long int j = 0; j < list_polygon->polygons[i].size; j++) {
        list_polygon->polygons[i].vertexes3_id[j] = strtoul(tmp, &tmp, 10) - 1;
        while (j < (list_polygon->polygons[i].size - 1) && *tmp != ' ') tmp++;
      }
    }
  }
}