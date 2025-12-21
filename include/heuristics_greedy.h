#ifndef HEURISTICS_GREEDY_H
#define HEURISTICS_GREEDY_H

#include "graph.h"

// used in rand greedy
bool greedyAddBestEdge(Graph *g);
Graph *heuristicsGreedyGenerateGraph(int n, int k);
Graph *heuristicsGreedyGenerateIntegralGraph(int n, int k);

#endif
