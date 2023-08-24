#include <stdio.h>
#include <stdlib.h>

// односвязный список

typedef int Data;
typedef struct Node Node;
struct Node {
    Data data; // 1 число ы 1 узле
    struct Node * next; // указатель на след элемент
};

void print(Node * list) {
    for (Node * p = list; p != NULL; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}


int main() {
    Node * list = NULL;
    Node a = {3}, b = {17}, c = {21}, t = {10};
    list = &a;
    a.next = &b;
    b.next = &c;
    c.next = NULL;

    print(list);

    return 0;
}