#include "calc.h"

void print(Node * list) {
    for (Node * p = list; p != NULL; p = p->next) {
        if(p->is_num) printf("%f ", p->num);
        else printf("'%c' ", p->op);
    }
    printf("\n\n");
}

// добавляет узел
void push(Node ** plist, double n, int is_num, char op) { // 1 арг - указатель на указатель последнего элемента
    Node * p = malloc(sizeof(Node));

    if(is_num) {
        p->num = n;
        p->is_num = 1;
    }
    else {
        p->is_num = 0;
        p->op = op;
        p->priority = define_priority(op);
    }
    p->next = *plist; // разыменование plist
    *plist = p;
}

// вытаскивает один узел из стека и записывает то что там было либо в num либо в op
int pop(Node ** plist, double *num, char *op) {
    int error = 0;
    if (is_empty(*plist)) error = 1;
    else {
        Node * p = *plist;
        if(p->is_num) {
            *num = p->num;
        }
        else {
            *op = p->op;
        }
        *plist = p->next;
        free(p);
    }

    return error;
}

int is_empty(Node *list) {
    return list == NULL ? 1 : 0;
}

int is_num(char n) {
    return n >= 48 && n <= 57 ? 1 : 0;
}

// если такого оператора нет, вместо приоритета вернет -1
int define_priority(char op) {
    int prior = -1;

    if (op == '(' || op == ')') prior = 0;
    else if (op == '-' || op == '+') prior = 1;
    else if (op == '*' || op == '/' || op == 'm') prior = 2;
    else if (op == '^' || op == 'q' ) prior = 3;
    else if (strchr("cstCSTLl", op) != NULL) prior = 4;

    return prior;
}

double calculate(double num1, double num2, char op) {
    double res = 0.0;

    if (op == '+') res = num1 + num2;
    else if (op == '-') res = num1 - num2;
    else if (op == '*') res = num1 * num2;
    else if (op == '/') res = num1 / num2;
    else if (op == '^') res = pow(num1, num2);
    else if (op == 'm') res = fmod(num1, num2); // m == mod(x) остаток от деления
    else if (op == 'q') res = sqrt(num1); // q == sqrt(x) - квадратный корень,
    else if (op == 'c') res = cos(num1);
    else if (op == 's') res = sin(num1);
    else if (op == 't') res = tan(num1);
    else if (op == 'C') res = acos(num1);
    else if (op == 'S') res = asin(num1);
    else if (op == 'T') res = atan(num1);
    else if (op == 'L') res = log(num1); // L - ln(x) - натуральный логарифм
    else if (op == 'l') res = log10(num1); //l - log(x) - десятичный логарифм

    return res;
}

// присвоить оператору нужый символ и изменить индекс
char check_op(char ch1, char ch2, size_t *index) {
    char res = ch1;
    if (ch1 == 'm' || ch1 == 'c' || ch1 == 't' || (ch1 == 's' && ch2 == 'i') || (ch1 == 'l' && ch2 == 'o')) {
        *(index) += 2;
    }
    else if ((ch1 == 's' && ch2 == 'q') || ch1 == 'a') {
        if (ch1 == 'a') res = ch2 - 32;
        else res = 'q';
        *(index) += 3;
    }
    else if (ch1 == 'l' && ch2 == 'n') {
        res = ch2 - 32;
        *(index) += 1;
    }
    return res;
}

void reverse_stack(Node **plist) {
    Node * reversed = NULL;
    while (!is_empty(*plist)) {
        char op;
        double res;
        if(!(*plist)->is_num) {
            pop(plist, &res, &op);
            push(&reversed, 0.0, 0, op);
        }
        else {
            pop(plist, &res, &op);
            push(&reversed, res, 1, op);
        }
    }
    *plist = reversed;
}


int main() {
    Node * notation = NULL;
    Node * stack_tmp = NULL;
    char buffer[255] = "\0";
    int k = 0;
    double num = 0;
    //char test[] = "6+3*(1+4*5)*2";
    //char test[] = "5+15mod10*2";
    //char test[] = "1+2^3+(4+7(1-8)*2)";
    //char test[] = "10^2";
    //char test[] = "5+cos(2*4+2)";
    char test[] = "atan(5)-sin(2+8)";

    for (size_t i = 0; i < (sizeof(test)/ sizeof(test[0]) - 1); i++) {
        if (is_num(test[i])) {
            do {
                buffer[k] = test[i];
                k++;
                i++;
            } while (is_num(test[i]) || test[i] == '.');
            buffer[k] = '\0';
            num = atof(buffer);
            i--;
            k = 0;
            push(&notation, num, 1, 0);
        }
        else {
            char op = 0;
            double res;

            if(test[i] == ')') {
                while (op != '('){
                    pop(&stack_tmp, &res, &op);
                    if (op != '(') push(&notation, 0.0, 0, op);
                }
            }
            else if(test[i] == '(') {
                push(&stack_tmp, 0.0, 0, test[i]);
            }
            else {
                while (!is_empty(stack_tmp) && stack_tmp->priority >= define_priority(test[i])) {       // если у нового элемента приоритет меньше все выталкиается
                    pop(&stack_tmp, &res, &op);
                    push(&notation, 0.0, 0, op);
                }

                push(&stack_tmp, 0.0, 0, check_op(test[i], test[i+1], &i));

            }
        }
        //print(notation);
    }

    while (!is_empty(stack_tmp)) {
        char op;
        double res;
        pop(&stack_tmp, &res, &op);
        push(&notation, 0.0, 0, op);
    }

    printf("stack: ");
    print(notation);
    reverse_stack(&notation);

    printf("notation: ");
    print(notation);

    Node * calc = NULL;
    int last = 0;

    while (!last) {
        char op = 0;
        double num1 = 0.0, num2 = 0.0, num = 0.0;
        if(notation->is_num) {
            pop(&notation, &num, &op);
            push(&calc, num, 1, op);
        }
        else {
            pop(&notation, &num, &op);
            if (strchr("cstqCSTLl", op) == NULL) { // если опеатор не унарный то дбавляется второй оперант
                pop(&calc, &num2, &op);
            }

            pop(&calc, &num1, &op);
            if(is_empty(notation)) last = 1;

            //printf("num1 - %f, num2 - %f, op - '%c', last - %d", num1, num2, op, last);
            push(&calc, calculate(num1, num2, op), 1, op);
        }
        // printf("\n");
        // printf("notation: ");
        // print(notation);

        // printf("calc: ");
        // print(calc);
        // printf("\n");

    }

    printf("calc: ");
    print(calc);

    return 0;
}
