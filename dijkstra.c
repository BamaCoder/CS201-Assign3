#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "scanner.h"
#include "darray.h"
#include "binomial.h"
#include "queue.h"

typedef struct Edge {
    int v1;
    int v2;
    int weight;
} Edge;

typedef int Vertex;

typedef struct VertexNode {
    Vertex value;
    struct VertexNode *pred;
    int distance;
    int visited;
    int level;
    BinomialNode *node;
} VertexNode;

typedef struct Graph {
    int size;
    int source;
    DArray *vertices;
    int **adj;
} Graph;

void updateVertex(void* val, BinomialNode *n) {
    VertexNode *v = (VertexNode*) val;
    v->node = n;
}

VertexNode *newVertex(Vertex value) {
    VertexNode *v = malloc(sizeof(VertexNode));
    v->pred = 0;
    v->value = value;
    v->distance = INT_MAX;
    v->visited = 0;
    v->node = 0;
    return v;
}

int compareVertices(void *a, void *b) {
    if(a == 0 &&  b == 0) return 0;
    else if(a == 0) return -1;
    else if(b == 0) return 1;
    else if(((VertexNode*)a)->distance == ((VertexNode*)b)->distance) {
        if(((VertexNode*)a)->value < ((VertexNode*)b)->value) return -1;
        else return 1;
    }
    else if (((VertexNode*)a)->distance < ((VertexNode*)b)->distance)
        return -1;
    else return 1;
}

void displayVertex(FILE *fp, void *v) {
    fprintf(fp, "%d", ((VertexNode*)v)->value);
    if(((VertexNode*)v)->pred != 0 && ((VertexNode*)v)->pred != v) {
        fprintf(fp, "(%d)", ((VertexNode*)v)->pred->value);
        fprintf(fp, "%d", ((VertexNode*)v)->distance);
    }
}

void displaysubTree(FILE *fp, queue *q) {
    if(sizeQueue(q) == 0) return;
    Binomial *pq = newBinomial(0, compareVertices, updateVertex);

    int lev = 0, queuesize = sizeQueue(q);
    for(int i = 0, n = sizeQueue(q); i < n; i++) {
        VertexNode *v = dequeue(q);
        if(v->level > lev) lev = v->level;
        insertBinomial(pq, v);
    }
    queue *rowtoPrint[lev];

    for(int i = 0; i <= lev; i++) {
        rowtoPrint[i] = newQueue(0);
    }

    for(int i = 0; i < queuesize; i++) {
        VertexNode *tmp = extractBinomial(pq);
        enqueue(rowtoPrint[tmp->level], tmp);
    }

    for(int i = 0; i <= lev; i++) {
        fprintf(stdout, "%d : ", i);
        while(sizeQueue(rowtoPrint[i]) != 0) {
            VertexNode *tmp = dequeue(rowtoPrint[i]);
            displayVertex(fp, tmp);
            if(sizeQueue(rowtoPrint[i]) > 0 ) fprintf(fp, " ");
        }
        fprintf(fp, "\n");
     }
    fprintf(stdout, "----\n");
}

// used forums as a basis, as well as miscellaneous online resources
void dijkstra (Graph* graph) {
    Binomial *heap = newBinomial(0, compareVertices, updateVertex);
    for(int i = 0; i < sizeDArray(graph->vertices); i++) {
        VertexNode *vert = getDArray(graph->vertices,i);
        if(vert != 0) {
            vert->node = insertBinomial(heap, vert);
        }
    }
    queue *seenNodes = newQueue(0);
    while(sizeBinomial(heap) != 0) {
        VertexNode *v = extractBinomial(heap);
        if(v->pred == 0) {
            v->distance = 0;
            displaysubTree(stdout, seenNodes);
            seenNodes = newQueue(0);
        }
        enqueue(seenNodes, v);
        v->visited = 1;
        for(int i = 0; i < graph->size; i++) {
            if(graph->adj[v->value][i] != 0) {
                VertexNode *u = getDArray(graph->vertices, i);
                if(u->visited == 0 && ((v->distance + graph->adj[v->value][i]) < u->distance)) {
                        u->pred = v;
                        u->distance = v->distance + graph->adj[v->value][i];
                        u->level = v->level+1;
                        decreaseKeyBinomial(heap,u->node, u);
                }
            }
        }
    }
    displaysubTree(stdout, seenNodes);
}

Graph* createGraph(char* file) {
    Graph *graph = malloc(sizeof(Graph));
    FILE *ifp = fopen(file, "r");
    int tmp1 = 0, tmp2 = 0, min = INT_MAX, weight = 1, max = 0;
    while(!feof(ifp)) {
        char c;
        tmp1 = readInt(ifp);
        if(tmp1 > max) max = tmp1;
        if(tmp1 < min) min = tmp1;
        tmp2 = readInt(ifp);
        if(tmp2 > max) max = tmp2;
        if(tmp1 < min) min = tmp2;
        skipWhiteSpace(ifp);
        c = fgetc(ifp);
        if(c != ';') {
            ungetc(c, ifp);
            weight = readInt(ifp);
            skipWhiteSpace(ifp);
            c = fgetc(ifp);
        }
        if(feof(ifp)) {
            graph->size = max + 1;
            graph->source = min;
        }
    }
    weight = weight;
    rewind(ifp);

    graph->adj = malloc(sizeof(int*)*graph->size);
    for(int i = 0; i < graph->size; i++)
        graph->adj[i] = malloc(graph->size*sizeof(int));

    DArray* vertices = newDArray(0);
    for(int i = 0; i < graph->size; i++) {
        setDArray(vertices,i,0);
    }

    while(!feof(ifp)) {
        int weight = 1;
        char c;
        tmp1 = readInt(ifp);
        tmp2 = readInt(ifp);
        skipWhiteSpace(ifp);
        c = fgetc(ifp);
        if(c != ';') {
            ungetc(c, ifp);
            weight = readInt(ifp);
            skipWhiteSpace(ifp);
            c = fgetc(ifp);
        }
        if(tmp1 != tmp2) {
            tmp1 -= min;
            tmp2 -= min;
            VertexNode *vertex1 = newVertex(tmp1);
            VertexNode *vertex2 = newVertex(tmp2);
            if(graph->adj[tmp1][tmp2] == 0 || weight < graph->adj[tmp1][tmp2]) {
                graph->adj[tmp1][tmp2] = weight;
                graph->adj[tmp2][tmp1] = weight;
            }
            if(getDArray(vertices, tmp1) == 0) {
                setDArray(vertices, tmp1, vertex1);
            }
            if(getDArray(vertices, tmp2) == 0) {
                setDArray(vertices, tmp2, vertex2);
            }
            if(tmp1 == graph->source) {
                if(getDArray(vertices, tmp1) == 0) {
                    setDArray(vertices, tmp1, vertex1);
                }
                vertex1->distance = 0;
                vertex1->pred = vertex1;
                vertex1->level = 0;
            }
            else if(tmp2 == graph->source) {
                if(getDArray(vertices, tmp2) == 0) {
                    setDArray(vertices, tmp2, vertex2);
                }
                vertex2->distance = 0;
                vertex2->pred = vertex2;
                vertex2->level = 0;
            }
        }
    }
    fclose(ifp);
    graph->vertices = vertices;

    return graph;
}

int main(int argc, char* argv[]) {
    if(argc == 2) {
        Graph* graph = createGraph(argv[1]);
        dijkstra(graph);
    }
    return 0;
}
