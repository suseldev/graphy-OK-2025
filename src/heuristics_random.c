#include <stdlib.h>
#include <stdio.h>
// again, just to be sure, can't remember where I imported this :D
#include <stdbool.h>

#include "config.h"
#include "heuristics_random.h"
#include "graph.h"
#include "spectrum.h"
#include "heuristics_common.h"


Graph *heuristicsRandomGenerateGraph(int n, int k) {
	if(n<=0) return NULL;
	int maximumE = n*(n-1)/2;
	if(k<n-1 || k>maximumE) return NULL;

	Graph *g = graphCreate(n);
	if(!g) return NULL;

	if(!QUIET) printf("[Random] Generated graph n=%d k=%d\n", n, k);

	// we start from the random tree, asserting our graph will be connected
	graphMakeRandomTree(g);

	while(g->edges < k) {
		int a = rand()%n;
		int b = rand()%n;
		if (a==b) continue;
		graphAddEdge(g, a, b); // if it was already existent, nothing bad happens as this function has sanity checks! :D
	}
	return g;
}

Graph *heuristicsRandomGenerateIntegralGraph(int n, int k) {
	while(true) {
		Graph *g = heuristicsRandomGenerateGraph(n, k);
		if(!g) return NULL;
		

		if(INTEGRALITY_CHECK_ENABLED) {
			if(spectrumIsIntegral(g)) {
				if(!QUIET) printf("[Random] Graph is integral!\n");
				return g;
			}
		}
		graphFree(g);
	}
}
