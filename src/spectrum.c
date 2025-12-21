#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_eigen.h>

#include "spectrum.h"
#include "constants.h"
#include "graph.h"
#include "graph_gsl.h"
#include "config.h"

bool spectrumCalculateEigenvalues(const Graph *g, double *eigenValues) {
	int i;
	// another sanity check
	if(!g || !eigenValues) return false;

	gsl_matrix *matrix = graphConvertToGSLMatrix(g);
	if(!matrix) return false;

	gsl_vector *eigenValuesGSL = gsl_vector_alloc(g->n);
	gsl_eigen_symm_workspace *workspace = gsl_eigen_symm_alloc(g->n);

	if(!eigenValuesGSL || !workspace) {
		if(eigenValuesGSL) gsl_vector_free(eigenValuesGSL);
		if(workspace) gsl_eigen_symm_free(workspace);
		gsl_matrix_free(matrix);
		return false;
	}

    gsl_eigen_symm(matrix, eigenValuesGSL, workspace);

    for(i=0; i<g->n; i++) {
        eigenValues[i] = gsl_vector_get(eigenValuesGSL, i);
    }

    gsl_vector_free(eigenValuesGSL);
    gsl_eigen_symm_free(workspace);
    gsl_matrix_free(matrix);
    return true;
}

double spectrumIntegralScore(const Graph *g) {
	int i;
	double score = 0.0;
	if(!g) return -INFINITY; // woah
	
	double *eigenValues = malloc(g->n * sizeof(double));
	if(!eigenValues) return -INFINITY; //woah

	if(!spectrumCalculateEigenvalues(g, eigenValues)) {
		free(eigenValues);
		return -INFINITY; //woah
	}
	for(i=0; i<g->n; i++) {
		double lambda = eigenValues[i];
		double nearest = round(lambda);
		double diff = fabs(lambda - nearest);
		if(diff < EIGEN_T) {
			score += 1.0;
		} else {
			score -= NON_INTEGRAL_PENALTY * diff;
		}
	}
	free(eigenValues);
	return score;
}

bool spectrumIsIntegral(const Graph *g) {
	int i;
	if(!g) return false;
	double *eigenValues = malloc(g->n * sizeof(double));
	if(!eigenValues) return false;

	if(!spectrumCalculateEigenvalues(g, eigenValues)) {
		free(eigenValues);
		return false;
	}
	for(i=0; i<g->n; i++) {
		if(!QUIET) printf("[Spectrum] Calculated eigenvalue: %.15f\n", eigenValues[i]);
		if(fabs(eigenValues[i] - round(eigenValues[i])) >= EIGEN_T) {
			if(!QUIET) printf("[Spectrum] Graph not integral\n");
			free(eigenValues);
			return false;
		}
	}
	free(eigenValues);
	return true;
}
