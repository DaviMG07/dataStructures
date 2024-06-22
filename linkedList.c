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

node* newNode(int);//return a new node
llist* newLlist(void);//return a new empty list

void append(llist*, int);//insert at the end
void push(llist*, int);//insert at beginning
void insert(llist*, int, int);//insert anywhere
void delete(llist*, int);//search the value and delete
void clear(llist*);//delete all nodes
node* pop(llist*, int);//go to position, delete and return the deleted node
int search(llist, int);//search value and return position
node* find(llist*, int);//search value and return node
node* getNode(llist*, int);//return node in given position
void printLlist(llist);//print all nodes in list
void printN(node*);//print the node content and the content of next node








int main(void){
    srand(time(NULL));
    system("cls||clear");

    llist* list = newLlist();

    for (int i = 0; i < 7; ++i){
        int x = i;//rand()%10;
        append(list, x);
    }

    printLlist(*list);

    printN(pop(list, 3));

    printLlist(*list);
    
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
    printf("NULL -> ");
    for (int i = 0; i < list.size; ++i){
        if (i % 5 == 0 && i) printf("\n");
        printf("%d(%d) -> ", list.head->value, i);
        list.head = list.head->next;
    }
    printf("NULL\n");
}

void printN(node* myNode){
    if (myNode) {
        printf("node: %d\nnext: ", myNode->value);
        if (!myNode->next){
            printf("NULL\n");
        } else {
            printf("%d\n", myNode->next->value);
        }
        return;
    }
    printf("node: NULL\n");

}

int search(llist list, int value){
    for (int i = 0; i < list.size; ++i){
        if (value == list.head->value) return i;
        list.head = list.head->next;
    }
    return -1;
}

node* find(llist* list, int value){
    node* current = list->head;
    for (int i = 0; i < list->size - 1; ++i){
        if (value == current->next->value) return current;
        if (current->next) current = current->next;
        else return NULL;
    }
    return NULL;
}
node* getNode(llist* list, int position){
    if (position < 0) {
        position = list->size - (abs(position) % list->size);
    } 
    if (position > list->size - 1){
        position = position % list->size;
    }
    if (position == 0){
        return list->head;
    }
    if (position == list->size - 1){
        return list->tail;
    }
    node* current = list->head;
    for (int i = 0; i < list->size - 1; ++i){
        if (i == position) return current;
        current = current->next;
    }
    return NULL;
}

void delete(llist* list, int value){
    if (!list->head) return;
    node* current = list->head;
    if (value == list->head->value) {
        --list->size;
        list->head = list->head->next;
        free(current);
        return;
    }
    while (current->next && current->next->value != value){
        current = current->next;
    }

    if (current == list->tail) return;
    node* toDelete = current->next;
    current->next = current->next->next;
    --list->size;
}

void clear(llist* list){
    node* current;
    for (int i = 0; i < list->size; ++i){
        current = list->head;
        list->head = list->head->next;
        free(current);
    }
    list->size = 0;
}

node* pop(llist* list, int position){
    if (!list->head) return NULL;
    node* target;
    if (position <= 0){
        target = list->head;
        list->head = list->head->next;
        --list->size;
        return target;
    }
    if (position >= list->size - 1){
        target = getNode(list, -2);
        node* toReturn = target->next;
        target->next = target->next;
        --list->size;
        return toReturn;
    }
    target = getNode(list, position - 1);
    node* toReturn = target->next;
    target->next = target->next->next;
    --list->size;
    return toReturn;
}