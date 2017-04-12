#include "binomial.h"
#include "comparator.h"
#include "integer.h"
#include <stdio.h>

int main (void) {

    Binomial *heap = newBinomial(displayInteger,intComparator,NULL);
    fprintf(stdout,"Inserting...\n");
    (void) insertBinomial(heap,newInteger(4));
    displayBinomial(stdout,heap);
    fprintf(stdout,"Inserting...\n");
    (void) insertBinomial(heap,newInteger(8));
    displayBinomial(stdout,heap);
    fprintf(stdout,"Inserting...\n");
    (void) insertBinomial(heap,newInteger(16));
    displayBinomial(stdout,heap);
    fprintf(stdout,"Inserting...\n");
    (void) insertBinomial(heap,newInteger(5));
    displayBinomial(stdout,heap);
    fprintf(stdout,"Inserting...\n");
    (void) insertBinomial(heap,newInteger(1));
    displayBinomial(stdout,heap);
    fprintf(stdout,"Extracting...\n");
    (void) extractBinomial(heap);
    displayBinomial(stdout,heap);
    fprintf(stdout,"Extracting...\n");
    (void) extractBinomial(heap);
    displayBinomial(stdout,heap);
    fprintf(stdout,"Extracting...\n");
    (void) extractBinomial(heap);
    displayBinomial(stdout,heap);

    return 0;
}
