#include <stdlib.h>
#include <string.h>

#include "graph.h"


// woah, memory management!
Graph *graphCreate(int n) {
	int i,j;

	if(n<=0) return NULL; // sanity checks
	Graph *g = malloc(sizeof(Graph)); // hope I won't accidentally create memory leaks, DANGEROUS :D
	if(!g) return NULL; // another sanity check

	g->n = n;
	g->edges = 0;
	g->adj = malloc(n*sizeof(int *));

	if(!g->adj) {
		free(g); // woah, almost forgot
		return NULL;
	}

	for(i=0; i<n; i++) {
		g->adj[i] = calloc(n, sizeof(int));
		// another sanity check
		if(!g->adj[i]) {
			for(j=0; j<i; j++) {
				free(g->adj[j]);
			}
			free(g->adj);
			free(g);
			return NULL;
		}
	}
	return g;
}

void graphFree(Graph *g) {
	int i;
	if(!g) return;
	for(i=0; i<g->n; i++) {
		free(g->adj[i]);
	}
	free(g->adj);
	free(g);
}

// basic operations
bool graphAddEdge(Graph *g, int a, int b) {
	if(!g) return false;
	if(a<0 || b<0 || a >= g->n || b >= g->n) return false;
	if(a==b) return false;
	if(g->adj[a][b]) return false;

	g->adj[a][b] = 1;
	g->adj[b][a] = 1;
	g->edges++;

	return true;
}

bool graphRemoveEdge(Graph *g, int a, int b) {
	// same sanity checks
	if(!g) return false;
	if(a<0 || b<0 || a >= g->n || b >= g->n) return false;
	if(a==b) return false;
	if(!g->adj[a][b]) return false;

	g->adj[a][b] = 0;
	g->adj[b][a] = 0;
	g->edges--;

	return true;
}

bool graphHasEdge(const Graph *g, int a, int b) {
	if(!g) return false;
	if(a<0 || b<0 || a >= g->n || b >= g->n) return false;
	return g->adj[a][b] != 0; // != 0 just to be sure, function returns bool however we store adjacency matrix as integers
}

// utils
void graphClear(Graph *g) {
	int i;
	int j;
	if(!g) return;
	for(i=0; i<g->n; i++) {
		for(j=0; j<g->n; j++) {
			g->adj[i][j]=0;
		}
	}
	g->edges=0;
}

Graph *graphCopy(const Graph *g) {
	int i;
	if(!g) return NULL;

	Graph *copy = graphCreate(g->n);
	if(!copy) return NULL;

	copy->edges = g->edges;

	for(i=0; i<g->n; i++) {
		memcpy(copy->adj[i], g->adj[i], g->n*sizeof(int));
	}

	return copy;
}
