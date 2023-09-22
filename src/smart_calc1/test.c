#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "calc.h"

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
  char input[] = "40+9-8/0";
  ck_assert_int_eq(calc(input, &res, x), 1);
}
END_TEST

START_TEST(calc_test_6) {
  double res = 0.0;
  double x = 0.2;
  char input[] = "-56";
  double ans = -56.0;
  ck_assert_int_eq(calc(input, &res, x), 0);
  ck_assert_double_eq_tol(res, ans, 0.000001);
}
END_TEST

START_TEST(calc_test_7) {
  double res = 0.0;
  double x = 0.2;
  char input[] = "5+((((-7))))";
  double ans = -2.0;
  ck_assert_int_eq(calc(input, &res, x), 0);
  ck_assert_double_eq_tol(res, ans, 0.000001);
}
END_TEST

START_TEST(calc_test_8) {
  double res = 0.0;
  double x = 0.2;
  char input[] = "1000^1000";
  ck_assert_int_eq(calc(input, &res, x), 0);
  ck_assert_double_infinite(res);
}
END_TEST

START_TEST(calc_test_9) {
  double res = 0.0;
  double x = 0.2;
  char input[] = ".99.";
  ck_assert_int_eq(calc(input, &res, x), 1);
}
END_TEST

START_TEST(calc_test_10) {
  double res = 0.0;
  double x = 0.2;
  char input[] = "12mod10+ln(2)+log(10)";
  double ans = 3.693147;
  ck_assert_int_eq(calc(input, &res, x), 0);
  ck_assert_double_eq_tol(res, ans, 0.000001);
}
END_TEST

START_TEST(calc_test_11) {
  double res = 0.0;
  double x = 0.2;
  char input[] = "2^(3^2)";
  double ans = 512.0;
  ck_assert_int_eq(calc(input, &res, x), 0);
  ck_assert_double_eq_tol(res, ans, 0.000001);
}
END_TEST

START_TEST(credit_test_1) {
  double sum = 5000.0;
  int months = 5;
  double rate = 10.0;
  double monthly_max = 0;
  double monthly_min = 0;
  double percents = 0;
  double all = 0;
  int mode = 1;

  credit_calc(sum, months, rate, &monthly_max, &monthly_min, &percents, &all,
              mode);

  double monthly_max_ans = 1025.138309;
  double monthly_min_ans = 0;
  double percents_ans = 125.691546;
  double all_ans = 5125.691546;

  ck_assert_double_eq_tol(monthly_max, monthly_max_ans, 0.000001);
  ck_assert_double_eq_tol(monthly_min, monthly_min_ans, 0.000001);
  ck_assert_double_eq_tol(percents, percents_ans, 0.000001);
  ck_assert_double_eq_tol(all, all_ans, 0.000001);
}
END_TEST

START_TEST(credit_test_2) {
  double sum = 15000.0;
  int months = 5;
  double rate = 5.0;
  double monthly_max = 0;
  double monthly_min = 0;
  double percents = 0;
  double all = 0;
  int mode = 2;

  credit_calc(sum, months, rate, &monthly_max, &monthly_min, &percents, &all,
              mode);

  double monthly_max_ans = 3062.500000;
  double monthly_min_ans = 3012.500000;
  double percents_ans = 187.500000;
  double all_ans = 15187.500000;

  ck_assert_double_eq_tol(monthly_max, monthly_max_ans, 0.000001);
  ck_assert_double_eq_tol(monthly_min, monthly_min_ans, 0.000001);
  ck_assert_double_eq_tol(percents, percents_ans, 0.000001);
  ck_assert_double_eq_tol(all, all_ans, 0.000001);
}
END_TEST

Suite *credit_suite(void) {
  TCase *tc = tcase_create("credit_core");
  Suite *s = suite_create("credit_tests");

  tcase_add_test(tc, credit_test_1);
  tcase_add_test(tc, credit_test_2);

  suite_add_tcase(s, tc);
  return s;
}

Suite *calc_suite(void) {
  TCase *tc = tcase_create("calc_core");
  Suite *s = suite_create("calc_tests");

  tcase_add_test(tc, calc_test_1);
  tcase_add_test(tc, calc_test_2);
  tcase_add_test(tc, calc_test_3);
  tcase_add_test(tc, calc_test_4);
  tcase_add_test(tc, calc_test_5);
  tcase_add_test(tc, calc_test_6);
  tcase_add_test(tc, calc_test_7);
  tcase_add_test(tc, calc_test_8);
  tcase_add_test(tc, calc_test_9);
  tcase_add_test(tc, calc_test_10);
  tcase_add_test(tc, calc_test_11);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int failed = 0;
  SRunner *sr;

  sr = srunner_create(calc_suite());
  srunner_add_suite(sr, credit_suite());

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed == 0) ? 1 : 0;
}
