# Code documentation

## cli (`include/cli.h`)
- `CliConfig` (`struct`): Structure representing parsed command line options.

  - `n` (`int`): Number of vertices in the generated graph.

  - `k` (`int`): Number of edges in the generated graph.

  - `seed` (`unsigned int`): Seed used to initialize the RNG. If set to `0`, a default value (`time(NULL)`) is used.

  - `quiet` (`bool`): Controls output verbosity (if `true`, only graph6 representations are printed).

  - `integralityCheck` (`bool`): Controls whether generated graphs are checked for spectral integrity.

  - `outFile` (`const char *`): Path to the output file. If `NULL`, output is written to standard output

- `CliConfig cliParse(int argc, char **argv)`: Parses command line arguments and returns populated CliConfig structure. Parameters `argc` and `argv` are argument count and argument vector passed to main. Returns fully initialized CliConfig structure. This function should terminate the program with an error message on invalid input.

## config (`include/config.h`)
- `INTEGRALITY_CHECK_ENABLED` (`bool`):

Controls whether the generated graphs are filtered by the integrality condition before being returned.

  - `true`: All heuristic methods verify whether the generated graph is spectrally integral. Only graphs satisfying this condition will be returned.

  - `false`: All generated graphs are returned without internal verification. This mode is intended for external post-processing (for example piping the output to tools such as `sito5`).

- `QUIET` (`bool`):

  Controls the output format.

  - `true`: Displays only generated graphs in graph6 format.

  - `false`: Displays additional debug information and generated graphs.

## constants (`include/constants.h`)

- `EIGEN_T` (`double`): Numerical tolerance used when checking whether an eigenvalue is considered integral. (defaults to `1e-15`).

- `NON_INTEGRAL_PENALTY` (`double`): Penalty factor when computing the integrality score of non-integral eigenvalues.

- `RANDGREEDY_PRAND` (`double`): pRand parameter used for greedy random algorithm.

## graph (`include/graph.h`)
- `Graph` (`struct`): Structure describing the graph

 - `n` (`int`): number of vertices

 - `edges` (`int`): number of edges

 - `adj` (`int**`): adjacency matrix

### Creating and destroying graphs
- `Graph *graphCreate(int n)`: Creates the empty graph and returns it.

- `void graphFree(Graph *g)`: Destroys the graph, freeing the memory

### Basic graph operations
- `bool graphAddEdge(Graph *g, int a, int b)`: Adds the edge `(a, b)` to graph `g`.
Returns `true` if operation was successful, `false` if not.

- `bool graphAddEdge(Graph *g, int a, int b)`: Removes the edge `(a, b)` from graph `g`
Returns `true` if operation was successful, `false` if not.

- `bool graphHasEdge(Graph *g, int a, int b)`: Checks whether the edge exists in the graph. Returns `true` if edge exists, `false` if not.

### Additional graph utilities
- `void graphClear(Graph *g)`: Clears the graph while keeping the allocated structure.
- `Graph *graphCopy(const Graph *g)`: Copies the graph. Returns copied graph.

## Graph GSL (`include/graph_gsl.h`)
- `gsl_matrix graphConvertToGSLMatrix(Graph *g)`: Converts the graph adjacency list to GSL matrix. Returns: `gsl_matrix`.

## Heuristics Common (`include/heuristics_common.h`)
- `void graphMakeRandomTree(Graph *g)`: Expects an empty graph. Creates a random tree structure using the algorithm described in [algorithms](algorithms.md) section.

## Heuristics Greedy (`include/heuristics_greedy.h`)
- `bool greadyAddBestEdge(Graph *g)`: Performs a single greedy step by selecting and adding the edge that maximizes the integrity score.
Returns `true` if an edge was successfuly added, `false` otherwise.

- `Graph *heuristicsGreedyGenerateGraph(int n, int k)`: Generates a connected graph with `n` vertices and `k` edges using the algorithm described in [algorithms](algorithms.md) section. Returns: a pointer to the generated graph or `NULL` if graph generation fails.

- `Graph *heuristicsGreedyGenerateIntegralGraph(int n, int k)`: Repeatedly generates graphs using the greedy heuristic until a spectrally integral graph is found. Returns: a pointer to a spectrally integral graph or `NULL` if graph generation fails.

## Heuristics Greedy Random (`include/heuristics_rand_greedy.h`)
- `Graph *heuristicsRandomGreedyGenerateGraph(int n, int k, double pRand)`: Generates a connected graph with `n` vertices and `k` edges using the algorithm described in [algorithms](algorithms.md) section. Parameter `pRand` is the probability of performing a random step. Returns: a pointer to a generated graph or `NULL` if graph generation fails.

- `Graph *heuristicsRandomGreedyGenerateIntegralGraph(int n, int k, double pRand)`: Repeatedly generates graphs using the randomized greedy heuristic until a spectrally integral graph is found. Returns: a pointer to a spectrally integral graph or `NULL` if graph generation fails.

## Heuristics Random (`include/heuristics_random.h`)
- `Graph *heuristicsRandomGenerateGraph(int n, int k)`:  Generates a connected graph with `n` vertices and `k` edges using the algorithm described in [algorithms](algorithms.md) section. Returns: a pointer to a generated graph or `NULL` if graph generation fails.

- `Graph *heuristicsRandomGenerateIntegralGraph(int n, int k, double pRand)`: Repeatedly generates graphs using the `heuristicRandomGenerateGraph` until a spectrally integral graph is found. Returns: a pointer to a spectrally integral graph or `NULL` if graph generation fails.

## IO (`include/io.h`)
- `void graphWriteToGraph6(const Graph *g, FILE *outputFile)`: Exports the graph `g` to the `outputFile` in graph6 format.


## Spectrum (`include/spectrum.h`)
- `bool spectrumCalculateEigenvalues(Graph *g, double *eigenValues)`: Computes all eigenValues of the adjacency matrix of graph `g`. Parameter `eigenValues` should be an output array of size `g->n` where computed eigenvalues will be stored. Returns `true` if computation was successful, `false` if it fails due to invalid input or allocation errors.

- `double spectrumIntegralScore(Graph *g)`: Computes the integrality score of the graph spectrum. Definition of the score function can be found in [algorithms](algorithms.md) section.

- `bool spectrumIsIntegral(Graph *g)`: Checks whether the spectrum of graph `g` is integral within a numerical tolerance (found in `include/constants.h`). Returns: `true` if all eigenvalues are integral, `false` otherwise.
