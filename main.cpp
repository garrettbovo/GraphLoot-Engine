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

/*HOW TO COMPILE & RUN THE PROGRAM
------------------------------
g++ -std=c++17 *.cpp -o engine
./engine --map DefaultMap.csv --loot Items.csv --runs 1000 --nodes Nodes.csv --algorithm dijkstra

//ALGORITHM OPTIONS (INPUT EXACTLY ONE AS FOLLOWS):
    - dijkstra
    - astar
------------------------------
*/

/*HOW TO BUILD USING CMAKE
------------------------------
rm -rf build
mkdir build
cd build
cmake ..
make

RUN INTERACTIVE MODE
./engine --map ../DefaultMap.csv --loot ../Items.csv --runs 1

RUN SIMULATION MODE
./engine --map ../DefaultMap.csv --loot ../Items.csv --runs 1000

TEST DIJKSTRA
./test_dijkstra
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
    string strRuns, strAlgorithm;

    //onlineGDB safe version of the interactive Fortnite mode
    if (argc == 1) {
        //no CLI args provided → fallback (OnlineGDB)
        static char arg0[] = "engine";
        static char arg1[] = "--map";
        static char arg2[] = "DefaultMap.csv";
        static char arg3[] = "--loot";
        static char arg4[] = "Items.csv";
        static char arg5[] = "--runs";
        static char arg6[] = "1";
        
        static char* fakeArgv[] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6 };

        argc = 7;
        argv = fakeArgv;
    }

    //version of the game outside of OnlineGDB
    else
    {
        //reading in CLI for how many times the game should run
        strRuns = getArgValue(argc, argv, "--runs");
        
        //converting the valid string input into and integer variable
        if (strRuns != "")
            runs = stoi(strRuns);
    }

    //determining which algorithm to use for player movement
    strAlgorithm = getArgValue(argc, argv, "--algorithm");
        
    //checking if the algorithm CLI was empty; if so, default to dijkstra
    if (strAlgorithm == "" || strAlgorithm == "dijkstra")
        strAlgorithm = "dijkstra";
    
    //checking if the algorithm CLI was prompting a*
    else if (strAlgorithm == "astar")
        strAlgorithm = "astar";

    //otherwise, an invalid algorithm was input so the program will throw an error and terminate
    else
    {
        cerr << "Invalid algorithm selection" << endl;
        exit(1);
    }

    //reading loot information from CSV file
    data.readCSV(argc, argv);
    //initializing the loot pool from the vector of items
    data.setLootPool();
    //assign the created world to the current game
    game.setWorld(buildWorld(argc, argv, data));

    //running the interactive version of the game if the user said to run the game one time
    if (runs == 1)
        game.run(data, strAlgorithm);
    
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