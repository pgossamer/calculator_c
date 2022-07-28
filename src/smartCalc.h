#ifndef SRC_SMARTCALC_H_
#define SRC_SMARTCALC_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPERATOR 0
#define NUMBER 1

typedef struct chisla {
  double chsl;
  struct chisla *next;
} Stack_c;

typedef struct function {
  char oper;
  struct function *next;
} Stack_f;

double s21_smart_calc(char *str_st, double x);

void end_calc(Stack_c **list_chisel, Stack_f **list, char sym);
void math_for_two_way(Stack_f **list, Stack_c **list_chisel);
void calculate(double a, double b, char symbol, Stack_c **chisla);
void long_calculate(double a, char symbol, Stack_c **chisla);

void print_chisel(Stack_c *chisla);
void print_oper(Stack_f *function);
void push_dbl(Stack_c **chisla, double n);
double pop_dbl(Stack_c **chisla);
void push_char(Stack_f **function, char n);
char pop_char(Stack_f **function);
int priority(char n);
char peek(Stack_f *function);

int validation(char *str);
int are_you_have_x(char *str);
int len_str(char *str);

#endif  // !SRC_SMARTCALC_H_
