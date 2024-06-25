#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int value;
    struct Node* next;
} node;

typedef struct{
    node* head;
    node* tail;
} queue;

node* newNode(int);
queue* newQueue(void);
void enqueue(queue**, int);
void dequeue(queue**);
void peek(queue*);

int main(void){
    srand(time(NULL));
    system("cls||clear");

    queue* idk = newQueue();
    peek(idk);

    printf("inserção:\n");

    for (int i = 0; i < 10; ++i){
        enqueue(&idk, rand() % 10);
        peek(idk);
    }

    printf("remoção:\n");
    for (int j = 0; j < 10; ++j){
        dequeue(&idk);
        peek(idk);
    }

    printf("\n");
    return 0;
}

node* newNode(int value){
    node* new = malloc(sizeof(node));
    new->value = value;
    new->next = NULL;
    return new;
}

queue* newQueue(void){
    queue* new = malloc(sizeof(queue));
    new->head = NULL;
    new->tail = NULL;
    return new;
}

void enqueue(queue** list, int value){
    node* new = newNode(value);
    if (!(*list)->head){
        (*list)->head = new;
        (*list)->tail = new;
        return;
    }
    (*list)->tail->next = new;
    (*list)->tail = new;
    return;
}

void dequeue(queue** list){
    if (!(*list)){
        return;
    }
    node* current = (*list)->head;
    (*list)->head = current->next;
    free(current);
    return;
}

void peek(queue* list){
    if (!list->head){
        printf("NULL\n");
        return;
    }

    if (list->head == list->tail){
        printf("%d ... NULL\n", list->head->value);
        return;
    }

    printf("%d ... %d\n", list->head->value, list->tail->value);
}