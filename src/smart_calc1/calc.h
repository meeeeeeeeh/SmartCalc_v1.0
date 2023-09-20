#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Node Node;
struct Node {
    int priority;
    char op;
    double num;
    int is_num;
    struct Node * next;
};

void print(Node * list);
void push(Node ** plist, double n, int is_num, char op);
int is_empty(Node *list);
void delete_stack(Node ** plist);
int pop(Node ** plist, double *num, char *op);
int is_num(char n);
int define_priority(char op);
double operations(double num1, double num2, char op, int *error);
void reverse_stack(Node **plist);
char check_op(char ch1, char ch2, int *index);
void fill_notation(Node **notation, Node **tmp, int *er);
double calc_result(Node ** notation, int *error);
void convert_to_notation(Node ** notation, Node ** stack_tmp, char *input, int len, int *error, double x);
int calc(char *input, double *result, double x);
void check_num(char *input, int *index, int *error, double *num);
void credit_calc(double sum, int months, double rate, double *monthly, double *percents, double *all, int mode);

#endif
