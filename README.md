# E4-Demonstration-of-a-Programming-Paradigm

# Parallel Game of Life (C++ with OpenMP)
## César Ignacio Saucedo Rodríguez A01712245

## Description

This project implements **Game of Life** using the **parallel programming paradigm**, specifically via **OpenMp** in C++. The simulation models cellular automata on a square matrix where cells live, die, or reproduce according to defined rules. It is a classic example of data-parallel processing, where each cell evolves independently based on its neighbors.

This problem was chosen because:

- It is a simple yet powerful example of how massive parallelism can be applied to a computational simulation.
- It maps naturally to grid-based processing, making it great to learn and use openMP.
- It allows for performance benchmarking between sequential and parallel paradigms.

---

## Context and Usefulness

Game of Life is not only a mathematical curiosity it’s a foundational concept in complexity science, simulation of populations, and distributed systems. A fast, parallel implementation makes it viable for real-times visualization and large-scale experimentation.

---

## Models

### Algorithm Logic

Each cell in the matrix is either **alive ('X')** or **dead ('.')**. At each generation, the cell's next state depends on the number of alive neighbors.

**Rules**:
- A live cell with fewer than 2 or more than 3 live neighbors dies.
- A live cell with 2 or 3 live neighbors lives.
- A dead cell with exactly 3 live neighbors becomes alive.

### Parallel Paradigm Use

- The evolution of each cell depends only on its immediate neighbors, enabling data parallelism
- OpenMP's `#pragma omp parallel for collapse(2)` is used to parallelize the two-level nested loop that processes the grid.
- Threads process rows and columns simultaneously, reducing computation time significantly.

### Diagram

![Diagrama del modelo paralelo](./Diagram.png)

## Implementation

- Language: **C++**
- Parallelization library: **OpenMP**
- User inputs matrix size and number of generations.
- Matrix is initialized randomly with alive/dead cells.
- Parallel region updates the grid across generations.

Files:
- `main.cpp`: Main program with simulation logic.
- `README.md`: Documentation (this file).

---

## Tests

The correctness of the implementation can be validated through:

- Manual inspection of output across generations.
- Use of controlled matrix input with known expected outputs.
- Ensuring edge boundaries behave correctly (no segmentation faults or invalid access).
- Execution with increasing matrix sizes (e.g., 10x10, 100x100) to validate stability.

Example test setup:

```bash
g++ -fopenmp -O2 life_game_omp.cpp -o life_game_omp
```

```bash
./life_game_omp.exe
```

```bash
Input:
Size of the Matrix: 10
Number of Generations: 10
```

