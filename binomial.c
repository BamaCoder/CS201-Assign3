#include "darray.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct BinomialNode {
    void* value;
    DArray *children;
    struct BinomialNode *parent;
    void (*display)(FILE *,void *);
}BinomialNode;

typedef struct Binomial {
    DArray *rootlist;
    int (*compare)(void *, void*);
    void (*update)(void *, BinomialNode*);
    BinomialNode *extreme;
    int size;
    void (*display)(FILE *, void *);
} Binomial;

Binomial *newBinomial (void(*d)(FILE *, void *), int(*c)(void *, void *), void(*u)(void *, BinomialNode*)) {
    Binomial *b = malloc(sizeof(Binomial));
    if(b == 0) {
        fprintf(stderr, "Out of memory. Exiting...\n");
        exit(-1);
    }
    b->rootlist = newDArray(d);
    b->compare = c;
    b->update = u;
    b->extreme = 0;
    b->size = 0;
    b->display = d;
    return b;
}

BinomialNode* newBinomialNode(void(*display)(FILE *, void *), void *value) {
    BinomialNode *n = malloc(sizeof(BinomialNode));
    if(n == 0) {
        fprintf(stderr, "Out of memory. Exiting...\n");
        exit(-1);
    }
    n->value = value;
    n->children = newDArray(display);
    n->parent = n;
    n->display = display;
    return n;
}

static BinomialNode* combine(Binomial *b, BinomialNode*x, BinomialNode *y) {
    int i = 0;
    if(b->compare(x->value, y->value) < 0) {
        i = sizeDArray(y->children);
        setDArray(x->children, i, y);
        y->parent = x;
        return x;
    }
    else {
        i = sizeDArray(x->children);
        setDArray(y->children, i, x);
        x->parent = y;
        return y;
    }
}

BinomialNode *getTree(DArray *a, int degree) {
    if(degree == sizeDArray(a)) return 0;
    else return getDArray(a, degree);
}

static void consolidate(Binomial *b, BinomialNode *node) {
    int degree = sizeDArray(node->children);
    BinomialNode *subtree;
    while((subtree = getTree(b->rootlist,degree))) {
        node = combine(b, node, subtree);
        setDArray(b->rootlist,degree,0);
        degree++;
    }
    setDArray(b->rootlist, degree, node);
}

static void merge(Binomial *b, DArray *donor) {
    for (int i = 0; i < sizeDArray(donor); i++) {
        BinomialNode* n = (BinomialNode*) getDArray(donor, i);
        n->parent = n;
        consolidate (b,n);
    }
}

void updateExtreme(Binomial *b, BinomialNode *n) {
    if(b->extreme == 0) b->extreme = n;
    else if (b->compare(n->value, b->extreme->value) < 0)  b->extreme = n;
}

BinomialNode *insertBinomial(Binomial *b, void *value) {
    BinomialNode *n = newBinomialNode(b->display, value);
    updateExtreme(b,n);
    consolidate(b,n);
    b->size++;
    return n;
}

BinomialNode *bubbleUp(Binomial *b, BinomialNode *n) {
    if(n->parent == n || b->compare(n->value, n->parent->value) > 0) return n;
    else {
        b->update(n->value,n->parent);
        b->update(n->parent->value, n);
        void *tmp = n->value;
        n->value = n->parent->value;
        n->parent->value = tmp;
        return bubbleUp(b, n->parent);
    }
}

void findExtreme(Binomial *b) {
    b->extreme = 0;
    BinomialNode *n = 0;
    for(int i = 0; i < sizeDArray(b->rootlist); i++) {
        n = getTree(b->rootlist, i);
        if(n != 0) updateExtreme(b,n);
    }
}

void decreaseKeyBinomial(Binomial *b, BinomialNode *n, void* value) {
    n->value = value;
    BinomialNode *np = bubbleUp(b, n);
    updateExtreme(b, np);
}

void* extractBinomial(Binomial *b) {
    BinomialNode *n = b->extreme;
    for(int i = 0, N = sizeDArray(b->rootlist); i < N; i++) {
        if((BinomialNode *)getDArray(b->rootlist, i) == n)  setDArray(b->rootlist, i, 0);
    }
    merge(b, n->children);
    b->size--;
    void *tmp = n->value;
    n = 0;
    findExtreme(b);
    return tmp;
}

void deleteBinomial(Binomial *b, BinomialNode *n) {
    decreaseKeyBinomial(b,n,0);
    extractBinomial(b);
}

int sizeBinomial(Binomial *b) {
    return b->size;
}

void displayBinomialNode(FILE *fp, BinomialNode *n) {
    if(n == 0) return;
    n->display(fp, n->value);
    fprintf(fp, "-");
    fprintf(fp, "%d", sizeDArray(n->children));
    if(n != n->parent) {
        fprintf(fp, "(");
        n->display(fp, n->parent->value);
        fprintf(fp, "-");
        fprintf(fp, "%d", sizeDArray(n->parent->children));
        fprintf(fp, ")");
    }
}

void displayTree(FILE *fp, BinomialNode* n) {
    queue *q = newQueue(n->display);
    int lev = 0;
    enqueue(q, n);
    if(n!= 0)
    while(sizeQueue(q)) {
        fprintf(fp, "%d: ", lev);
        lev++;
        for(int i = 0, n = sizeQueue(q); i < n; i++) {
            BinomialNode *node = peekQueue(q);
            displayBinomialNode(fp, node);
            dequeue(q);
            if(i != sizeQueue(q)-1) fprintf(fp, " ");
            for(int j = 0; j < sizeDArray(node->children); j++) {
                enqueue(q, getTree(node->children, j));
            }
        }
        fprintf(fp,"\n");
    }
    free(q);
    fprintf(fp, "----\n");
}

void displayBinomial(FILE *fp, Binomial *b) {
    if(sizeBinomial(b) == 0) {
        fprintf(fp, "0:\n");
        return;
    }
    for(int i = 0; i < sizeDArray(b->rootlist); i++) {
        BinomialNode* n = getTree(b->rootlist, i);
        if(n != 0) displayTree(fp, n);
    }
}


