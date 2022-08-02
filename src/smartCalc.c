#include "smartCalc.h"

double _smart_calc(char *str_st, double x) {
  Stack_f *list = NULL;
  Stack_c *list_chisel = NULL;
  char sym;
  int i = 0, previous = OPERATOR;
  int have_x = are_you_have_x(str_st);
  while ((sym = str_st[i]) != '\0') {
    if (isdigit(sym)) {
      push_dbl(&list_chisel, strtod(str_st + i, &str_st));
      i = 0;
      previous = NUMBER;
      continue;
    } else if (strchr("+-*/()^m", sym)) {
      if (sym == '(') {
        push_char(&list, sym);
        previous = OPERATOR;
        i++;
        continue;
      }
      if (sym == ')') {
        while (peek(list) != '(') {
          math_for_two_way(&list, &list_chisel);
        }
        pop_char(&list);
        i++;
        previous = NUMBER;
        continue;
      }
      if ((sym == '-' && list_chisel == NULL) ||
          (sym == '-' && list != NULL && previous == OPERATOR)) {
        push_char(&list, '*');
        push_dbl(&list_chisel, -1.0);
        i++;
        continue;
      }
      if ((sym == '+' && list_chisel == NULL) ||
          (sym == '+' && list != NULL && previous == OPERATOR)) {
        i++;
        continue;
      }
      if (list != NULL && priority(sym) <= priority(peek(list)) &&
          !(strchr("sqct#$ng!(", peek(list)))) {
        double a = pop_dbl(&list_chisel);
        double b = pop_dbl(&list_chisel);
        calculate(b, a, pop_char(&list), &list_chisel);

        end_calc(&list_chisel, &list, sym);
      } else if (list && (strchr("sqct#$ng!", peek(list)))) {
        long_calculate(pop_dbl(&list_chisel), pop_char(&list), &list_chisel);
        end_calc(&list_chisel, &list, sym);
      } else {
        push_char(&list, sym);
      }
      previous = OPERATOR;
    } else if (strchr("sqct#$ng!", sym)) {
      push_char(&list, sym);
    } else if (sym == 'x' && have_x) {
      push_dbl(&list_chisel, x);
      previous = NUMBER;
      i++;
      continue;
    }
    i++;
  }
  while (list) {
    math_for_two_way(&list, &list_chisel);
  }
  double result = pop_dbl(&list_chisel);
  return result;
}

char peek(Stack_f *function) { return function->oper; }
void push_char(Stack_f **function, char n) {
  Stack_f *buf = malloc(sizeof(Stack_c));
  buf->next = *function;
  buf->oper = n;
  *function = buf;
}
char pop_char(Stack_f **function) {
  char n;
  Stack_f *buf;
  buf = *function;
  *function = (*function)->next;
  n = buf->oper;
  free(buf);
  return n;
}

void push_dbl(Stack_c **chisla, double n) {
  Stack_c *buf = malloc(sizeof(Stack_c));
  buf->next = *chisla;
  buf->chsl = n;
  *chisla = buf;
}
double pop_dbl(Stack_c **chisla) {
  double n = 0.0;
  Stack_c *buf;
  buf = *chisla;
  *chisla = (*chisla)->next;
  n = buf->chsl;
  free(buf);
  return n;
}

int priority(char n) {
  int prior = 0;
  if (n == '+' || n == '-') {
    prior = 1;
  }
  if (n == '*' || n == '/' || n == 'm') {
    prior = 2;
  }
  if (n == '^') {
    prior = 3;
  }
  if (strchr("sqct#$ng!", n)) {
    prior = 4;
  }
  return prior;
}

void calculate(double a, double b, char symbol, Stack_c **chisla) {
  long double n = 0.0;
  if (symbol == '+') {
    n = a + b;
  } else if (symbol == '-' || symbol == '!') {
    n = a - b;
  } else if (symbol == '*') {
    n = a * b;
  } else if (symbol == '/') {
    n = a / b;
  } else if (symbol == '^') {
    n = pow(a, b);
  } else if (symbol == 'm') {
    n = fmod(a, b);
  }
  push_dbl(chisla, n);
}

void long_calculate(double a, char symbol, Stack_c **chisla) {
  double n = 0.0;
  if (symbol == 's') {
    n = sin(a);
  } else if (symbol == 'q') {
    n = sqrt(a);
  } else if (symbol == 'c') {
    n = cos(a);
  } else if (symbol == 't') {
    n = tan(a);
  } else if (symbol == '#') {
    n = acos(a);
  } else if (symbol == '$') {
    n = asin(a);
  } else if (symbol == '!') {
    n = atan(a);
  } else if (symbol == 'n') {
    n = log(a);
  } else if (symbol == 'g') {
    n = log10(a);
  }
  push_dbl(chisla, n);
}

void end_calc(Stack_c **list_chisel, Stack_f **list, char sym) {
  if (*list != NULL && (priority(sym) <= priority(peek(*list)))) {
    double a = pop_dbl(list_chisel);
    double b = pop_dbl(list_chisel);
    calculate(b, a, pop_char(list), list_chisel);
  }
  push_char(list, sym);
}

void math_for_two_way(Stack_f **list, Stack_c **list_chisel) {
  if (!(strchr("sqct#$ng!", peek(*list)))) {
    double a = pop_dbl(list_chisel);
    double b = pop_dbl(list_chisel);
    calculate(b, a, pop_char(list), list_chisel);
  } else {
    long_calculate(pop_dbl(list_chisel), pop_char(list), list_chisel);
  }
}

int validation(char *str) {
  int flag_for_brackets = 0, flag_error = 0;
  if (strchr(".*/m^", str[0])) {
    flag_error++;
  }
  if (strchr(".*/m^+-", str[strlen(str) - 1])) {
    flag_error++;
  }
  for (size_t i = 0; i < strlen(str) && !flag_error; i++) {
    if (str[i] == '(') {
      flag_for_brackets++;
    }
    if (str[i] == ')') {
      flag_for_brackets--;
    }
    if (flag_for_brackets < 0) {
      flag_error++;
      break;
    }
    if (i + 1 < strlen(str)) {
      if ((strchr("+-/*me", str[i]) || strchr("^(", str[i])) &&
          strchr("*/^e.m)", str[i + 1])) {
        flag_error++;
        break;
      }
      if (str[i] == '.' && strchr("+-/*^()m.xsqct#$!ng", str[i + 1])) {
        flag_error++;
        break;
      }
      if (isdigit(str[i]) && (strchr("(", str[i + 1]) || str[i + 1] == 'x')) {
        flag_error++;
        break;
      }
      if (strchr(")", str[i]) &&
          ((isdigit(str[i + 1])) || (strchr(".(stc#$!ngqx", str[i + 1])))) {
        flag_error++;
        break;
      }
      if (str[i] == 'x' &&
          (strchr("(.esctq#$!ngx", str[i + 1]) || isdigit(str[i + 1]))) {
        flag_error++;
        break;
      }
      if (str[i] == 'e' && strchr("*/^(.esctq#$!ngxm", str[i + 1])) {
        flag_error++;
        break;
      }
    }
  }
  if (flag_for_brackets != 0) flag_error++;

  return flag_error ? 1 : 0;
}

int are_you_have_x(char *str) {
  int flag = 0;
  for (size_t i = 0; i < strlen(str); i++) {
    if (str[i] == 'x') flag = 1;
  }
  return flag;
}

int len_str(char *str) { return strlen(str) < 256 ? 1 : 0; }
