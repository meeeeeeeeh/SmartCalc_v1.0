#include "calc.h"

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// abs tests
START_TEST(calc_test_1) {
  int n = 10;
  ck_assert_int_eq(s21_abs(n), abs(n));
}
END_TEST

Suite *calc_suite(void) {
  TCase *tc = tcase_create("calc_core");
  Suite *s = suite_create("calc_tests");

  tcase_add_test(tc, calc_test_1);


  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int failed = 0;
  SRunner *sr;

  sr = srunner_create(calc_suite());
  srunner_add_suite(sr, s21_ceil_suite());
 

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed == 0) ? 1 : 0;
}
