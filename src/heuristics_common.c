#include "heuristics_common.h"
#include "graph.h"

// helper function - generates random tree
void graphMakeRandomTree(Graph *g) {
	for(int i=1; i<g->n; i++) {
		int parent;
    	do {
    	    parent = rand() % i;
    	} while(!graphAddEdge(g, i, parent));
	}
}
