<body>

<header>
  <h1>Fortnite Graph Loot Engine 🎮</h1>
  <p>
    The <strong>Fortnite Graph Loot Engine</strong> is a C++ console-based simulation that models
    player movement and loot acquisition using <strong>graph theory, weighted shortest-path algorithms,
    and modular object-oriented design</strong>.
  </p>
  <p>
    This project demonstrates real-world application of <strong>Dijkstra’s algorithm</strong>,
    structured game logic, CSV-driven data systems, and modern C++ programming practices.
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
  </ul>
</details>

<section id="overview">
  <h2>Overview 📋</h2>
  <p>
    The Fortnite Graph Loot Engine represents Fortnite locations as vertices in a
    <strong>weighted, undirected graph</strong>. Each connection between locations has a travel
    cost, and the fastest route is computed dynamically based on player input.
  </p>
  <p>
    Players can explore the map, inspect neighboring locations, travel across optimal routes,
    and loot chests containing procedurally selected items.
  </p>
</section>

<section id="features">
  <h2>Key Features ⭐</h2>
  <ul>
    <li><strong>Weighted World Graph:</strong> Locations are nodes; travel routes are weighted edges.</li>
    <li><strong>Dijkstra’s Algorithm:</strong> Computes shortest paths with full route reconstruction.</li>
    <li><strong>Dynamic Loot System:</strong> Items generated using rarity and category weighting.</li>
    <li><strong>CSV-Based Data:</strong> Weapons and items loaded from external CSV files.</li>
    <li><strong>Animated Travel:</strong> Step-by-step traversal with timed delays.</li>
    <li><strong>Robust Input Handling:</strong> Defensive parsing and normalization of user input.</li>
  </ul>
</section>

<section id="structure">
  <h2>Project Structure 🗂️</h2>
  <pre>
GraphLoot-Engine/
│
├── Game.cpp / Game.hpp          # Game loop, menu, and player interaction
├── World.cpp / World.hpp        # World state and chest management
├── WorldGraph.cpp / .hpp        # Graph implementation + Dijkstra algorithm
├── ItemDatabase.cpp / .hpp      # CSV parsing and item creation
├── LootPool.cpp / .hpp          # Weighted random loot selection
├── Chest.cpp / .hpp             # Chest contents and display logic
├── GameUtils.cpp / .hpp         # Input formatting helpers
├── FortniteWorld.cpp            # Graph construction and connections
├── Items.csv                    # Item data source
└── README.html
  </pre>
</section>

<section id="graph">
  <h2>World Graph Design 🌍</h2>
  <p>
    The world is modeled as an <strong>undirected weighted graph</strong>, meaning travel is
    possible in both directions along each connection.
  </p>
  <p>
    Edge weights represent relative travel cost, allowing realistic path optimization and
    preventing hardcoded routes.
  </p>
</section>

<section id="algorithms">
  <h2>Algorithms Used ⚙️</h2>
  <h3>Dijkstra’s Shortest Path Algorithm</h3>
  <ul>
    <li>Priority queue (min-heap) based implementation</li>
    <li>Tracks distance and predecessor maps</li>
    <li>Time complexity: <strong>O(E log V)</strong></li>
  </ul>
  <p>
    This algorithm is widely used in navigation systems, routing software, and AI pathfinding.
  </p>
</section>

<section id="gameplay">
  <h2>Gameplay Flow 🎯</h2>
  <ol>
    <li>Select an initial drop location</li>
    <li>View neighboring locations</li>
    <li>Choose a destination</li>
    <li>Shortest path is calculated and displayed</li>
    <li>Travel node-by-node with animated feedback</li>
    <li>Loot chests and receive randomized items</li>
  </ol>

  <pre>
Fastest route:
Lonely Labs -> Mega City -> Frenzy Fields

→ Traveling from Lonely Labs to Mega City...
✔ Arrived at Mega City!

→ Traveling from Mega City to Frenzy Fields...
✔ Arrived at Frenzy Fields!
  </pre>
</section>

<section id="skills">
  <h2>Skills Demonstrated 🧠</h2>
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
  <h2>How to Run 🛠️</h2>
  <p><strong>Compile:</strong></p>
  <pre>
g++ -std=c++17 *.cpp -o lootpath
  </pre>

  <p><strong>Run:</strong></p>
  <pre>
./lootpath
  </pre>

  <p>
    Ensure <code>Items.csv</code> is present in the project directory before running.
  </p>
</section>

<footer>
  <p>
    <strong>Fortnite Graph Loot Engine</strong> is a portfolio-grade project showcasing
    algorithmic reasoning, data structures, and real-world C++ system design.
  </p>
</footer>

</body>
</html>
