#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <math.h>

#include "heuristics_greedy.h"
#include "heuristics_common.h"
#include "spectrum.h"
#include "config.h"

bool greedyAddBestEdge(Graph *g) {
	int bestA = -1;
	int bestB = -1;
	double bestScore = -INFINITY;

	for(int a=0; a<g->n; a++) {
		for(int b=a+1; b<g->n; b++) {
			if(graphHasEdge(g, a, b)) continue;
			graphAddEdge(g,a,b);
			double score = spectrumIntegralScore(g);
			graphRemoveEdge(g,a,b);

			if(score>bestScore) {
				bestScore = score;
				bestA = a;
				bestB = b;
			}
		}
	}

	if(bestA < 0) {
		if(!QUIET) fprintf(stderr, "greedyAddBestEdge() failed!\n");
		return false;
	}
	graphAddEdge(g, bestA, bestB);
	return true;
}

Graph *heuristicsGreedyGenerateGraph(int n, int k) {
	if(n<=0) return NULL;
	int maxEdges = n*(n-1)/2;
	if(k<n-1 || k>maxEdges) return NULL;

	Graph *g = graphCreate(n);
	if(!g) return NULL;
	if(!QUIET) printf("[Greedy] Generating graph n=%d k=%d\n", n, k);
	graphMakeRandomTree(g);

	while(g->edges < k) {
		if(!greedyAddBestEdge(g)) {
			// theoretically impossible
			// break;
			return NULL;
		}
	}
	return g;
}

Graph *heuristicsGreedyGenerateIntegralGraph(int n, int k) {
	while(true) {
		Graph *g = heuristicsGreedyGenerateGraph(n, k);
		if(!g) return NULL;

		if(INTEGRALITY_CHECK_ENABLED) {
			if(spectrumIsIntegral(g)) {
				if(!QUIET) printf("[Greedy] Graph is integral!\n");
				return g;
			}
		} else {
			return g;
		}

		graphFree(g);
	}
}
