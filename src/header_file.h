#ifndef WORK_NEW_HOPE_HEADER_FILE_H
#define WORK_NEW_HOPE_HEADER_FILE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int poligon_count;  //  колличество индексов в полигоне
  int* poligon_arr;  // массив полигонов
} poligon;           // pol

typedef struct {
  double x;
  double y;
  double z;
} point;  // coord

typedef struct {
  int vert_numb;  // количество точек
  point* coord;

  int minMax_x[2];
  int minMax_y[2];
  int minMax_z[2];
} vertex;  // xyz

struct capt {
  vertex* xyz;
  poligon* poligon;
  int pol_number;  // колличество созданных структур с полигонами
};
typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

int init_struct(struct capt* capt, int mode, int i);
int core_reader(FILE* file, struct capt* capt);
char* convertation(char* str, double* res);
void print_poligon(struct capt* capt);
void free_all(struct capt* capt);
void v_parsing(struct capt* capt, char* line, int iter);
void f_parsing(struct capt* capt, char* str2, int* len);
void min_max_fanc(struct capt* capt, int iter);
void toCenter_toScale(struct capt* capt, int mode, double scale_value,
                      double prev_scale_value);
double max_number_of_three(double A, double B, double C);
void movePoint(struct capt* capt, double shift_value, char symb);
void rotation_xyz(struct capt* capt, char symb, double value);
int mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int s21_create_matrix(int rows1, int columns1, matrix_t* result);
void s21_remove_matrix(matrix_t* result);
#endif  //  WORK_NEW_HOPE_HEADER_FILE_H
