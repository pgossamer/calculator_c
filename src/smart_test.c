#include <check.h>
#include "smartCalc.h"

START_TEST(test_1) {
    char *str_st = "1+2/3";
    double result = _smart_calc(str_st, 0);
    long double res_og = 1.0+2.0/3.0;
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_2) {
    char *str_st = "2*(1.1234567/2+-21.1234567/2)";
    double result = _smart_calc(str_st, 0);
    long double res_og = 2.0*(1.1234567/2.0+-21.1234567/2.0);
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_3) {
    char *str_st = "47.22+-273.3+4^4/736.2--233*42-74/4.3+-0.987+24*(1+3)/-2";
    double result = _smart_calc(str_st, 0);
    long double res_og = 47.22+-273.3+pow(4.0, 4.0)/736.2-(-233.0)*42.0-74.0/4.3+-0.987+24.0*(1.0+3.0)/-2.0;
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_4) {
    char *str_st = "4^s(1)";
    double result = _smart_calc(str_st, 0);
    long double res_og = pow(4, sin(1));
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_5) {
    char *str_st = "-s(c(-2^2)*3)+6";
    double result = _smart_calc(str_st, 0);
    long double res_og = -sin(cos(pow(-2, 2))*3)+6;
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_6) {
    char *str_st = "-5--3-2++2-q(21)";
    double result = _smart_calc(str_st, 0);
    long double res_og = -5-(-3)-2+(+2)-sqrt(21);
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_7) {
    char *str_st = "t(n(2))";
    double result = _smart_calc(str_st, 0);
    long double res_og = tan(log(2));
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_8) {
    char *str_st = "#(0.2)*3-(12.21324*-3)";
    double result = _smart_calc(str_st, 0);
    double res_og = acos(0.2)*3.0-(12.21324*(-3.0));
    ck_assert_float_eq(result, res_og);
}
END_TEST
START_TEST(test_9) {
    char *str_st = "7m3+#(0.2)*3-(12.21324*-3)";
    double result = _smart_calc(str_st, 0);
    double res_og = fmod(7.0, 3.0)+acos(0.2)*3.0-(12.21324*(-3.0));
    ck_assert_float_eq(result, res_og);
}
END_TEST
START_TEST(test_10) {
    char *str_st = "!($(-0.22435))";
    double result = _smart_calc(str_st, 0);
    long double res_og = atan(asin(-0.22435));
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_11) {
    char *str_st = "g(2+2.21+-3)*(1.1234567/2+-21.1234567/2)";
    double result = _smart_calc(str_st, 0);
    long double res_og = log10(2.0+2.21+-3.0)*(1.1234567/2.0+-21.1234567/2.0);
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_12) {
    char *str_st = "-1--3*(-3)+5-4";
    double result = _smart_calc(str_st, 0);
    long double res_og = -1-(-3)*(-3)+5-4;
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_13) {
    char *str_st = "4^(8/4+3-2)";
    double result = _smart_calc(str_st, 0);
    long double res_og = pow(4, 8/4+3-2);
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_14) {
    char *str_st = "5m5";
    double result = _smart_calc(str_st, 0);
    long double res_og = fmod(5, 5);
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_15) {
    char *str_st = "3m(s(5))";
    double result = _smart_calc(str_st, 0);
    long double res_og = fmod(3, sin(5));
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_16) {
    char *str_st = "3.m(s(5))";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_17) {
    char *str_st = "3+-0.+s(2)";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_18) {
    char *str_st = "3)+6";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_19) {
    char *str_st = "/2-(4+3)+6";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_20) {
    char *str_st = "2-(4+3)+6+";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_21) {
    char *str_st = "2-(4+3";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_22) {
    char *str_st = "2-4+/3";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_23) {
    char *str_st = "2-4+(3+9.)";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_24) {
    char *str_st = "+3.9(4+9)";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_25) {
    char *str_st = "+3.9/(4+9).12.4";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_26) {
    char *str_st = "+3.9/(4+9/)+12.4";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_27) {
    char *str_st = "47.22+-273.3+4^4/736.2--233*42-74/4.3+-0.987+24*(1+3)/-2";
    int result = validation(str_st);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(test_28) {
    char *str_st = "-s(c(-2^2)*3)+6";
    int result = validation(str_st);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(test_29) {
    char *str_st = "3+x/7^2";
    int result = are_you_have_x(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_30) {
    char *str_st = "3+9/7^2";
    int result = are_you_have_x(str_st);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(test_31) {
    char *str_st = "4^x";
    double x = 2.4;
    double result = _smart_calc(str_st, x);
    long double res_og = pow(4, 2.4);
    ck_assert_double_eq(result, res_og);
}
END_TEST
START_TEST(test_32) {
    char *str_st = "3+x./7^2";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_33) {
    char *str_st = "47.22+-273.3+4^4/736.2--233*42-74/4.3+-0.987+24*(1+3)/-247.22+-273.3+4^4/736.2--233"
                "*42-74/4.3+-0.987+24*(1+3)/-247.22+-273.3+4^4/736.2-47.22+-273.3+4^4/736.2--233*42-74/4.3+"
                "-0.987+24*(1+3)/-2-233*42-74/4.3+-0.987+24*(1+3)/-247.22+-273.3+4^4/736.2--233*42-7";
    int result = len_str(str_st);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(test_34) {
    char *str_st = "47.22+-273.3+4^4/736.2--233*42-74/4.3+-0.987+24*(1+3)/-247.22+-273.3+4^4/736.2--233*42"
    "-74/4.3+-0.987+24*(1+3)/-247.22+-273.3+4^4/736.2-47.22+-273.3+4^4/736.2--233*42-74/4.3+-0.987+24*(1+3)"
    "/-2-233*42-74/4.3+-0.987+24*(1+3)/-247.22+-273.3+4^4/736.2--233*42";
    int result = len_str(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(test_35) {
    char *str_st = "2.5e(4+3)+6";
    int result = validation(str_st);
    ck_assert_int_eq(result, 1);
}
END_TEST



int main() {
    Suite *s1 = suite_create("Suite");
    SRunner *sr = srunner_create(s1);
    int nf;

    TCase *tc1_1 = tcase_create("tests");
    suite_add_tcase(s1, tc1_1);

    tcase_add_test(tc1_1, test_1);
    tcase_add_test(tc1_1, test_2);
    tcase_add_test(tc1_1, test_3);
    tcase_add_test(tc1_1, test_4);
    tcase_add_test(tc1_1, test_5);
    tcase_add_test(tc1_1, test_6);
    tcase_add_test(tc1_1, test_7);
    tcase_add_test(tc1_1, test_8);
    tcase_add_test(tc1_1, test_9);
    tcase_add_test(tc1_1, test_10);
    tcase_add_test(tc1_1, test_11);
    tcase_add_test(tc1_1, test_12);
    tcase_add_test(tc1_1, test_13);
    tcase_add_test(tc1_1, test_14);
    tcase_add_test(tc1_1, test_15);
    tcase_add_test(tc1_1, test_16);
    tcase_add_test(tc1_1, test_17);
    tcase_add_test(tc1_1, test_18);
    tcase_add_test(tc1_1, test_19);
    tcase_add_test(tc1_1, test_20);
    tcase_add_test(tc1_1, test_21);
    tcase_add_test(tc1_1, test_22);
    tcase_add_test(tc1_1, test_23);
    tcase_add_test(tc1_1, test_24);
    tcase_add_test(tc1_1, test_25);
    tcase_add_test(tc1_1, test_26);
    tcase_add_test(tc1_1, test_27);
    tcase_add_test(tc1_1, test_28);
    tcase_add_test(tc1_1, test_29);
    tcase_add_test(tc1_1, test_30);
    tcase_add_test(tc1_1, test_31);
    tcase_add_test(tc1_1, test_32);
    tcase_add_test(tc1_1, test_33);
    tcase_add_test(tc1_1, test_34);
    tcase_add_test(tc1_1, test_35);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
