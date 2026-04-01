<body>

<header>
  <h1>Fortnite Graph Loot Engine</h1>
  <p>
    A configurable C++ simulation engine that models traversal across a weighted graph while generating probabilistic loot outcomes. Designed to analyze loot distributions and traversal behavior using large-scale simulation.
  </p>

  <p><strong>Supports both interactive gameplay and large-scale simulation via a command-line interface.</strong></p>

  <h2>How to Run the Code</h2>
<p>
  You can run this project directly in your browser without creating an account:
  <a href="https://onlinegdb.com/Ay8gTHQf_" target="_blank">
    👉 Click here to open on OnlineGDB
  </a>
</p>

<p>
  ⚠️ OnlineGDB is intended for quick interactive demos only.  
  For full simulation capabilities, run locally using the Makefile.
</p>
</header>

<details>
  <summary><strong>Table of Contents 📖</strong></summary>
  <ul>
    <li><a href="#overview">Overview</a></li>
    <li><a href="#features">Key Features</a></li>
    <li><a href="#structure">Project Structure</a></li>
    <li><a href="#graph">World Graph Design</a></li>
    <li><a href="#algorithms">Algorithms Used</a></li>
    <li><a href="#gameplay">Gameplay Flow</a></li>
    <li><a href="#skills">Skills Demonstrated</a></li>
    <li><a href="#usage">How to Run</a></li>
    <li><a href="#results">Results</a></li>
  </ul>
</details>

<section id="overview">
  <h2>Overview</h2>
  <p>
    GraphLoot Engine simulates a player moving through a graph of Points of Interest (POIs), collecting loot at each step. The system supports both single-run execution and large-scale simulations to analyze statistical outcomes.

    The engine is fully data-driven:
  </p>
  <ul>
    <li>Map topology is loaded from CSV files</li>
    <li>Loot tables are externally configurable</li>
    <li>Runtime behavior is controlled via CLI arguments</li>
  </ul>
</section>

<section id="features">
  <h2>Features</h2>

<li> <strong>Data-Driven Design</strong> <ul> <li>Map and loot systems loaded from CSV files</li> <li>No hardcoded game data</li> </ul> </li> <li> <strong>Simulation Engine</strong> <ul> <li>Supports large-scale runs (e.g., 1,000,000+ simulations)</li> <li>Fixed-step traversal model</li> <li>Interactive and simulation modes</li> </ul> </li> <li> <strong>Statistical Analysis</strong> <ul> <li>Rarity and weapon type distribution tracking</li> <li>Percentage-based output with counts</li> </ul> </li> <li> <strong>CLI Interface</strong> <ul> <li>Flexible runtime configuration</li> <li>Supports optional and required parameters</li> </ul> </li>
</section>

<section id="structure">
  <h2>Project Structure</h2>
  <pre>
GraphLoot-Engine/
│
├── main.cpp                 # Program entry point
├── Game.cpp / Game.hpp     # Core game loop and simulation control
├── GameUtils.cpp / .hpp    # Helper functions for game logic
│
├── World.cpp / World.hpp           # Base world representation
├── FortniteWorld.cpp / .hpp        # Fortnite-inspired world implementation
├── WorldGraph.cpp / .hpp           # Graph structure and traversal logic
│
├── Entry.cpp / Entry.hpp   # Node/POI representation in the graph
├── Chest.cpp / Chest.hpp   # Loot chest logic and interactions
│
├── Inventory.cpp / .hpp    # Player inventory system
├── Item.cpp / Item.hpp    # Base item definitions
├── Weapon.cpp / .hpp      # Weapon-specific item logic
├── ItemDatabase.cpp / .hpp # Loads and manages item data (CSV-driven)
├── LootPool.cpp / .hpp    # Loot probability and drop system
│
├── DefaultMap.csv         # Default map configuration
├── TestMap.csv            # Test map for debugging
├── Items.csv              # Item definitions and stats
│
├── Results.txt            # Output results from simulation runs
│
├── Makfefile              # Build automation
├── .vscode/               # VSCode configuration
└── README.md              # Project documentation
  </pre>
</section>

<section id="graph">
  <h2>World Graph Design</h2>
  <p>
    The game world is modeled as an <strong>undirected weighted graph</strong>, where each node
    represents a point of interest (POI) and edges represent traversable paths between locations.
  </p>

  <p>
    Edge weights encode <strong>relative traversal cost</strong> (e.g., distance or difficulty),
    enabling dynamic route optimization without relying on hardcoded paths.
  </p>

  <p>
    This abstraction allows the engine to scale across different map configurations while
    supporting algorithmic pathfinding via <strong>Dijkstra’s algorithm</strong>, producing
    optimal traversal routes in real time.
  </p>

  <p>
    The graph is implemented using an <strong>adjacency list</strong> for efficient memory usage
    and fast neighbor lookup, making it suitable for larger, extensible worlds.
  </p>
</section>

