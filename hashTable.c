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

int isPrime(int);//returns 1 if given numberis prime, and returns 0 if not
int nextPrime(int);//returns the nearest prime
table* newTable(int);//table constructor
table* reHash(table*);//creates another table and copy all keys to another table with nearest prime(3x) of the original size, and obviously, do free to the table
int search(table*, int);
table* tableRmv(table*, int);
int hashing(int, int);//hashing function
table* insert(table*, int);//get the index given by hashing function, tries to insert, if fail, try again with ++key, if growth rate is more  or equal than 75%, do rehash
void printC(cell);//print a cell of an table
void printH(table);//print hash table with the value and status of cell, the status can be "empty", "occupied" or "deleted"







int main(void){
    srand(time(NULL));
    system("cls||clear");

    
    table* tbl = newTable(7);
    for (int i = 0; i < 23; ++i){
        tbl = insert(tbl, i);
    }
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
    return (key * 3) % size;
}

table* insert(table* table, int key){
    if (search(table, key) > -1) return table;
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
    table* new = newTable(nextPrime(myTable->size * 3));

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

int isPrime(int number){
    for (int i = 2; i <= number; ++i){
        if (number % i == 0 && number != i) {
            return 0;
        }
    }
    return 1;
}

int nextPrime(int number){
    int x = 4;
    int distance = 0;
    while (!isPrime(x)){
        if (isPrime(number - distance)) x = number - distance;
        if (isPrime(number + distance)) x = number + distance;
        ++distance;
    }
    return x;
}

int search(table* table, int key){
    int begin = hashing(key, table->size);
    for (int i = begin; i < table->size && table->arr[i].status != 0; ++i){
        if (table->arr[i].value == key) return i;
    }
    return -1;
}

table* tableRmv(table* mtable, int key){
    int index = search(mtable, key);
    if (index > -1){
        mtable->arr[index].status = -1;
        mtable->arr[index].value = 0;
    }
    return mtable;
}