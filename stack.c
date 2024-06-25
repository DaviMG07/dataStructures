#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int value;
    struct Node* next;
} node;

node* newNode(int);
void peek(node*);
node* getop(node**);
void push(node**, int);

int main(void){
    srand(time(NULL));
    system("cls||clear");

    node* top = NULL;
    peek(top);
    push(&top, 10);
    peek(top);
    push(&top, 11);
    peek(top);
    free(getop(&top));
    peek(top);

    printf("\n");
    return 0;
}

node* newNode(int value){
    node* new = malloc(sizeof(node));
    new->value = value;
    new->next = NULL;
    return new;
}

void peek(node* top){
    if (!top){
        printf("NULL\n");
        return;
    }
    printf("%d\n", top->value);
}

node* getop(node** top){
    if (!(*top)){
        return NULL;
    }
    node* current = *top;
    *top = (*top)->next;
    return current;
}

void push(node** top, int value){
    node* new = newNode(value);
    if (!(*top)){
        *top = new;
        return;
    }
    new->next = *top;
    *top = new;
    return;
}