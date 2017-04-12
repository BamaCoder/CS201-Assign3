#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "integer.h"

struct integer
    {
    int value;
    void *owner;
    };

integer *
newInteger(int x)
    {
    integer *p = malloc(sizeof(integer));
    if (p == 0) { fprintf(stderr,"out of memory\n"); exit(1); }
    p->value = x;
    return p;
    }

int
getInteger(integer *v)
    {
    return v->value;
    }

int
setInteger(integer *v,int x)
    {
    int old = v->value;
    v->value = x;
    return old;
    }

void *
getIntegerOwner(integer *v)
    {
    return v->owner;
    }

void *
setIntegerOwner(integer *v,void *x)
    {
    void *old = v->owner;
    v->owner = x;
    return old;
    }

void
displayInteger(FILE *fp,void *v)
    {
    fprintf(fp,"%d",getInteger((integer *) v));
    }

void
freeInteger(integer *v)
    {
    free(v);
    }
