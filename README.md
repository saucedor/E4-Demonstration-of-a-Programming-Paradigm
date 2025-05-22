# E4-Demonstration-of-a-Programming-Paradigm

# Parallel Game of Life (C++ with OpenMP)
## César Ignacio Saucedo Rodríguez A01712245

## Description

This project implements **Game of Life** using the **parallel programming paradigm**, specifically via **OpenMP** in C++. The simulation models cellular automata on a square matrix where cells live, die, or reproduce according to defined rules. It is a classic example of data-parallel processing, where each cell evolves independently based on its neighbors.

This problem was chosen because:

- It is a simple yet powerful example of how massive parallelism can be applied to a computational simulation.
- It maps naturally to grid-based processing, making it great to learn and use OpenMP.
- It allows for performance benchmarking between sequential and parallel paradigms.

---

## Context and Usefulness

Game of Life is not only a mathematical curiosity—it’s a foundational concept in complexity science, simulation of populations, and distributed systems. A fast, parallel implementation makes it viable for real-times visualization and large-scale experimentation.

---

## Models

### Algorithm Logic

Each cell in the matrix is either **alive ('X')** or **dead ('.')**. At each generation, the cell's next state depends on the number of alive neighbors.

**Rules**:
- A live cell with fewer than 2 or more than 3 live neighbors dies.
- A live cell with 2 or 3 live neighbors lives.
- A dead cell with exactly 3 live neighbors becomes alive.

### Parallel Paradigm Use

- The evolution of each cell depends only on its immediate neighbors, enabling **data parallelism**.
- OpenMP's `#pragma omp parallel for collapse(2)` is used to parallelize the two-level nested loop that processes the grid.
- Threads process rows and columns simultaneously, reducing computation time significantly.

### Diagram

