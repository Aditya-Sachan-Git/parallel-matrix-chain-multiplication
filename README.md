# ⚡ Parallel Matrix Chain Multiplication using OpenMP

A performance-oriented implementation of the Matrix Chain Multiplication (MCM) problem using Dynamic Programming and OpenMP.

This project compares sequential execution with multiple OpenMP parallelization strategies on 4-core, 8-core, and 12-core systems to evaluate scalability and performance improvements.

---

## Features

- Sequential Dynamic Programming implementation
- Top-down Memoization
- Bottom-up Dynamic Programming
- OpenMP Parallelization
- Task-based Parallelism
- Loop-level Parallelism
- Automatic Input Generator
- Performance Benchmarking
- Execution Time Comparison

---

## Technologies Used

- C
- OpenMP
- Python (Input Generation)

---

## Algorithms

### Sequential

- Top-down Dynamic Programming
- Memoization
- Recursive Solution

---

### Parallel

- Bottom-up Dynamic Programming
- OpenMP Tasks
- OpenMP Taskloop
- Parallel For
- Dynamic Scheduling
- Guided Scheduling

---

## Project Structure

```
        Input Generator
               │
               ▼
         Input Dataset
               │
               ▼
        Sequential MCM
               │
        ┌──────|───────┐
        ▼              ▼
 Parallel 4      Parallel 8
        │              │
        └──────┬───────┘
               ▼
        Parallel 12
               │
               ▼
    Performance Comparison
```

---

## Implementations

### Sequential

- Recursive DP
- Memoization

### Parallel (4 Cores)

- Task-based Parallelism
- OpenMP Taskloop
- Grain Size = 10

### Parallel (8 Cores)

- Guided Scheduling
- OpenMP Tasks
- Grain Size = 15

### Parallel (12 Cores)

- Loop-level Parallelization
- Dynamic Scheduling

---

## Performance

| Implementation | Speedup |
|---------------|---------:|
| Sequential | 1× |
| Parallel (4 Cores) | 2.3× |
| Parallel (8 Cores) | 5.1× |
| Parallel (12 Cores) | 6.35× |

---

## Build

Compile using GCC with OpenMP support

```bash
gcc seq_exec.c -o seq

gcc -fopenmp par_4_cores.c -o par4

gcc -fopenmp par_8_cores.c -o par8

gcc -fopenmp par_12_cores.c -o par12
```

---

## Run

Sequential

```bash
./seq
```

Parallel

```bash
./par4

./par8

./par12
```

---

## Input

The input generator creates random matrix dimensions.

```bash
python generate.py
```

---

## Future Improvements

- CUDA Implementation
- MPI Version
- Hybrid MPI + OpenMP
- Cache Blocking
- SIMD Optimization
- GPU Benchmarking
- Visualization Dashboard

---

## Learning Outcomes

This project strengthened my understanding of

- Dynamic Programming
- Matrix Chain Multiplication
- OpenMP
- Parallel Programming
- Multithreading
- Load Balancing
- Performance Optimization
- Benchmarking
- High Performance Computing

