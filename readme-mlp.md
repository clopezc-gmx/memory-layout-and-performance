# nbody-core-cpp

Scalable short-range n-body engine in modern C++20.

Designed to demonstrate algorithmic scaling, spatial decomposition, and clean hot-loop performance engineering.
Structured for MPI domain decomposition and optional Python-based control integration.

Implements:

- O(N²) baseline kernel
- O(N) neighbor search via cell lists
- Data-oriented layouts (AoS / SoA)
- Deterministic update loop
- Validation tests and benchmark mode

## Origin

Inspired by the educational Lennard-Jones MD reference implementation
[https://github.com/akohlmey/ljmd-c/blob/master/src/ljmd.c](https://github.com/akohlmey/ljmd-c/blob/master/src/ljmd.c)

This version redesigns the structure in modern C++20 with a focus on performance, modularity, and scalability.

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

## Run

```bash
./build/nbody --n 50000 --steps 200
```

