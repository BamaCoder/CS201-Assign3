/*
 * Dynamic Array Tester, by John C. Lusth
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "integer.h"
#include "darray.h"

static void insert(DArray *,integer **,int);
static void delete(DArray *);
static void delete2(DArray *a,int);
static void randomize(integer **,int);
static void display(DArray *);

extern void srandom(unsigned int seed);
extern long int random(void);

void Fatal(char *,...);

int
main(int argc,char **argv)
    {
    int i;
    int nodeCount;
    integer **nodes;
    DArray *a;

    if (argc != 4) Fatal("usage: %s NODE_COUNT TRIALS SUBMISSION\n",argv[0]);

    srandom(atoi(argv[2]) * 1000 + atoi(argv[3]));

    nodeCount = atoi(argv[1]);
    nodes = malloc(sizeof(integer *) * nodeCount);
    for (i = 0; i < nodeCount; ++i)
        nodes[i] = newInteger(i);

    a = newDArray(displayInteger);

    insert(a,nodes,nodeCount);
    display(a);
    delete(a);
    display(a);
    insert(a,nodes,--nodeCount);
    display(a);
    delete(a);
    display(a);
    insert(a,nodes,--nodeCount);
    display(a);
    delete2(a,nodeCount);
    display(a);

    return 0;
    }

static void
randomize(integer **array,int count)
    {
    int i;
    for (i = 0; i < count; ++i)
        {
        int j = random() % count;
        //printf("swaping %s with %s\n",nodes[i],nodes[j]);
        integer *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        }
    }

static void
insert(DArray *a,integer **nodes,int nodeCount)
    {
    int i;
    randomize(nodes,nodeCount);
    printf("INSERTING:");
    for (i = 0; i < nodeCount; ++i)
        {
        printf(" %d",getInteger(nodes[i]));
        insertDArray(a,nodes[i]);
        }
    printf("\n\n");
    }

static void
display(DArray *a)
    {
    printf("dynamic array size is %d\n",sizeDArray(a));
    printf("----\n");
    displayDArray(stdout,a);
    printf("\n\n");
    }

static void
delete(DArray *a)
    {
    printf("REMOVING:");
    while (sizeDArray(a) > 0)
        {
        integer *x = removeDArray(a);
        printf(" %d",getInteger(x));
        }
    printf("\n\n");
    }

static void
delete2(DArray *a,int nodeCount)
    {
    int i;
    printf("REMOVING:");
    for (i = 0; i < nodeCount; ++i)
        {
        if (i % 8 == 7)
            {
            printf("\n\n");
            display(a);
            if (i < nodeCount)
                printf("DELETING:");
            }
        integer *x = removeDArray(a);
        printf(" %d",getInteger(x));
        }
    printf("\n\n");
    }

void
Fatal(char *fmt, ...)
    {
    va_list ap;

    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
    }
