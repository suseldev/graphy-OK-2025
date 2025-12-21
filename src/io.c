#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "graph.h"

// inspired by nauty's function
void graphWriteToGraph6(const Graph *g, FILE *outputFile) {
	int i, j;
	if(!g || !outputFile) return;
	int n = g->n;
	if(n>62) return;

	// 1st character: number of verices
	fputc((char)(n+63), outputFile); //ASCII magic
	
	int bitCount = 0;
	int value = 0;

	for(i=0; i<n; i++) {
		for(j=i+1; j<n; j++) {
			value = (value << 1) | (g->adj[i][j]?1:0);
			bitCount++;

			if(bitCount==6){
				fputc((char)(value+63),outputFile);
				bitCount = 0;
				value = 0;
			}
		}
	}
	if (bitCount > 0) {
        value <<= (6 - bitCount);
        fputc((char)(value + 63), outputFile);
    }
}
