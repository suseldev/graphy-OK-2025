#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "constants.h"
#include "config.h"
#include "graph.h"
#include "heuristics_rand_greedy.h"
#include "io.h"

int main(int argc, char **argv) {
    CliConfig cfg = cliParse(argc, argv);
    Graph *g = NULL;
    if(cfg.integralityCheck) {
        g = heuristicsRandomGreedyGenerateIntegralGraph(cfg.n, cfg.k, RANDGREEDY_PRAND);
    } else {
        g = heuristicsRandomGreedyGenerateGraph(cfg.n, cfg.k, RANDGREEDY_PRAND);
    }
    if (!g) {
        fprintf(stderr, "Error: Failed to generate graph!\n");
        return 1;
    }
    if (!QUIET) {
        printf("[Greedy] n=%d k=%d%s\n", cfg.n, cfg.k, cfg.integralityCheck ? " (integrality check enabled)":"");
    }
    FILE *out = stdout;
    if (cfg.outFile) {
        out = fopen(cfg.outFile, "a");
        if (!out) {
            perror("fopen");
            graphFree(g);
            return 1;
        }
    }
    graphWriteToGraph6(g, out);
    fputc('\n', out);
    if (out != stdout) fclose(out);
    graphFree(g);
    return 0;
}
