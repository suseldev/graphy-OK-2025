# Implemented algorithms

## Spectral algorithms (`src/spectrum.c`)
### Eigenvalues calculation
Eigenvalues calculation is done using GSL functions.

### Calculation of spectral integrality score
To guide heuristic algorithms during graph construction, a numerical score is assigned to each candidate graph.

- For each eigenvalue, its distance to the nearest integer is computed.

    - If an eigenvalue is close to one (smaller than `EIGEN_T`, found in `include/constants.h`), a `1` is added to the score.

    - Otherwise, the score is decreased proportionally to the distance from the nearest integer:

        - `score = score - NON_INTEGRAL_PENALTY*(eigenvalue-round(eigenvalue))`

`NON_INTEGRAL_PENALTY` can be modified in `include/constants.h` file.

## Heuristic algorithms
### Random (`src/heuristic_random.c`)
1) We start from the random tree to guarantee connectivity. This is done by iteratively connecting each vertex i (`i=0, ..., n-1`) to a randomly chosen vertex (`0, ..., i-1`)

2) While the number of edges is smaller than `k`, random pairs of distinct vertices is selected. If an edge does not already exist, it is added to the graph.

3) If integrality checking is enabled, the selected graph is tested for spectral integrality.

### Greedy (`src/heuristic_greedy.c`)
1) We start from the random tree to guarantee connectivity, using the same algorithm as before.

2) While the number of edges is smaller than `k`, the algorithm considers all possible edges not already present in the graph, temporarily adding it, calculating the integrality score and removing it.. The edge with the highest score improvement is then added to the graph.

3) If integrality checking is enabled, the selected graph is tested for spectral integrality.

### Greedy Random (`src/heuristic_rand_greedy.c`)
1) We again start from the random tree.

2) While the number of edges is smaller than `k`, the algorithm performs one of two actions:

- with probability `pRand`: a random missing edge is selected and added to the graph

- with probability `1-pRand`: the greedy strategy is applied.

3) If integrality checking is enabled, the selected graph is tested for spectral integrality.

The parameter `pRand` (found in `include/constants.h`, named `RANDGREEDY_PRAND`) controls the balance:

- `pRand=0` reduces the algorithm to the pure greedy heuristics

- `pRand=1` reduces it to the purely random construction

- intermediate values mix both approaches to the problem.

### Evolutionary (`src/heuristics_evo.c`)
1) We initialize the population, generating it using the same algorithm.

2) For each generation, all individuals in the population are evaluated using the integrality score.

3) The best performing individuals are selected for the next generation.

4) New candidate graphs are produced by applying random mutations to selected individuals (replacing one edge with another, while preserving the total number of edges).

5) The population is iteratively updated.

6) If integral checking is enabled, the resulting graph is tested for spectral integrality.
