#ifndef HEURISTICS_EVO_H
#define  HEURISTICS_EVO_H

#include "graph.h"

Graph *heuristicsEvoGenerateGraph(int n, int k, int populationSize, int generations);

Graph *heuristicsEvoGenerateIntegralGraph(int n, int k, int populationSize, int generations);

#endif
