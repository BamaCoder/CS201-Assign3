#include <stdio.h>
#include <string.h>
#include "integer.h"
#include "comparator.h"


int intComparator(void*v, void*w) {
    return *(int*)v - *(int*)w;
}

