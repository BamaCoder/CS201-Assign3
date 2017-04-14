#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "darray.h"
#include "binomial.h"

typedef struct Edge {
    int v1;
    int v2;
    int weight;
} Edge;

typedef int Vertex;

typedef struct Graph {
    DArray *vertices;
    DArray *edges;
} Graph;

int getWeight(int *a, int *b) {
    return e->weight;
}

void dijkstra (Graph g, )

int main(int argc, char* argv[]) {
    if(argc == 2) {
        Graph graph;
        graph->edges = newDArray(NULL);
        graph->vertices = newDArray(NULL);
        FILE *ifp = fopen(argv[1], "r+");
        int edgeind = 0;
        while(!feof(ifp)) {
            Edge* newEdge = malloc(sizeof(Edge));
            int tmp1, tmp2, weight = 1;
            char c;
            tmp1 = readInt(ifp);
            static int source = tmp1;
            if(tmp1 < source) source = tmp1;
            /*printf("tmp1: %d\n", tmp1);*/
            tmp2 = readInt(ifp);
            if(tmp2 < source) source = tmp2;
            /*printf("tmp2: %d\n", tmp2);*/
            insertDArray(graph->vertices, temp1);
            insertDArray(graph->vertices, temp2);
            skipWhiteSpace(ifp);
            c = fgetc(ifp);
            if(c != ';') {
                ungetc(c, ifp);
                weight = readInt(ifp);
                /*printf("weight: %d\n", weight);*/
                skipWhiteSpace(ifp);
                c = fgetc(ifp);
            }
            newEdge->v1 = *temp1;
            newEdge->v2 = *temp2;
            newEdge->weight = weight;
            if(newEdge->v1) insertDArray(graph->edges, newEdge);
        }
        fclose(ifp);
    }
    else fprintf(stderr, "Invalid Input. Please input 'dijkstra <filename>'.\n");

    return 0;
}
