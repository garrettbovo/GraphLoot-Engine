#include "ItemDatabase.hpp"
#include "World.hpp"
#include "FortniteWorld.hpp"
#include "Game.hpp"

#include <iostream>
using namespace std;

int main()
{
    //variable declarations for database, world, and game
    ItemDatabase data;
    World world;
    Game game;

    //reading loot information from CSV file
    data.readCSV();
    //initializing the loot pool from the vector of items
    data.setLootPool();
    //building the Fortnite map
    world = buildWorld(data);
    //assign the created world to the current game
    game.setWorld(world);
    //running the game
    game.run(data);

    return 0;
}