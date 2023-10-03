#include "header_file.h"

int init_struct(struct capt* capt, int mode, int i) {
  if (mode == 0) {
    capt->poligon = (poligon*)malloc(sizeof(poligon));
    capt->poligon[0].poligon_arr = (int*)malloc(sizeof(int));
    capt->poligon[0].poligon_count = 0;
    capt->poligon[0].poligon_arr[0] = 0;

    capt->xyz = (vertex*)malloc(1 * sizeof(vertex));
    capt->xyz->coord = (point*)malloc(1 * sizeof(*capt->xyz->coord));
  } else if (mode == 1) {
    capt->xyz->coord =
        (point*)realloc(capt->xyz->coord, (1 + i) * sizeof(*capt->xyz->coord));

  } else if (mode == 2) {
    capt->poligon =
        (poligon*)realloc(capt->poligon, capt->pol_number * sizeof(poligon));
    capt->poligon[capt->pol_number - 1].poligon_arr = (int*)malloc(sizeof(int));
    capt->poligon[capt->pol_number - 1].poligon_arr[0] = 0;
    capt->poligon[capt->pol_number - 1].poligon_count = 0;
  } else if (mode == 3) {
    capt->poligon[capt->pol_number - 1].poligon_arr = (int*)realloc(
        capt->poligon[capt->pol_number - 1].poligon_arr,
        capt->poligon[capt->pol_number - 1].poligon_count * sizeof(int));
  }
  return 0;
}

int core_reader(FILE* file, struct capt* capt) {
  int error = 0;
  char* str2;
  int len = 0;
  int iter = 0;
  size_t size = 0;

  char* line = NULL;
  capt->pol_number = 0;

  init_struct(capt, 0, 0);
  capt->pol_number = 0;

  if (file != NULL) {
    while (getline(&line, &size, file) != -1) {  // берем строку
      str2 = line;

      if (line[0] == 'v' && line[1] != 't' && line[1] != 'n') {
        v_parsing(capt, line, iter);
        iter += 1;
        init_struct(capt, 1, iter);
      }

      if (str2[0] == 'f') {
        f_parsing(capt, str2, &len);
      }
      if (line != NULL) {
        free(line);
        line = NULL;
      }
    }

    toCenter_toScale(capt, 0, 0, 0);

    if (line != NULL) {
      free(line);
      line = NULL;
    }
  } else {
    error = 1;
  }

  return error;
}

double max_number_of_three(double A, double B, double C) {
  double result = 0;
  if (A >= B && A >= C) {
    result = A;
  } else if (B >= A && B >= C) {
    result = B;
  } else {
    result = C;
  }
  return result;
}
void toCenter_toScale(struct capt* capt, int mode, double scale_value,
                      double prev_scale_value) {
  if (!mode) {
    double center_x = capt->xyz->minMax_x[0] +
                      (capt->xyz->minMax_x[1] - capt->xyz->minMax_x[0]) / 2;

    double center_y = capt->xyz->minMax_y[0] +
                      (capt->xyz->minMax_y[1] - capt->xyz->minMax_y[0]) / 2;

    double center_z = capt->xyz->minMax_z[0] +
                      (capt->xyz->minMax_z[1] - capt->xyz->minMax_z[0]) / 2;

    for (int i = 0; i < capt->xyz->vert_numb; i++) {
      capt->xyz->coord[i].x -= center_x;
      capt->xyz->coord[i].y -= center_y;
      capt->xyz->coord[i].z -= center_z;
    }

    center_x = capt->xyz->minMax_x[1] - capt->xyz->minMax_x[0];
    center_y = capt->xyz->minMax_y[1] - capt->xyz->minMax_y[0];
    center_z = capt->xyz->minMax_z[1] - capt->xyz->minMax_z[0];
    double mult = 0;
    mult = max_number_of_three(center_x, center_y, center_z);
    if (mult) {
      mult = (0.8 - (-0.8)) / mult;
    } else {
      mult = 1;
    }
    for (int i = 0; i < capt->xyz->vert_numb; i++) {
      capt->xyz->coord[i].x *= mult;
      capt->xyz->coord[i].y *= mult;
      capt->xyz->coord[i].z *= mult;
    }
  } else if (mode) {
    double scale = 0.1;
    if (prev_scale_value > scale_value) {
      scale = scale_value / prev_scale_value;

    } else if (prev_scale_value < scale_value) {
      scale = 1 * (scale_value / prev_scale_value);
    } else {
      scale = 1;
    }

    for (int i = 0; i < capt->xyz->vert_numb; i++) {
      capt->xyz->coord[i].x *= scale;
      capt->xyz->coord[i].y *= scale;
      capt->xyz->coord[i].z *= scale;
    }
  }
}

