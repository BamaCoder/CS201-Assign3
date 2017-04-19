#include "darray.h"
#include <stdio.h>
#include <stdlib.h>

struct DArray {
    void **array;
    int capacity;
    int size;
    void (*display)(FILE *, void*);
};

DArray *newDArray(void (*display) (FILE *, void *)) {
    DArray *newArray = malloc(sizeof(DArray));
    if(newArray == 0) {
        fprintf(stderr, "Out of memory.\n");
        exit(-1);
    }
    newArray->array = 0;
    newArray->capacity = 1;
    newArray->size = 0;
    newArray->display = display;
    return newArray;
}

void doubleifFull(DArray *a, void* value) {
    while(a->size >= a->capacity) {
        a->capacity *= 2;
        a->array = realloc(a->array, sizeof(value) * a->capacity);
    }
}

void shrinkifQuarter(DArray *a, void* value) {
    if(a->size < a->capacity/4) {
        a->capacity /= 2;
        a->array = realloc(a->array, sizeof(value)* a->capacity);
    }
}

void insertDArray(DArray *a, void *v) {
    if(a->array == 0) a->array = malloc(sizeof(v));
    doubleifFull(a, v);
    a->array[a->size++] = v;
}

void *removeDArray(DArray *a) {
    void* v = a->array[a->size-1];
    a->array[--a->size] = 0;
    shrinkifQuarter(a, v);
    return v;
}
void *getDArray(DArray *a, int index) {
    if(index >= a->size || index < 0) {
        fprintf(stderr, "Index %d out of bounds for array of size %d\n", index, a->size);
        exit(1);
    }
    else return a->array[index];
}

void setDArray(DArray *a, int index, void *value) {
    if(index == a->size) insertDArray(a, value);
    else a->array[index] = value;
}

int sizeDArray(DArray *a) {
    if(a == 0) return 0;
    else return a->size;
}

void displayDArray(FILE *fp, DArray *a) {
    fprintf(fp, "[");
    for(int i = 0; i < a->size; i++) {
        a->display(fp, a->array[i]);
        if(i != a->size - 1) fprintf(fp, ",");
    }
    fprintf(fp, "]");
    fprintf(fp, "[%d]", a->capacity-a->size);
}
