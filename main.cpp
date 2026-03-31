#include "ItemDatabase.hpp"
#include "World.hpp"
#include "FortniteWorld.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

/*HOW TO RUN THE PROGRAM
------------------------------
g++ -std=c++17 *.cpp -o engine
./engine --map DefaultMap.csv --loot Items.csv --runs 1000
------------------------------
*/

int main(int argc, char *argv[])
{
    //seed for random number generation
    srand(time(0));

    //variable declarations and initializations for database, world, game, and runs/strRuns which stores how many times the program should run
    ItemDatabase data;
    World world;
    Game game;
    int runs = 1;
    string strRuns = getArgValue(argc, argv, "--runs");
    
    if (strRuns != "")
        runs = stoi(strRuns);

    //reading loot information from CSV file
    data.readCSV(argc, argv);
    //initializing the loot pool from the vector of items
    data.setLootPool();
    //assign the created world to the current game
    game.setWorld(buildWorld(argc, argv, data));

    //running the interactive version of the game if the user said to run the game one time
    if (runs == 1)
        game.run(data);
    
    //running the simulated version of the game if the user said to run the game more than once
    else if (runs > 1)
    {
        //running the simulation runs number of times
        for (int i = 0; i < runs; i++)
            game.simulate(data);

        //writing the simulation results to an output file
        game.writeSimulation(runs);
    }

    return 0;
}