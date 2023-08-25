#include <stdio.h>
#include <stdlib.h>

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
//Data pop(Node ** plist);
int is_num(char n);


void print(Node * list) {
    for (Node * p = list; p != NULL; p = p->next) {
        if(p->is_num) printf("%f ", p->num);
        else printf("%c ", p->op);
    }
    printf("\n");
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
    }
    p->next = *plist; // разыменование plist
    *plist = p;
}

int pop(Node ** plist, double *num, char *op, int *prior) {
    int error = 0;
    if (is_empty) error = 1;
    else {
        Node * p = *plist;
        if(p->is_num) {
            *num = p->num;
        }
        else {
            *op = p->op;
            *prior = p->priority;
        }
        *plist = p->next;
        free(p);  
    }
    
    return error;
}

int is_empty(Node *list) {
    return list == NULL;
}

int is_num(char n) {
    return n >= 48 && n <= 57 ? 1 : 0;
}


int main() {
    char test[20] = "25.3+17-18";
    char buffer[255] = "\0";
    int k = 0;
    double num;
    Node * notation = NULL;

    for (size_t i = 0; i < sizeof(test)/ sizeof(test[0]); i++) {
        if (is_num(test[i])) {
            while (is_num(test[i]) || test[i] == '.') {
                buffer[k] = test[i];
                k++;
                i++;
            }
            buffer[k] = '\0';
            k = 0;
            num = atof(buffer);

            push(&notation, num, 1, 0);

            print(notation);
        }
        else {
            push(&notation, 0.0, 0, test[i]);

            print(notation);
        }
        
        
    }


//    Data test[] = {21, 17, 3, 10};
//    Node * list = NULL;
//    printf("Empty: %s\n", is_empty(list) ? "YES" : "NO");
//
//    for (size_t i = 0; i < sizeof(test)/ sizeof(test[0]); i++) {
//        push(&list, test[i]); // передаем указатель потому что переменная будет меняться
//        print(list);
//    }
//    printf("Empty: %s\n", is_empty(list) ? "YES" : "NO");
//
//    while(!is_empty(list)) {
//        Data d = pop(&list); // амперсант тк лист будет меняться
//        printf("pop %d: ", d);
//        print(list);
//    }
//    printf("Empty: %s\n", is_empty(list) ? "YES" : "NO");

    return 0;
}
