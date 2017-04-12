#include <stdio.h>
#include "integer.h"

#ifndef __COMPARATOR_INCLUDED__
#define __COMPARATOR_INCLUDED__

typedef int (*Comparator)(void*,void*);

extern int intComparator(void *,void *);

#endif
