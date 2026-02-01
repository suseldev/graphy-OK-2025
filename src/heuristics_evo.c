#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "heuristics_evo.h"
#include "heuristics_random.h"
#include "heuristics_common.h"
#include "spectrum.h"
#include "config.h"

static void evoMutate(Graph *g) {
	int tries = 0;

	for(tries=0; tries<10; tries++) {
		int a = rand()%g->n;
		int b = rand()%g->n;
		if(a==b) continue;
		if(!graphHasEdge(g,a,b)) continue;

		graphRemoveEdge(g,a,b);

		int c = rand()%g->n;
		int d = rand()%g->n;
		if(c!=d && !graphHasEdge(g,c,d)) {
			graphAddEdge(g,c,d);
			return;
		}
		// rollback
		graphAddEdge(g,a,b);
	}
}

Graph *heuristicsEvoGenerateGraph(int n, int k, int populationSize, int generations) {
    int i, j, generation;

    if(n<=0 || k<n-1) return NULL;
    if(populationSize < 2 || generations <= 0) return NULL;

    if(!QUIET) printf("[Evo] n=%d k=%d: Population=%d Generations=%d\n", n, k, populationSize, generations);

    Graph **population = malloc(populationSize * sizeof(Graph *));
    if(!population) return NULL;

    // init population
    for(i=0; i<populationSize; i++) {
        population[i] = heuristicsRandomGenerateGraph(n, k);
        if(!population[i]) {
            // protect the memory :D
            for(j=0; j<i; j++) graphFree(population[j]);
            free(population);
            return NULL;
        }
    }

    // global best ever (important shit)
    Graph *bestEver = NULL;
    double bestEverScore = -INFINITY;

    int ELITE = populationSize / 4; // elitism or sth
    if(ELITE < 1) ELITE = 1; // safeguard

    for(generation=0; generation<generations; generation++) {
        // maybe we have a jackpot :D
        if(INTEGRALITY_CHECK_ENABLED) {
            for(i=0; i<populationSize; i++) {
                if(spectrumIsIntegral(population[i])) {
                    if(!QUIET)
                        printf("[Evo] Integral graph found at generation %d\n", generation);
                    Graph *result = graphCopy(population[i]);
                    // protect THE MEMORY :p
                    for(j=0;j<populationSize;j++) graphFree(population[j]);
                    free(population);
                    if(bestEver) graphFree(bestEver);
                    return result;
                }
            }
        }

        // find best in current generation + update global best
        int bestIdx = 0;
        double genBestScore = -INFINITY;

        for(i=0; i<populationSize; i++) {
            double score = spectrumIntegralScore(population[i]);

            if(score > genBestScore) {
                genBestScore = score;
                bestIdx = i;
            }

            if(score > bestEverScore) {
                if(bestEver) graphFree(bestEver);
                bestEver = graphCopy(population[i]);
                bestEverScore = score;
            }
        }

        if(!QUIET && generation%100 == 0) printf("[Evo] gen=%d | best=%.6f | bestEver=%.6f\n", generation, genBestScore, bestEverScore);

        // next generation
        Graph **next = malloc(populationSize * sizeof(Graph *));
        if(!next) break; // oops!

        // elitism or sth
        for(i=0; i<ELITE; i++) next[i] = graphCopy(population[bestIdx]);

        for(i=ELITE; i<populationSize; i++) {
            int parent = rand() % ELITE;
            next[i] = graphCopy(next[parent]);
            // mutate, but not always
            if(rand()%100 < 80) evoMutate(next[i]);
        }

        for(i=0; i<populationSize; i++) graphFree(population[i]);
        free(population);
        population = next;
    }

    // return best found EVER
    for(i=0; i<populationSize; i++) graphFree(population[i]);
    free(population);
    return bestEver;
}

Graph *heuristicsEvoGenerateIntegralGraph(int n, int k, int populationSize, int generations) {
	while(true) {
		Graph *g = heuristicsEvoGenerateGraph(n, k, populationSize, generations);
		if(!g) return NULL;

		if(INTEGRALITY_CHECK_ENABLED) {
			if(spectrumIsIntegral(g)){
				if(!QUIET) printf("[Evo] Integral graph found!\n");
				return g;
			}
		} else {
			return g;
		}
		graphFree(g);
	}
}
