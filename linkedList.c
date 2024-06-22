#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int value;
    struct Node* next;
} node;

typedef struct{
    int size;
    node* head;
    node* tail;
} llist;

node* newNode(int);
llist* newLlist(void);

void append(llist*, int);//insert at the end
void push(llist*, int);//insert at beginning
void insert(llist*, int, int);//insert anywhere
void delete(llist*, int);//search the value and delete
int pop(llist*, int);//go to position, delete and return the value of deleted node
int search(llist*, int);//search value and return position
void printLlist(llist);




int main(void){
    srand(time(NULL));
    system("cls||clear");

    llist* list = newLlist();

    for (int i = 0; i < 10; ++i){
        printf("position: %d\nvalue: %d\n", i-2, i);
        insert(list, i-2, i);
        printLlist(*list);
    }
    printLlist(*list);

    printf("\n");
    return 0;
}




node* newNode(int value){
    node* new = malloc(sizeof(node));
    new->value = value;
    new->next = NULL;
    return new;
}

llist* newLlist(void){
    llist* new = malloc(sizeof(llist));
    new->head = NULL;
    new->tail = NULL;
    new->size = 0;
    return new;
}

void append(llist* list, int value){
    node* new = newNode(value);
    ++list->size;
    if (!(list->head)){
        list->head = new;
        list->tail = new;
        return;
    }
    list->tail->next = new;
    list->tail = new;
    return;
}

void push(llist* list, int value){
    node* new = newNode(value);
    ++list->size;
    if (!(list->head)){
        list->head = new;
        list->tail = new;
        return;
    }
    new->next = list->head;
    list->head = new;
    return;
}

void insert(llist* list, int position, int value){
    if (position >= list->size - 1){
        append(list, value);
        return;
    }
    if (position <= 0){
        push(list, value);
        return;
    }
    node* new = newNode(value);
    ++list->size;
    if (!(list->head)){
        list->head = new;
        list->tail = new;
        return;
    }

    node* current = list->head;
    int i = 0;
    while (i < position - 1 && current->next){
        current = current->next;
        ++i;
    }
    new->next = current->next;
    current->next = new;
    return;
}

void printLlist(llist list){
    printf("size: %d\n", list.size);
    printf("NULL -> ");
    for (int i = 0; i < list.size; ++i){
        printf("%d -> ", list.head->value);
        list.head = list.head->next;
    }
    printf("NULL\n");
}