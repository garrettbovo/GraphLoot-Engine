cmake_minimum_required(VERSION 3.16)

project(GraphLootEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable and all source files
add_executable(engine
    main.cpp
    Game.cpp
    GameUtils.cpp
    World.cpp
    FortniteWorld.cpp
    WorldGraph.cpp
    Entry.cpp
    Chest.cpp
    Item.cpp
    Weapon.cpp
    ItemDatabase.cpp
    LootPool.cpp
)

add_executable(test_dijkstra
    tests/test_dijkstra.cpp
    WorldGraph.cpp
)

target_include_directories(test_dijkstra PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(test_astar
    tests/test_astar.cpp
    WorldGraph.cpp
)

target_include_directories(test_astar PRIVATE ${CMAKE_SOURCE_DIR})
