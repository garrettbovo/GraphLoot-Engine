# GraphLoot Engine

[![Build and Test](https://github.com/garrettbovo/GraphLoot-Engine/actions/workflows/build.yml/badge.svg)](https://github.com/garrettbovo/GraphLoot-Engine/actions/workflows/build.yml)
![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
![CMake](https://img.shields.io/badge/build-CMake-064F8C?logo=cmake&logoColor=white)
![Threads](https://img.shields.io/badge/concurrency-std::thread-orange)

A C++17 simulation engine that computes optimal routes across a weighted graph and runs
probabilistic outcome models at scale. Implements **Dijkstra and A\*** over an adjacency-list
graph, parallelizes **1,000,000+ simulation runs** across cores with `std::thread`, and is
driven entirely by CSV configuration — no game data is hardcoded.

The reference world is modeled on Fortnite points of interest, but the engine is domain-agnostic:
swap the CSVs and it routes any weighted graph.

<a href="https://garrettbovo.github.io/GraphLootWASM/">
  <img src="https://raw.githubusercontent.com/garrettbovo/GraphLootWASM/main/Videos/demo.gif" alt="Interactive graph visualization demo" width="800">
</a>

**[→ Open the interactive demo](https://garrettbovo.github.io/GraphLootWASM/)** · **[→ Run it on OnlineGDB](https://onlinegdb.com/Ay8gTHQf_)** (no account needed)

---

## Benchmark: A\* vs. Dijkstra

Both algorithms run over the same graph structure. A\* adds a Euclidean-distance heuristic from
`Nodes.csv` to bias expansion toward the goal. The engine ships a benchmark harness that times
both across **1,000 iterations per scenario** with `std::chrono::high_resolution_clock` and
reports nodes expanded alongside wall time.

On large graphs, **A\* explores ~97% fewer nodes and runs ~3.1× faster** than Dijkstra, while
returning an identical-cost path.

Reproduce it yourself:

```bash
cmake -S . -B build && cmake --build build
./build/test_benchmark
```

The harness measures three scenarios — the 8-node POI graph, a 15×15 grid, and a 30×30 grid —
so you can watch the heuristic's advantage grow with graph size. On the small POI graph the two
are near-identical; the gap opens up as the search space expands. CI runs this on every push.

---

## Quickstart

Requires a C++17 compiler (GCC 7+, Clang 5+, MSVC 2017+) and CMake 3.16+.

```bash
git clone https://github.com/garrettbovo/GraphLoot-Engine.git
cd GraphLoot-Engine
cmake -S . -B build && cmake --build build
```

Run interactively — pick a drop spot, choose a destination, watch the engine route you there:

```bash
./build/engine --map DefaultMap.csv --loot Items.csv --nodes Nodes.csv --algorithm dijkstra --runs 1
```

Run a large-scale simulation:

```bash
./build/engine --map DefaultMap.csv --loot Items.csv --nodes Nodes.csv --algorithm dijkstra --runs 1000000
```

Compare both algorithms and write cost, nodes explored, and timing to `CompareAlgorithms.txt`:

```bash
./build/engine --map DefaultMap.csv --loot Items.csv --nodes Nodes.csv --algorithm compare --runs 1
```

| Flag | Values | Purpose |
|---|---|---|
| `--map` | CSV path | Graph topology (POIs and weighted edges) |
| `--loot` | CSV path | Item definitions, types, and rarity tiers |
| `--nodes` | CSV path | 2-D POI coordinates, used as the A\* heuristic |
| `--algorithm` | `dijkstra` \| `astar` \| `compare` | Pathfinding strategy |
| `--runs` | integer | 1 for interactive mode, N for batch simulation |

A `Makefile` is also provided (`make`, `make run`, `make simulate`). Running the binary with no
arguments falls back to `DefaultMap.csv`, `Items.csv`, and a single interactive run — which is how
the OnlineGDB demo works, since it can't pass CLI arguments.

### Example session

```
Select a drop spot: Anvil Square
Current Location: Anvil Square
Enter your choice: 1
Where would you like to go?: Shattered Slabs

Fastest route:
Anvil Square -> Slappy Shores -> Faulty Splits -> Shattered Slabs

Travel this route? (Yes/No): Yes
Arrived at Slappy Shores!
Arrived at Faulty Splits!
Arrived at Shattered Slabs!
```

---

## How It Works

### World graph

The world is an **undirected weighted graph** stored as an **adjacency list** — each node is a
point of interest, each edge a traversable path whose weight encodes relative traversal cost.
Adjacency-list storage keeps memory proportional to actual edges and makes neighbor lookup fast,
which matters once the batch simulator is expanding millions of paths.

Topology is loaded from CSV at startup, so map changes require no recompilation.

### Dijkstra

A **priority-queue-driven implementation** keyed on cumulative cost, using `std::priority_queue`
with a custom comparator over an `std::unordered_map` adjacency list. Rather than returning only
a final distance, it maintains **distance and predecessor maps** and reconstructs the full POI
sequence, so the result drives step-by-step traversal and loot generation directly.

**Time complexity:** O(E log V) with a binary heap.

### A\* search

A\* reuses the same graph structure and adds a **Euclidean-distance heuristic** from 2-D
coordinates in `Nodes.csv`, tracking g-scores, f-scores, and predecessors. Because the heuristic
never overestimates true remaining cost, it stays **admissible** — A\* returns the same optimal
path as Dijkstra while expanding a fraction of the nodes.

Select at runtime with `--algorithm astar`, or `--algorithm compare` to run both and dump the
comparison.

### Parallel simulation

Running 1,000,000+ simulations sequentially is wall-clock prohibitive — even at microseconds per
run, single-threaded execution leaves multi-core hardware idle. The engine partitions the batch
across `std::thread` workers and aggregates under a mutex.

- Worker threads each execute an independent slice of the batch (e.g. 250,000 runs per core on a 4-core machine)
- Each thread keeps **thread-local counters** for rarity and weapon distributions, eliminating contention in the hot loop
- Results merge into a shared aggregator at thread completion under a single `std::mutex` lock, so no locking occurs during simulation
- Worker count comes from `std::thread::hardware_concurrency()` for portable scaling

Because the workload is CPU-bound with negligible shared state, this scales near-linearly with
core count up to memory-bandwidth limits.

### Data-driven design

| File | Contents |
|---|---|
| `DefaultMap.csv` | POI nodes and weighted edges |
| `Nodes.csv` | 2-D coordinates backing the A\* heuristic |
| `Items.csv` | 5 item types across 5 rarity tiers |
| `TestMap.csv` | Smaller graph for debugging |

Adding items, rarities, or map regions is a CSV edit. The engine is architected around a
polymorphic `World` base class with a `FortniteWorld` derived implementation, so a new domain
means a new subclass rather than changes to the traversal core.

---

## Testing

Deterministic tests validate both algorithms against known graph configurations, covering:

- Dijkstra shortest-path routing
- A\* routing with node-coordinate heuristics
- Identical start and destination
- Unreachable destinations
- A\* and Dijkstra returning equal-cost paths

```bash
./build/test_dijkstra
./build/test_astar
./build/test_benchmark
```

CI runs all three on every push and pull request.

---

## Simulation Results

Example output from 1,000,000 runs, demonstrating statistically stable distributions across a
large sample — which is what validates the weighted probability model:

```
========================================
      GRAPH LOOT ENGINE RESULTS
========================================

Simulation Runs: 1000000
Steps per Run: 5
Total Loot Rolls: 3654143

----------------------------------------
Rarity Distribution
----------------------------------------
Common      : 26.32 % (961837)
Uncommon    : 26.30 % (960857)
Rare        : 26.23 % (958432)
Epic        : 13.66 % (498975)
Legendary   : 6.74  % (246257)

----------------------------------------
Weapon Type Distribution
----------------------------------------
AR          : 38.05 % (1390394)
Shotgun     : 24.67 % (901531)
SMG         : 29.16 % (1065504)
Heavy       : 7.33  % (267871)

========================================
```

---

## Project Structure

```
GraphLoot-Engine/
├── main.cpp                    # Entry point and CLI argument parsing
├── Game.cpp/.hpp               # Core loop and simulation control
├── GameUtils.cpp/.hpp          # Game logic helpers
│
├── World.cpp/.hpp              # Abstract world base class
├── FortniteWorld.cpp/.hpp      # Concrete world implementation
├── WorldGraph.cpp/.hpp         # Graph, Dijkstra, and A* search
├── Entry.cpp/.hpp              # POI / node representation
├── Chest.cpp/.hpp              # Loot container logic
│
├── Item.cpp/.hpp               # Base item type
├── Weapon.cpp/.hpp             # Weapon specialization of Item
├── ItemDatabase.cpp/.hpp       # CSV-driven item loading
├── LootPool.cpp/.hpp           # Weighted probability drop system
│
├── tests/
│   ├── test_dijkstra.cpp       # Dijkstra correctness
│   ├── test_astar.cpp          # A* correctness
│   └── test_benchmark.cpp      # A* vs Dijkstra timing harness
│
├── DefaultMap.csv              # Default graph topology
├── TestMap.csv                 # Debug graph
├── Items.csv                   # Item definitions
├── Nodes.csv                   # POI coordinates (A* heuristic)
│
├── .github/workflows/build.yml # CI: build + run all tests
├── CMakeLists.txt              # Primary build system
└── Makefile                    # Alternative build
```

---

## Engineering Notes

- **Modern C++17** — STL containers and algorithms, RAII, structured bindings, templates, inheritance and polymorphism
- **Concurrency** — `std::thread`, `std::mutex`, thread-local accumulation, `hardware_concurrency()`
- **Algorithms** — graph traversal, shortest path, admissible heuristics, priority queues, benchmarking methodology
- **Build and CI** — CMake, Make, GitHub Actions running build and regression checks on every push
