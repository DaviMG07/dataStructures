#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int value;
    int priority;
    struct Node* next;
} node;

node* newNode(int, int);
void enqueue(node**, int, int);
void dequeue(node**);
void printPQ(node*);






int main(void){
    srand(time(NULL));
    system("cls||clear");

    node* head = NULL;

    for (int i = 0; i < 10; ++i){
        enqueue(&head, rand() % 100, rand() % 3);
        printPQ(head);
    }
    for (int j = 0; j < 10; ++j){
        dequeue(&head);
        printPQ(head);
    }

    printf("\n");
    return 0;
}






node* newNode(int value, int priority){
    node* new = malloc(sizeof(node));
    new->value = value;
    new->priority = priority;
    new->next = NULL;
    return new;
}

void enqueue(node** head, int value, int priority){
    node* new = newNode(value, priority);
    if (!(*head)){
        printf("caso 1\n");
        *head = new;
        return;
    }
    if (priority > (*head)->priority){
        printf("caso 2\n");
        new->next = *head;
        *head = new;
        return;
    }
    node* current = *head;
    while (current->next && current->next->priority >= priority){
        current = current->next;
    }
    printf("caso 3\n");
    new->next = current->next;
    current->next = new;
}

void dequeue(node** head){
    if (!(*head)){
        return;
    }
    node* current = *head;
    *head = current->next;
    free(current);
}

void printPQ(node* head){
    printf("NULL -> ");
    while (head){
        printf("%d(%d) -> ", head->value, head->priority);
        head = head->next;
    }
    printf("NULL\n");
}