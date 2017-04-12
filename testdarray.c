#include "integer.h"
#include "darray.h"
#include <stdio.h>

int main(void) {
    DArray *array = newDArray(displayInteger);
    insertDArray(array,newInteger(3));
    removeDArray(array);
    displayDArray(stdout,array);
    insertDArray(array,newInteger(4));
    insertDArray(array,newInteger(7));
    insertDArray(array,newInteger(2));
    displayDArray(stdout,array);
    for (int i = 0; i < 5000; i++) insertDArray(array,newInteger(7));
    for (int i = 0; i < 4999; i++) removeDArray(array);
    displayDArray(stdout,array);
    fprintf(stdout,"%d\n",getInteger(getDArray(array,0)));
    return 0;
}