void movePoint(struct capt* capt, double shift_value, char symb) {
  if (symb == 'x') {
    for (int i = 0; i < capt->xyz->vert_numb; i++) {
      capt->xyz->coord[i].x += shift_value;
    }
  }
  if (symb == 'y') {
    for (int i = 0; i < capt->xyz->vert_numb; i++) {
      capt->xyz->coord[i].y += shift_value;
    }
  }
  if (symb == 'z') {
    for (int i = 0; i < capt->xyz->vert_numb; i++) {
      capt->xyz->coord[i].z += shift_value;
    }
  }
}

void f_parsing(struct capt* capt, char* str2, int* len) {
  int j = 0;
  char* str1 = NULL;
  int count = 0;
  int count_while = 0;
  int len_count = 0;
  len_count = strlen(str2);

  int flag = 0;
  double x = 0;
  int t = 0;

  while (t < len_count) {
    if (str2[t] == 47) {
      count++;
    }
    t++;
  }
  count = count / 2;

  str1 = str2;
  capt->pol_number++;
  if (capt->pol_number > 1) {
    init_struct(capt, 2, 0);  // создаем под следующий элемент
  }
  capt->poligon[capt->pol_number - 1].poligon_count = 0;

  while (flag != 1) {
    if (str2[j] == '\0' || str2[j] == '\n' || str2[j] == 13 || str2[j] == ' ') {
      str1 = NULL;
      flag = 1;
    }
    if (count_while >= count) {
      str1 = NULL;
      flag = 1;
    }
    if (str1) {
      x = 0;
      capt->poligon[capt->pol_number - 1].poligon_count++;
      if (capt->poligon[capt->pol_number - 1].poligon_count > 1) {
        init_struct(capt, 3, 0);
      }
      str1 = convertation(str2, &x);

      capt->poligon[capt->pol_number - 1]
          .poligon_arr[capt->poligon[capt->pol_number - 1].poligon_count - 1] =
          fabs(x) - 1;
      for (j = 0; str1[j] != ' ' && str1[j] != '\0' && str1[j] != '\n'; j++) {
      }
      for (; str1[j] == ' '; j++) {
      }

      for (j = 0; str1[j] != ' ' && str1[j] != '\0' && str1[j] != '\n'; j++) {
      }
      str2 = str1 + j;
      *len = strlen(str2);

      if (str1[j] == '\0' || str1[j] == '\n') {
        str1 = NULL;
        flag = 1;
      }
    }
    count_while++;
  }
}

void v_parsing(struct capt* capt, char* line, int iter) {
  char symb = 'v';

  sscanf(line, "%c %lf %lf %lf", &symb, &capt->xyz->coord[iter].x,
         &capt->xyz->coord[iter].y, &capt->xyz->coord[iter].z);
  capt->xyz->vert_numb += 1;

  if (!iter) {
    capt->xyz->minMax_x[0] = capt->xyz->coord[iter].x;
    capt->xyz->minMax_x[1] = capt->xyz->coord[iter].x;

    capt->xyz->minMax_y[0] = capt->xyz->coord[iter].y;
    capt->xyz->minMax_y[1] = capt->xyz->coord[iter].y;

    capt->xyz->minMax_z[0] = capt->xyz->coord[iter].z;
    capt->xyz->minMax_z[1] = capt->xyz->coord[iter].z;
  } else {
    min_max_fanc(capt, iter);
  }
}

void min_max_fanc(struct capt* capt, int iter) {
  ////x
  if (capt->xyz->minMax_x[0] > capt->xyz->coord[iter].x) {
    capt->xyz->minMax_x[0] = capt->xyz->coord[iter].x;
  }

  if (capt->xyz->minMax_x[1] < capt->xyz->coord[iter].x) {
    capt->xyz->minMax_x[1] = capt->xyz->coord[iter].x;
  }
  /////y
  if (capt->xyz->minMax_y[0] > capt->xyz->coord[iter].y) {
    capt->xyz->minMax_y[0] = capt->xyz->coord[iter].y;
  }

  if (capt->xyz->minMax_y[1] < capt->xyz->coord[iter].y) {
    capt->xyz->minMax_y[1] = capt->xyz->coord[iter].y;
  }
  /////z
  if (capt->xyz->minMax_z[0] > capt->xyz->coord[iter].z) {
    capt->xyz->minMax_z[0] = capt->xyz->coord[iter].z;
  }

  if (capt->xyz->minMax_z[1] < capt->xyz->coord[iter].z) {
    capt->xyz->minMax_z[1] = capt->xyz->coord[iter].z;
  }
}

