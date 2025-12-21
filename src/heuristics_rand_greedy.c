#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <math.h>

#include "heuristics_greedy.h"
#include "heuristics_common.h"
#include "spectrum.h"
#include "config.h"

static void randomAddEdge(Graph *g) {
	while(true) {
		int a = rand()%g->n;
		int b = rand()%g->n;
		if(graphHasEdge(g,a,b)) continue;
		graphAddEdge(g,a,b);
		break;
	}
}
Graph *heuristicsRandomGreedyGenerateGraph(int n, int k, double pRand) {
	if(n<=0) return NULL;
	int maxEdges = n*(n-1)/2;
	if(k<n-1 || k>maxEdges) return NULL;

	Graph *g = graphCreate(n);
	if(!g) return NULL;

	if(!QUIET) printf("[RandGreedy] Generating graph n=%d k=%d p=%.2f\n", n, k, pRand);

	graphMakeRandomTree(g);
	while(g->edges < k) {
		double r = (double)rand()/RAND_MAX;
		if(r<pRand) {
			randomAddEdge(g);	
		} else {
			// again, theoretically impossible
			if(!greedyAddBestEdge(g)) break;
		}
	}
	return g;
}

Graph *heuristicsRandomGreedyGenerateIntegralGraph(int n, int k, double pRand) {
	while(true) {
		Graph *g = heuristicsRandomGreedyGenerateGraph(n, k, pRand);
		if(!g) return NULL;

		if(INTEGRALITY_CHECK_ENABLED) {
			if(spectrumIsIntegral(g)) {
				if(!QUIET) printf("[RandGreedy] Graph is integral!\n");
				return g;
			}
		} else {
			return g;
		}

		graphFree(g);
	}
}
