#ifndef GRAPH_GSL_H
#define GRAPH_GSL_H

#include <gsl/gsl_matrix.h>
#include "graph.h"

gsl_matrix *graphConvertToGSLMatrix(const Graph *g);

#endif