Expected:
```bash
Initial State:
. . . . X . . . X X
. . X . . X . X . X 
. . X . . X X X X .
. X X . . X X . . .
. X . X . X . . . X 
. X X X . . X X X .
X X . . X X X . X .
. . . . . . . X X .
X . X X . . . X . X
. X X . . . X . X X 
-------------------------
Gen 1:
. . . . . . . . X X
. . . X X X . . . X 
. . X X X . . . X .
. X . X . . . . X .
X . . X . X . . X .
. . . X . . . . X X
X X . X X X . . . X
X . X X X X . . . X
. . X X . . X . . X 
. X X X . . . X X X
-------------------------
Gen 2:
. . . . X . . . X X
. . X . . X . . . X 
. . . . . X . . X X
. X . . . . . X X X
. . . X . . . X X . 
X X . X . X . . X X
X X . . . X . . . X
X . . . . . X . X X
. . . . . X X X . X
. X . X . . . X X X
-------------------------
Gen 3:
. . . . . . . . X X
. . . . X X . . . .
. . . . . . X X . .
. . . . . . X . . . 
X X . . X . X . . .
X X . . . . X X . X
. . X . X X X X . .
X X . . . . . . . X
. . . . . X . . . .
. . . . . . . X . X 
-------------------------
Gen 4:
. . . . . . . . . .
. . . . . X X X X .
. . . . . . X X . .
. . . . . . X . . .
X X . . . . X . . .
X . X X X . . . X .
. . X . . X . X . .
. X . . X . . . . .
. . . . . . . . X . 
. . . . . . . . . .
-------------------------
Gen 5:
. . . . . . X X . .
. . . . . X . . X .
. . . . . . . . X .
. . . . . X X . . .
X X X X . X . X . .
X . X X X X X X . .
. . X . . X . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . . 
-------------------------
Gen 6:
. . . . . . X X . .
. . . . . . X . X .
. . . . . X X X . .
. X X . X X X X . .
X . . . . . . X . .
X . . . . . . X . .
. X X . . X . . . . 
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
-------------------------
Gen 7:
. . . . . . X X . .
. . . . . . . . X . 
. . . . X . . . X .
. X . . X . . . X .
X . . . . X . X X .
X . . . . . X . . .
. X . . . . . . . . 
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
-------------------------
Gen 8:
. . . . . . . X . . 
. . . . . . . . X .
. . . . . . . X X X
. . . . X X . . X X
X X . . . X X X X .
X X . . . . X X . .
. . . . . . . . . . 
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
-------------------------
Gen 9:
. . . . . . . . . . 
. . . . . . . . . X
. . . . . . . X . .
. . . . X X . . . .
X X . . X . . . . X
X X . . . X . . X . 
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
-------------------------
Gen 10:
. . . . . . . . . . 
. . . . . . . . . .
. . . . . . . . . .
. . . . X X . . . .
X X . . X . . . . .
X X . . . . . . . . 
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
-------------------------

```
---

## Analysis

### Time Complexity

Let `N` be the size of the matrix:

- **Seqquential complexity**: O(N²) per generation (analyze every cell).
- **Parallel complexity**: O(N² / T) where `T` is the number of threads.

**Speedup** is ideally linear with the numbers of threads, although it is limited by:
- Synchronization overhead.
- Cache and memory bandwidth.

### Possible Alternative Paradigms
In response to feedback provided: "Improve the documentation for the other possible solutions."

## Other Possible Solutions: Alternative Paradigms

Below are other ways to implement the Game of Life, along with their applications and limitations:

| **Paradigm** | **Application** | **Advantages** | **Disadvantages** |
|------------------------|---------------------------------------------------------------------------|--------------------------------------------------|---------------------------------------------------------------------|
| **Functional** | Use pure functions to transform the array state without side effects. | More predictable and testable code. | Poor cache performance, higher control flow overhead. |
| **Object-Oriented** | Model each cell as an object with attributes (state, neighbors). | Code reuse, encapsulation. | High memory consumption and low efficiency for large arrays. |
| **Event-Driven** | Update cells only when a state change occurs (event-driven simulation). | Can be efficient if changes are few. | Dificult to implement correctly and almost impossible to parallelize. |

### Why was the **parallel** paradigm chosen?

The parallel approach is best suited for this problem because:

- It works on large matrices, where each cell can be processed independently.
- Parallelization (using OpenMP) allows iterations to be divided by rows or blocks.
- It maximizes the use of multiple CPU cores, significantly reducing execution time.

## Conclusion

This project demonstrates how **parallel programming** dramatically reduces computation time for problems with **independent data points**, such as Game of Life. OpenMP offers a simple and effective way to leverage modern multi-core processors with minimal code changes and helps me to understand in a easy way to implement openMP.

##Bibliography 

- Conway, J. H. (1970). *Game of Life*. Scientific American, 223(4), 4–7.  
- OpenMP Architecture Review Board. (2018). *OpenMP Application Programming Interface Version 5.0*. https://www.openmp.org/specifications/   
- Malik, D. S. (2011). *C++ Programming: Program Design Including Data Structures* (6th ed.). Cengage Learning.
- Kowalski, M. (n.d.). *Parallel programming examples* [Source code]. GitHub. https://github.com/mateuszk098/parallel-programming-examples

