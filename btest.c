/*
 * Binomial Heap Tester, by John C. Lusth
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "integer.h"
#include "binomial.h"

static void insert(Binomial *,integer **,int);
static void delete(Binomial *b,integer **,int);
static void extract(Binomial *);
static void randomize(integer **,int);
static int lessthan(void *,void *);
static void display(Binomial *);
static void update(void *,BinomialNode *);

extern void srandom(unsigned int seed);
extern long int random(void);

void Fatal(char *,...);

int
main(int argc,char **argv)
    {
    int i;
    int nodeCount;
    integer **nodes;
    Binomial *b;

    if (argc != 4) Fatal("usage: %s NODE_COUNT TRIALS SUBMISSION\n",argv[0]);

    srandom(atoi(argv[2]) * 1000 + atoi(argv[3]));

    nodeCount = atoi(argv[1]);
    nodes = malloc(sizeof(integer *) * nodeCount);
    for (i = 0; i < nodeCount; ++i)
        nodes[i] = newInteger(i);

    b = newBinomial(displayInteger,lessthan,update);

    insert(b,nodes,nodeCount);
    display(b);
    extract(b);
    printf("size of heap: %d\n",sizeBinomial(b));
    insert(b,nodes,--nodeCount);
    display(b);
    extract(b);
    printf("size of heap: %d\n",sizeBinomial(b));
    insert(b,nodes,--nodeCount);
    display(b);
    delete(b,nodes,nodeCount-2);
    display(b);

    return 0;
    }

static int
lessthan(void *a,void *b)
    {
    integer *x = a;
    integer *y = b;
    if (x == 0 && y == 0)
        return 0;
    else if (x == 0)
        return -1;
    else if (y == 0)
        return 1;
    else
        return getInteger(x) - getInteger(y);
    }

static void
update(void *a,BinomialNode *n)
    {
    if (a != 0) setIntegerOwner((integer *) a,n);
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
insert(Binomial *b,integer **nodes,int nodeCount)
    {
    int i;
    randomize(nodes,nodeCount);
    printf("INSERTING:");
    for (i = 0; i < nodeCount; ++i)
        {
        printf(" %d",getInteger(nodes[i]));
        setIntegerOwner(nodes[i],insertBinomial(b,nodes[i]));
        }
    printf("\n\n");
    }

static void
display(Binomial *b)
    {
    printf("binomial heap size is %d\n",sizeBinomial(b));
    printf("----\n");
    displayBinomial(stdout,b);
    printf("\n");
    }

static void
extract(Binomial *b)
    {
    printf("EXTRACTING:");
    while (sizeBinomial(b) > 0)
        {
        integer *x = extractBinomial(b);
        printf(" %d",getInteger(x));
        }
    printf("\n\n");
    }

static void
delete(Binomial *b,integer **nodes,int nodeCount)
    {
    int i;
    printf("When deleting, the first number is the value to be deleted.\n");
    printf("    The second (in parentheses) is the decreased key value.\n");
    printf("\n");
    printf("DELETING:");
    for (i = 0; i < nodeCount; ++i)
        {
        if (i % 8 == 7)
            {
            printf("\n\n");
            display(b);
            if (i < nodeCount)
                printf("DELETING:");
            }
        printf(" %d (",getInteger(nodes[i]));
        setInteger(nodes[i],-1 - i);
        decreaseKeyBinomial(b,getIntegerOwner(nodes[i]),nodes[i]);
        integer *x = extractBinomial(b);
        printf("%d)",getInteger(x));
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
