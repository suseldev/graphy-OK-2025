# Graphy
Project made for combinatorial optimization classes implementing heuristic algorithms searching for integral graphs.

## Build
Graphy is written in C and uses the GNU Scientific Library (GSL) for spectral computations.
### Requirements
- GCC compiler
- GNU Make
- GSL (libgsl)
#### Installing GSL
  - Debian-based systems:
  `sudo apt install libgsl-dev`
  - Arch Linux based systems:
  `sudo pacman -S gsl`
### Compilation
To build all binaries, run:
```
$ make all
```
The compiled executables will be placed in `bin/` directory.

### Cleaning build artifacts
To clean build artifacts, run:
```
$ make clean
```

## Usage
Each algorithm is provided as a separate executable. All programs share the same command-line interface. Generated output is in the graph6 format.
### General form
`./graphy_<algorithm> [-qI] [-s <seed>] [-w <outfile] n k`

where:

- `n` (**required**): number of vertices
- `k` (**required**): number of edges
- `-q`: Quiet mode: prints only generated graphs in graph6 format.
- `-I`: Disables internal integrity checks, returning the first generated graph without verifying whether its spectrum is integral. Useful when piping the output to external tools (e.g. `sito5`).
- `-s`: Sets the seed for initializing RNG.
- `-w <outfile>`: Writes generated graphs to a file instead of a standard output

### Examples
Generate a random connected integral graph with 6 vertices and 9 edges:

`./graphy_random 6 9`

Run the greedy heuristic with quiet output and a fixed seed:

`./graphy_greedy -q -s 12345 6 9`

Generate graphs and pipe them to an external filter:

`./graphy_rand_greedy -qI 6 9 | ./sito5`


