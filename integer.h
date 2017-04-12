#include <stdio.h>

#ifndef __INTEGER_INCLUDED__
#define __INTEGER_INCLUDED__

typedef struct integer integer;
extern integer *newInteger(int);
extern int getInteger(integer *);
extern int setInteger(integer *,int);
extern void *getIntegerOwner(integer *);
extern void *setIntegerOwner(integer *,void *);
extern void displayInteger(FILE *,void *);
extern void freeInteger(integer *);

#define PINFINITY IN_MAX
#define NINFINITY IN_MIN

#endif
