#ifndef GRAPH_H
#define GRAPH_H

// GCC should deal with it, but just to be sure :D
#include <stdbool.h>

typedef struct {
	int n; // number of vertices
	int edges; // current number of edges
	int **adj; // adjacency matrix
} Graph;

// basic memory management stuff
Graph *graphCreate(int n);
void graphFree(Graph *g);

// basic operations i guess :p 
bool graphAddEdge(Graph *g, int a, int b);
bool graphRemoveEdge(Graph *g, int a, int b);
bool graphHasEdge(const Graph *g, int a, int b); // const to make sure we don't modify graph during checks

// some required utils
void graphClear(Graph *g); // should remove all edges while keeping the allocated structure
// bool graphIsConnected(const Graph *g);
Graph *graphCopy(const Graph *g);


#endif