void print_poligon(struct capt* capt) {
  for (int i = 0; i < capt->pol_number; i++) {
    for (int j = 0; j < capt->poligon[i].poligon_count; j++) {
      printf("%d ", capt->poligon[i].poligon_arr[j]);
      printf("X - %lf Y - %lf Z - %lf\n",
             capt->xyz->coord[capt->poligon[i].poligon_arr[j]].x,
             capt->xyz->coord[capt->poligon[i].poligon_arr[j]].y,
             capt->xyz->coord[capt->poligon[i].poligon_arr[j]].z);
    }
    printf("\n");
  }
}

char* convertation(char* str, double* res) {
  char* tmp = NULL;
  *res = 0;
  int i = 0;
  if (str[i] == 'f') {
    i = i + 1;
  }
  if (str[i] == ' ') {
    i = i + 1;
  }
  for (; (str[i] < 58 && str[i] > 47); i++) {
    *res = (*res * 10) + (int)(str[i] - '0');
  }
  if (str[i] != '\0') {
    tmp = str + i;
  }
  return tmp;
}

void free_all(struct capt* capt) {
  free(capt->xyz->coord);
  free(capt->xyz);
  for (int i = 0; i < capt->pol_number; i++) {
    free(capt->poligon[i].poligon_arr);
  }
  free(capt->poligon);
}

void rotation_xyz(struct capt* capt, char symb, double value) {
  if (symb == 'x') {
    for (int i = 0; i < capt->xyz->vert_numb; i++) {
      capt->xyz->coord[i].x = 1 * capt->xyz->coord[i].x +
                              0 * capt->xyz->coord[i].y +
                              0 * capt->xyz->coord[i].z;

      capt->xyz->coord[i].y = 0 * capt->xyz->coord[i].x +
                              cos(value) * capt->xyz->coord[i].y +
                              -sin(value) * capt->xyz->coord[i].z;

      capt->xyz->coord[i].z = 0 * capt->xyz->coord[i].x +
                              sin(value) * capt->xyz->coord[i].y +
                              cos(value) * capt->xyz->coord[i].z;
    }
  }

  if (symb == 'y') {
    for (int i = 0; i < capt->xyz->vert_numb; i++) {
      capt->xyz->coord[i].x = cos(value) * capt->xyz->coord[i].x +
                              0 * capt->xyz->coord[i].y +
                              sin(value) * capt->xyz->coord[i].z;
      capt->xyz->coord[i].y = 0 * capt->xyz->coord[i].x +
                              1 * capt->xyz->coord[i].y +
                              0 * capt->xyz->coord[i].z;
      capt->xyz->coord[i].z = -sin(value) * capt->xyz->coord[i].x +
                              0 * capt->xyz->coord[i].y +
                              cos(value) * capt->xyz->coord[i].z;
    }
  }

  if (symb == 'z') {
    for (int i = 0; i < capt->xyz->vert_numb; i++) {
      capt->xyz->coord[i].x = cos(value) * capt->xyz->coord[i].x +
                              -sin(value) * capt->xyz->coord[i].y + 0;
      capt->xyz->coord[i].y = sin(value) * capt->xyz->coord[i].x +
                              cos(value) * capt->xyz->coord[i].y + 0;
      capt->xyz->coord[i].z = 0 * capt->xyz->coord[i].x +
                              0 * capt->xyz->coord[i].y +
                              1 * capt->xyz->coord[i].z;
    }
  }
}

void s21_remove_matrix(matrix_t* result) {
  if (result != NULL) {
    for (int i = 0; i < result->rows; i++) {
      free(result->matrix[i]);
    }
    free(result->matrix);
    result->matrix = NULL;
    result->rows = 0;
    result->columns = 0;
  }
}

int s21_create_matrix(int rows1, int columns1, matrix_t* result) {
  int error = 0;

  if (rows1 < 1 || columns1 < 1) {
    error = 1;
  } else {
    result->rows = rows1;
    result->columns = columns1;

    result->matrix = (double**)malloc(result->rows * sizeof(double));

    if (result->matrix != NULL) {
      for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = (double*)malloc(result->columns * sizeof(double));
        if (result->matrix[i] == NULL) {
          error = 1;
          break;
        }
      }
      if (!error) {
        for (int i = 0; i < result->rows; i++) {
          for (int i1 = 0; i1 < result->columns; i1++) {
            result->matrix[i][i1] = 0;
          }
        }
      }
    } else {
      error = 1;
    }
  }
  if (error) {
    s21_remove_matrix(result);
  }
  return error;
}
