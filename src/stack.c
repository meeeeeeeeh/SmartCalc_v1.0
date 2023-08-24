#include <stdio.h>
#include <stdlib.h>

// односвязный список

typedef int Data;
typedef struct Node Node;
struct Node {
    Data data; // 1 число ы 1 узле
    struct Node * next; // указатель на след элемент
};

void print(Node * list);
void push(Node ** plist, Data d);


void print(Node * list) {
    for (Node * p = list; p != NULL; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}

void push(Node ** plist, Data d) { // 1 арг - указатель на указатель последнего элемента
    Node * p = malloc(sizeof(Node));
    p->data = d;
    p->next = *plist; // разыменование plist
    *plist = p;
}


int main() {
    Data test[] = {21, 17, 3, 10};
    Node * list = NULL;

    for (size_t i = 0; i < sizeof(test)/ sizeof(test[0]); i++) {
        push(&list, test[i]); // передаем указатель потому что переменная будет меняться
        print(list);
    }

    return 0;
}