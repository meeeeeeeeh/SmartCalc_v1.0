#include <stdio.h>
#include <string.h>

typedef struct data_stack {
    double num;
    char op;
    struct stack *next;
}stack;

int invalid_expression(char *expr);
int is_num(char n);


int main() {
    char arr[100] = "1+2-6-1345.5+78";
    if (invalid_expression(arr)) printf("Invalid expression\n");


    char notation[255];
    char temp[255];
    int n = 0;
    int num_count = 0;
    int k = 0;

    for (int i = 0; i < (int)strlen(arr); ++i) {
        if (is_num(arr[i]) && num_count < 2) {
            num_count++;
            while (is_num(arr[i]) || arr[i] == '.') {
                notation[k] = arr[i];
                i++;
                k++;
            }
            notation[k] = ' ';
            k++;
            i--;
        }

        if (!is_num(arr[i]) && num_count < 2) {
            temp[n] = arr[i];
        }

        if (num_count == 2) {
            notation[k] = temp[n];
            n++;
            k++;
            notation[k] = ' ';
            k++;
            num_count = 1;
        }
        notation[k] = '\0';
    }
    
    printf("%s", notation);


    return 0;
}




int invalid_expression(char *expr) {
    int res = 0;
    int open_br = 0;
    int close_br = 0;

    for (int i = 0; i < (int)strlen(expr) && !res; ++i) {
        if (expr[i] == '/' && expr[i + 1] == '0') res = 1;
        if (!is_num(expr[i]) && expr[i] == expr[i + 1]) res = 1;
        if (expr[i] == '(') {
            if (is_num(expr[i - 1])) res = 1;
            else open_br++;
        } 
        if (expr[i] == ')') close_br++;
    }

    if (open_br != close_br) res = 1;

    return res;
}

int is_num(char n) {
    return n >= 48 && n <= 57 ? 1 : 0;
}