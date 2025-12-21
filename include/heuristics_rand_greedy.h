#ifndef HEURISTICS_RANDOM_GREEDY_H
#define HEURISTICS_RANDOM_GREEDY_H

#include "graph.h"
#include "heuristics_common.h"

Graph *heuristicsRandomGreedyGenerateGraph(int n, int k, double pRand);
Graph *heuristicsRandomGreedyGenerateIntegralGraph(int n, int k, double pRand);

#endif
