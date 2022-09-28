#include "./parser.h"

// int main() {
//   int count_to_read = 2;
//   FILE* fp = NULL;

//   data store = {0};
//   char* file_name = "cube-3d-shape.obj";

//   for (int i = 0; i < count_to_read; i++) {
//     if (i == 0) {
//       fp = fopen(file_name, "r");

//       if (fp) {
//         char line_str[BUFF_SIZE];
//         while (fgets(line_str, sizeof line_str, fp) != NULL) {
//           count_vertexes(line_str, &store);
//           count_facets(line_str, &store);
//         }

//         allocate_memory(&store);
//         fclose(fp);
//       }
//     } else {
//       fp = fopen(file_name, "r");
//       if (fp) {
//         char line_str[BUFF_SIZE];
//         int i = 1;
//         int k = 1;
//         while (fgets(line_str, sizeof line_str, fp) != NULL) {
//           if (line_str[0] == 'v' && line_str[1] == ' ') {
//             parse_vertexes(line_str, &store, i);
//             i++;
//           } else if (line_str[0] == 'f' && line_str[1] == ' ') {
//             count_v_in_f(line_str, &store, k);
//             fill_vertexes(line_str, &store, k);
//             k++;
//           }
//         }

//         fclose(fp);
//       }
//     }
//   }

//   free_memory(&store);

//   return 0;
// }

void count_vertexes(char* line_str, data* flag_v) {
  if (line_str[0] == 'v' && line_str[1] == ' ') {
    flag_v->count_of_vertexes++;
  }
}

void count_facets(char* line_str, data* flag_f) {
  if (line_str[0] == 'f' && line_str[1] == ' ') {
    flag_f->count_of_facets++;
  }
}

void allocate_memory(data* store) {
  if (store->count_of_vertexes > 0) {
    store->matrix_3d.rows = store->count_of_vertexes + 1;
    store->matrix_3d.cols = SIZE_X_Y_Z;

    store->matrix_3d.matrix = calloc(store->matrix_3d.rows, sizeof(double*));
    if (NULL != store->matrix_3d.matrix) {
      for (int i = 0; i < store->matrix_3d.rows; i++) {
        store->matrix_3d.matrix[i] =
            calloc(store->matrix_3d.cols, sizeof(double));
      }
    } else {
      printf("MEMORY ERROR");
      exit(ALLOCATION_ERROR);
    }
  }

  store->polygons =
      (polygon_t*)calloc(store->count_of_facets + 1, sizeof(polygon_t));
  if (NULL == store->polygons) {
    printf("MEMORY ERROR");
    exit(ALLOCATION_ERROR);
  }
}

void parse_vertexes(char* line_str, data* store, int out_i) {
  int i = 0;
  int j = 0;
  while (line_str[i]) {
    if ((line_str[i] >= '0' && line_str[i] <= '9') || line_str[i] == '-') {
      store->matrix_3d.matrix[out_i][j] = atof(&line_str[i]);
      while ((line_str[i] >= '0' && line_str[i] <= '9') || line_str[i] == '.' ||
             line_str[i] == '-') {
        i++;
      }
      j++;
    }
    i++;
  }
}

void count_v_in_f(char* line_str, data* store, int out_k) {
  int i = 0;
  int count_v = 0;
  // printf("|%s|", line_str);

  while (line_str[i]) {
    if ((line_str[i] >= '1' && line_str[i] <= '9') && line_str[i + 1] == '/') {
      count_v++;
      while ((line_str[i] >= '1' && line_str[i] <= '9') || line_str[i] == '/') {
        i++;
      }
    } else if ((line_str[i] >= '1' && line_str[i] <= '9') &&
               line_str[i + 1] == ' ') {
      count_v++;
    }
    i++;
  }

  store->polygons[out_k].numbers_of_vertexes_in_facets = count_v;
}

void fill_vertexes(char* line_str, data* store, int out_k) {
  store->polygons[out_k].vertexes =
      calloc(store->polygons[out_k].numbers_of_vertexes_in_facets, sizeof(int));
  if (store->polygons[out_k].vertexes == NULL) {
    printf("MEMORY ERROR");
    exit(ALLOCATION_ERROR);
  }

  int i = 0;
  int i_v = 0;

  while (line_str[i]) {
    if ((line_str[i] >= '1' && line_str[i] <= '9') && line_str[i + 1] == '/') {
      store->polygons[out_k].vertexes[i_v] = line_str[i] - '0';
      i_v++;
      while ((line_str[i] >= '1' && line_str[i] <= '9') || line_str[i] == '/') {
        i++;
      }
    } else if ((line_str[i] >= '1' && line_str[i] <= '9') &&
               line_str[i + 1] == ' ') {
      store->polygons[out_k].vertexes[i_v] = line_str[i] - '0';
      i_v++;
    }
    i++;
  }

  for (int j = 0; j < i_v; j++) {
    printf("%d\t", store->polygons[out_k].vertexes[j]);
  }
  printf("\n");
}

// f 1//4 3//4 5//4 4/3/

void free_memory(data* store) {
  if (store->matrix_3d.matrix != NULL && store->matrix_3d.rows > 0 &&
      store->matrix_3d.cols > 0) {
    for (int i = 0; i < store->matrix_3d.rows; i++) {
      free(store->matrix_3d.matrix[i]);
    }
    free(store->matrix_3d.matrix);
    store->matrix_3d.matrix = NULL;
    store->matrix_3d.rows = 0;
    store->matrix_3d.cols = 0;
  }

  for (int i = 1; i < store->count_of_facets + 1; i++) {
    free(store->polygons[i].vertexes);
    store->polygons[i].vertexes = NULL;
    store->polygons[i].numbers_of_vertexes_in_facets = 0;
  }

  if (store->polygons != NULL && store->count_of_facets > 0) {
    free(store->polygons);
    store->polygons = NULL;
    store->count_of_facets = 0;
  }
}

void display_matrix(data store) {
  for (int i = 0; i < store.matrix_3d.rows; i++) {
    for (int j = 0; j < store.matrix_3d.cols; j++) {
      printf("%lf\t", store.matrix_3d.matrix[i][j]);
    }
    printf("\n");
  }
}
