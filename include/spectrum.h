#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <stdbool.h>
#include "constants.h"
#include "graph.h"

// eigenvalues must point to an array of size g->n
bool spectrumCalculateEigenvalues(const Graph *g, double *eigenValues);

double spectrumIntegralScore(const Graph *g);

bool spectrumIsIntegral(const Graph *g);

#endif
