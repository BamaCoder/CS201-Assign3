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


int main(int argc, char* argv[]) {
    if(argc == 2) {
        DArray *edges = newDArray(NULL);
        DArray *vertices = newDArray(NULL);
        FILE *ifp = fopen(argv[1], "r+");
        while(!feof(ifp)) {
            Edge* newEdge = malloc(sizeof(Edge));
            int tmp1, tmp2, weight = 1;
            char c = 0;
            Vertex *temp1 = &tmp1, *temp2 = &tmp2;
            tmp1 = readInt(ifp);
            tmp2 = readInt(ifp);
            insertDArray(vertices, temp1);
            insertDArray(vertices, temp2);
            c = fgetc(ifp);
            if(c != 59) {
                ungetc(c, ifp);
                weight = readInt(ifp);
            }
            newEdge->v1 = *temp1;
            newEdge->v2 = *temp2;
            newEdge->weight = weight;
            insertDArray(edges, newEdge);
        }

        fclose(ifp);
    }
    else fprintf(stderr, "Invalid Input. Please input 'dijkstra <filename>'.\n");

    return 0;
}
