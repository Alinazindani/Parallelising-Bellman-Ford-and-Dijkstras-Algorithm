# Parallelizing Dijkstra and Bellman-Ford Algorithms

This project contains implementations of both the sequential and parallelized versions of Dijkstra's and Bellman-Ford algorithms, along with graph generators to create datasets of varying sizes for testing and benchmarking.

---

## Folder Structure

- `dijkstra/`  
  Contains code for Dijkstra's algorithm, including:
  - `dijkstra.c`: Parallelized implementation.
  - `seq_dijkstra.c`: Sequential implementation.
  - `generate.c`: Graph generator. Change the number of vertices in the code to generate graphs of different sizes.
  - `README.md`: Explains the files and their purposes within this folder.

- `Bellman_ford/`  
  Contains code and notebooks related to the Bellman-Ford algorithm:
  - `graph-gen`: Dataset generator (graphs).
  - `Bellman_seq`: Sequential Bellman-Ford algorithm.
  - `bellman_parallel`: Parallelized Bellman-Ford algorithm.
  - Jupyter notebooks for analysis and experimentation.

---

## How to Use

### Dijkstra

1. Use `generate.c` to create graphs of desired sizes by adjusting the vertex count in the source code.
2. Run `seq_dijkstra.c` to execute the sequential version of Dijkstra’s algorithm.
3. Run `dijkstra.c` for the parallelized version.

### Bellman-Ford

- Run `graph-gen` to generate graph datasets.
- Run `Bellman_seq` for the sequential Bellman-Ford algorithm.
- Run `bellman_parallel` for the parallelized version.

---

## Compilation and Running

Example commands to compile and run the code:

```bash
# Compile Dijkstra code
gcc dijkstra/dijkstra.c -o dijkstra/dijkstra
gcc dijkstra/seq_dijkstra.c -o dijkstra/seq_dijkstra
gcc dijkstra/generate.c -o dijkstra/generate

# Run graph generation
./dijkstra/generate

# Run sequential Dijkstra
./dijkstra/seq_dijkstra

# Run parallelized Dijkstra
./dijkstra/dijkstra

# Similarly for Bellman-Ford, adjust paths and filenames
