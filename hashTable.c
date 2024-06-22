#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int value;
    int status;// 1 occupied; 0 empty; -1 deleted
} cell;

typedef struct{
    cell* arr;
    int buckets;
    int growthRate;
    int size;
} table;

table* newTable(int);
table* reHash(table*);
int hashing(int, int);
table* insert(table*, int);
void printC(cell);
void printH(table);

int main(void){
    srand(time(NULL));
    system("cls||clear");

    table* tbl = newTable(4);
    insert(tbl, 10);
    insert(tbl, 11);
    insert(tbl, 12);
    printH(*tbl);

    printf("\n");
    return 0;
}

table* newTable(int size){
    table* new = malloc(sizeof(table));;
    new->size = size;
    new->arr = malloc(sizeof(cell) * size);
    new->buckets = 0;
    new->growthRate = 0.0;
    return new;
}

int hashing(int key, int size) {
    return key % size;
}

table* insert(table* table, int key){
    int original = key;
    int index = hashing(key, table->size);
    while (table->arr[index].status == 1){
        index = hashing(++key, table->size);
    }
    table->arr[index].value = original;
    table->arr[index].status = 1;
    ++table->buckets;
    table->growthRate = (float)table->buckets / (float)table->size;
    if (table->growthRate > 0.75) return reHash(table);
    return table;
}

table* reHash(table* myTable){
    table* new = malloc(sizeof(table));
    new->size = myTable->size * 2;
    new->arr = malloc(sizeof(cell) * new->size);
    new->buckets = myTable->buckets;
    new->growthRate = (float)new->buckets / (float)new->size;

    free(myTable->arr);
    myTable->arr = NULL;
    free(myTable);
    myTable = NULL;

    return new;
}

void printC(cell cell){
    printf("%d(%d)", cell.value, cell.status);
}

void printH(table myTable){
    printf("[");
    for (int i = 0; i < myTable.size; ++i){
        printC(myTable.arr[i]);
        if (i+1 != myTable.size){
            printf(", ");
        }
    }
    printf("]\n");
}