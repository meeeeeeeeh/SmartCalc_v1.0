#include "calc.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(calc_test_1) {
  double res = 0.0;
  double x = 0.2;
  char input[] = "1+2-3x4^5+(-7)xX-(+8)-sqrt(4)/2.5";
  double ans = -3079.2;
  ck_assert_int_eq(calc(input, &res, x), 0);
  ck_assert_double_eq_tol(res, ans, 0.000001);
}
END_TEST

START_TEST(calc_test_2) {
  double res = 0.0;
  double x = 0.2;
  char input[] = "cos(50)+sin(10)+tan(20)";
  double ans = 2.658106;
  ck_assert_int_eq(calc(input, &res, x), 0);
  ck_assert_double_eq_tol(res, ans, 0.000001);
}
END_TEST

START_TEST(calc_test_3) {
  double res = 0.0;
  double x = 0.2;
  char input[] = "cos(50)+sin(10)+tan(20)++";
  ck_assert_int_eq(calc(input, &res, x), 1);
}
END_TEST

START_TEST(calc_test_4) {
  double res = 0.0;
  double x = 0.2;
  char input[] = "7+0+8(-8(";
  ck_assert_int_eq(calc(input, &res, x), 1);
}
END_TEST

START_TEST(calc_test_5) {
  double res = 0.0;
  double x = 0.2;
  char input[] = "40+9-8\0";
  ck_assert_int_eq(calc(input, &res, x), 1);
}
END_TEST

// START_TEST(credit_test_1) {
//   double res = 0.0;
//   double x = 0.2;
//   char input[] = "cos(10)+sin(10)+tan(20)";
//   double ans = 0.854068;
//   ck_assert_int_eq(calc(input, &res, x), 0);
//   ck_assert_double_eq(res, ans);
// }
// END_TEST

Suite *calc_suite(void) {
  TCase *tc = tcase_create("calc_core");
  Suite *s = suite_create("calc_tests");

  tcase_add_test(tc, calc_test_1);
  tcase_add_test(tc, calc_test_2);
  tcase_add_test(tc, calc_test_3);
  tcase_add_test(tc, calc_test_4);
  tcase_add_test(tc, calc_test_5);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int failed = 0;
  SRunner *sr;

  sr = srunner_create(calc_suite());
  //srunner_add_suite(sr, s21_credit_suite());
 

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed == 0) ? 1 : 0;
}
