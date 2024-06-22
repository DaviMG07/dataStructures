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
    float growthRate;
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
    for (int i = 0; i < 12; ++i){
        printf("\n");
        tbl = insert(tbl, i*i);
        printH(*tbl);
    }

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
    if (table->growthRate >= 0.75) return reHash(table);
    return table;
}

table* reHash(table* myTable){
    table* new = newTable(myTable->size * 3);

    for (int i = 0; i < myTable->size; ++i){
        if (myTable->arr[i].status == 1){
            insert(new, myTable->arr[i].value);
        }
    }

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
    printf("size: %d\nbuckets: %d\ngrowth rate: %f\n", myTable.size, myTable.buckets, myTable.growthRate);
    printf("[");
    for (int i = 0; i < myTable.size; ++i){
        printC(myTable.arr[i]);
        if (i+1 != myTable.size){
            printf(", ");
        }
    }
    printf("]\n");
}