<section id="algorithms">
  <h2>Algorithms Used</h2>
  <h3>Dijkstra’s Shortest Path Algorithm</h3>

  <p>
    The engine uses a <strong>priority queue–driven implementation of Dijkstra’s algorithm</strong>
    to compute optimal traversal routes across the world graph. Rather than returning only the
    final distance, the system reconstructs the <strong>full path sequence of POIs</strong>,
    enabling step-by-step simulation of player movement.
  </p>

  <ul>
    <li>
      Maintains a <strong>min-heap (priority queue)</strong> keyed by cumulative traversal cost
      to ensure optimal node expansion order
    </li>
    <li>
      Uses <strong>distance and predecessor maps</strong> to track shortest paths and reconstruct
      full traversal routes after computation
    </li>
    <li>
      Integrates directly with the game loop, allowing path results to drive
      <strong>loot generation and simulation flow</strong>
    </li>
    <li>
      Designed to operate on a dynamic graph loaded from CSV-based map data,
      enabling flexible world configurations
    </li>
  </ul>

  <p>
    This implementation mirrors real-world routing systems (e.g., GPS navigation), where both
    optimal cost and the exact route are required for execution.
  </p>

  <p>
    <strong>Time Complexity:</strong> O(E log V) using a binary heap
  </p>
</section>

<section id="gameplay">
  <h2>Gameplay Flow</h2>
  <p>
    The engine simulates a full traversal-and-loot cycle by combining graph-based navigation
    with probabilistic item generation. Each step in the flow is driven by underlying systems
    rather than hardcoded sequences.
  </p>

  <ol>
    <li>
      <strong>Initialize World:</strong> Load map data from CSV and construct the weighted graph
      of POIs and connections
    </li>
    <li>
      <strong>Select Drop Location:</strong> Player chooses a starting node within the graph
    </li>
    <li>
      <strong>Explore Connectivity:</strong> Adjacent nodes are dynamically retrieved from the
      graph’s adjacency list
    </li>
    <li>
      <strong>Compute Optimal Route:</strong> Dijkstra’s algorithm calculates the shortest path
      to the selected destination
    </li>
    <li>
      <strong>Simulate Traversal:</strong> The engine iterates through each node in the computed
      path, providing step-by-step movement feedback
    </li>
    <li>
      <strong>Trigger Loot Events:</strong> At each location, loot is generated via the weighted
      probability system and added to the player’s inventory
    </li>
  </ol>

  <p>
    This pipeline tightly integrates pathfinding with gameplay systems, ensuring that navigation
    decisions directly influence loot outcomes and overall simulation behavior.
  </p>

  <pre>
Fastest Route Computed:
Lonely Labs -> Mega City -> Frenzy Fields

→ Traversing: Lonely Labs → Mega City
✔ Arrival confirmed: Mega City

→ Traversing: Mega City → Frenzy Fields
✔ Arrival confirmed: Frenzy Fields
  </pre>
</section>

<section id="skills">
  <h2>Skills Demonstrated</h2>
  <ul>
    <li>Graph theory and shortest-path algorithms</li>
    <li>Modern C++ (STL, RAII, object-oriented design)</li>
    <li>File I/O and CSV parsing</li>
    <li>Weighted probability systems</li>
    <li>Defensive programming</li>
    <li>Clean, modular architecture</li>
  </ul>
</section>

<section id="usage">
  <h2>How to Run</h2>

  <h3>🟢 Quick Demo (OnlineGDB)</h3>
  <p>
    The project supports a fallback execution mode for environments that do not allow
    command-line arguments (e.g., OnlineGDB).
  </p>
  <ul>
    <li>Simply compile and run the program</li>
    <li>No arguments are required</li>
    <li>The engine will automatically use default values:</li>
  </ul>

  <pre>
Map: DefaultMap.csv
Loot: Items.csv
Runs: 1 (interactive mode)
  </pre>

  <p>
    This mode is intended for <strong>interactive gameplay demonstration</strong>.
  </p>

  <hr>

  <h3>🔵 Full Usage (Local Environment with Makefile)</h3>
  <p>
    For full functionality, including simulation and configuration via command-line arguments,
    use the provided Makefile in a local development environment.
  </p>

  <h4>Build</h4>
  <pre>
make
  </pre>

  <h4>Run Interactive Mode</h4>
  <pre>
make run
  </pre>

  <h4>Run Simulation Mode</h4>
  <pre>
make simulate
  </pre>

  <p>
    The Makefile enables:
  </p>
  <ul>
    <li>Custom map and loot configurations</li>
    <li>Multi-run simulations for statistical analysis</li>
    <li>Proper command-line argument support</li>
  </ul>

  <hr>

  <h3>Notes</h3>
  <ul>
    <li>CSV files (<code>DefaultMap.csv</code>, <code>Items.csv</code>) must be present</li>
    <li>OnlineGDB does not support command-line arguments reliably</li>
    <li>Use local execution for full feature support</li>
  </ul>
</section>

<section id="results">
  <h2>Simulation Results</h2>

  <p>
    The engine supports large-scale simulation to analyze loot distribution and system balance.
    Below is an example run with <strong>1,000,000 simulations</strong>.
  </p>

  <pre>
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
  </pre>

  <p>
    These results demonstrate the engine’s ability to produce <strong>statistically stable
    distributions</strong> across large sample sizes, validating the correctness of the
    weighted loot system and probability model.
  </p>
</section>