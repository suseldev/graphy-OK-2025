#include <stdlib.h>
#include <gsl/gsl_matrix.h>

#include "graph.h"
#include "graph_gsl.h"

gsl_matrix *graphConvertToGSLMatrix(const Graph *g) {
	int i, j;
    if (!g) return NULL;
    gsl_matrix *TargetMat = gsl_matrix_alloc(g->n, g->n);
    if (!TargetMat) return NULL;
    for(i=0; i<g->n; i++) {
        for(j=0; j<g->n; j++) {
            gsl_matrix_set(TargetMat, i, j, (double)g->adj[i][j]);
        }
    }
    return TargetMat;
}

