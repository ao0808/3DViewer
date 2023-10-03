#include <check.h>

#include "header_file.h"

START_TEST(basic_test_1) {
  struct capt capt = {0};
  char x = 'x';
  char z = 'z';
  char y = 'y';
  FILE *file = NULL;
  char file_name[150] = "test.obj";
  file = fopen(file_name, "r");
  core_reader(file, &capt);
  fclose(file);
  ck_assert_double_eq_tol(
      -0.4575, capt.xyz->coord[capt.poligon[0].poligon_arr[0]].x, 1e-6);
  ck_assert_double_eq_tol(
      -0.3688, capt.xyz->coord[capt.poligon[0].poligon_arr[1]].x, 1e-6);
  ck_assert_double_eq_tol(
      -0.2726, capt.xyz->coord[capt.poligon[0].poligon_arr[2]].x, 1e-6);
  ck_assert_double_eq_tol(0, capt.xyz->coord[capt.poligon[1].poligon_arr[0]].x,
                          1e-6);
  ck_assert_double_eq_tol(
      -0.4216, capt.xyz->coord[capt.poligon[1].poligon_arr[1]].x, 1e-6);
  ck_assert_double_eq_tol(
      -0.2444, capt.xyz->coord[capt.poligon[1].poligon_arr[2]].x, 1e-6);
  movePoint(&capt, 1.0, x);
  movePoint(&capt, 0.0, y);
  movePoint(&capt, -1.0, z);
  rotation_xyz(&capt, x, 5);
  rotation_xyz(&capt, y, 0);
  rotation_xyz(&capt, z, -5);
  free_all(&capt);
  matrix_t result;
  s21_create_matrix(2, 2, &result);
  s21_remove_matrix(&result);
}
END_TEST

int main() {
  Suite *s1 = suite_create("3d_tests");
  TCase *tc1_1 = tcase_create("3d_tests ");
  SRunner *sr = srunner_create(s1);
  int result;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, basic_test_1);
  srunner_run_all(sr, CK_ENV);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}