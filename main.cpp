#include "ItemDatabase.hpp"
#include "World.hpp"
#include "FortniteWorld.hpp"
#include "Game.hpp"

#include <iostream>
using namespace std;

int main()
{
    ItemDatabase data;
    World world;
    Game game;

    data.readCSV();
    data.setLootPool();
    world = buildWorld(data);
    game.setWorld(world);
    while (game.run(data));

    return 0;
}