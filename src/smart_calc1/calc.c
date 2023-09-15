#include "calc.h"

// переделать мейн
// если результат будет переполнять дабл???
// добавить х в код!!!


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

// вытаскивает один узел из стека и записывает то что там было либо в num либо в op, если доставать уже нечего - 1
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

void delete_stack(Node ** plist) {
   while(!is_empty(*plist)) {
        Node * p = *plist;
        *plist = p->next;
        free(p);
    }
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

double operations(double num1, double num2, char op) {
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
char check_op(char ch1, char ch2, int *index) {
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
        char op = 0;
        double res = 0.0;
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

void fill_notation(Node **notation, Node **tmp, int *er) {
    while (!is_empty(*tmp) && !(*er)) {
        char op = 0;
        double res = 0.0;

        pop(tmp, &res, &op);
        if (op == '(' || op == ')') *er = 1; // если во временном стеке осталась хоть одна скобка то ввод не корректен
        else push(notation, 0.0, 0, op);
    }
}

double calc_result(Node ** notation, int *error) {
    Node * calc = NULL;
    int last = 0;
    double res = 0.0;

    while (!last && !(*error)) {
        char op = 0;
        double num1 = 0.0, num2 = 0.0, num = 0.0;

        pop(notation, &num, &op);


        if(op == 0) {
            //pop(notation, &num, &op);
            push(&calc, num, 1, op);
        }
        else {
            //pop(notation, &num, &op);
            if (strchr("cstqCSTLl", op) == NULL) { // если опеатор не унарный то добавляется второй оперант
                if(pop(&calc, &num2, &op)) *error = 1; // ошибка в записи нотации, некорректный ввод
            }
            if (!(*error)) {
                if (pop(&calc, &num1, &op)) *error = 1; // ошибка в записи нотации, некорректный ввод
                else {
                    res = operations(num1, num2, op);
                    if(is_empty(*notation)) last = 1;
                    else push(&calc, res, 1, op);
                }
            }
        }
    }
    delete_stack(&calc);
    return res;
}

void check_num(char *input, int *index, int *error, double *num) {
    char buffer[255] = "\0";
    int k = 0;
    int dot = 0;

    do {
        if (dot && input[*index] == '.') *error = 1;
        else {
            if (input[*index] == '.') dot = 1;
            buffer[k] = input[*index];
            k++;
            (*index)++;
        }
    } while ((is_num(input[*index]) || input[*index] == '.') && !(*error));

    buffer[k] = '\0';
    if(buffer[0] == '.' || buffer[k-1] == '.') *error = 1;
    else {
        *num = atof(buffer);
        (*index)--;
    }
}

void convert_to_notation(Node ** notation, Node ** stack_tmp, char *input, int len, int *error, double x) {
    char op = 0;
    double res = 0.0;
    double num = 0;

    if (input[0] == '-' || input[0] == '+') push(notation, 0.0, 1, 0); // унарные знаки вначале строки
    for (int i = 0; i < len && !(*error); i++) {
        if (input[i] == 'x') {
            push(notation, x, 1, 0);
        }
        else if (is_num(input[i]) || input[i] == '.') {
            check_num(input, &i, error, &num);
            if (!(*error)) push(notation, num, 1, 0);
        }
        else {
            op = 0;
            res = 0.0;

            if(input[i] == ')') {
                while (op != '(' && !(*error)) {
                    *error = pop(stack_tmp, &res, &op); // если закрывающей нет соотв открывающей - ошибка        
                    if (op != '(' && !(*error)) push(notation, 0.0, 0, op);
                }
            }
            else if(input[i] == '(') {
                push(stack_tmp, 0.0, 0, input[i]);
                if (input[i+1] == '-' || input[i+1] == '+') push(notation, 0.0, 1, 0); // унарные знаки не вначале строки
            }
            else {
                while (!is_empty(*stack_tmp) && (*stack_tmp)->priority >= define_priority(input[i])) {// если у нового элемента приоритет меньше все выталкиается
                    pop(stack_tmp, &res, &op);
                    push(notation, 0.0, 0, op);
                }
                push(stack_tmp, 0.0, 0, check_op(input[i], input[i+1], &i));

            }
        }
    }
    fill_notation(notation, stack_tmp, error); // добавляет оставшиеся операторы из временного стека к нотации
}

int calc(char *input, double *result, double x) {
    Node * notation = NULL;
    Node * stack_tmp = NULL;
    int error = 0;
    int len = (int)strlen(input);
    error = len <= 255 ? 0 : 2; // ошибка переполнения

    if (error != 2) {
        convert_to_notation(&notation, &stack_tmp, input, len, &error, x);
        if (!error) {
            reverse_stack(&notation); // переворачивает стек
            print(notation);
            *result = calc_result(&notation, &error);
        }
        delete_stack(&notation);
        delete_stack(&stack_tmp);
    }
    return error;
}

int main() {
    double res = 0;
    double x = 8;
    char arr[] = "x+6*sqrt(78)+sin(30^5)-x";
    printf("%d\n", calc(arr, &res, x));
    printf("%f", res);
    return 0;
}
