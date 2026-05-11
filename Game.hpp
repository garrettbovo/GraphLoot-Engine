#ifndef GAME_H
#define GAME_H

#include "World.hpp"
#include "ItemDatabase.hpp"

#include <string>
#include <unordered_map>

//number of times the simulator should traverse the map in each run of the simulation
#define STEPS 5

//struct for storing the results of a simulation run
struct SimulationResult
{
    //public member attributes
    unordered_map<string, int> rarityCounts;
    unordered_map<bullet, int> typeCounts;
};

class Game
{
    //private member attributes
    World world;
    string currentLoc;
    unordered_map<string, int> rarityCounts;
    unordered_map<bullet, int> typeCounts;

    public:
        //default constructor
        Game() {}
        //setter assigning the game's map
        void setWorld(World wID) { world = wID; }
        //getter returning the game's map
        World getWorld() const { return world; }
        //setter assigning the player's current location
        void setCurrentLoc(string lID) { currentLoc = lID; }
        //getter returning the player's current location
        string getCurrentLoc() const { return currentLoc; }
        //setter assigning the number of weapon's based on rarity
        void setRarityCounts(unordered_map<string, int> map) { rarityCounts = map; }
        //getter returning the number of weapon's based on rarity
        unordered_map<string, int> getRarityCounts() const { return rarityCounts; }
        //setter assigning the number of weapon's based on rarity
        void setTypeCounts(unordered_map<bullet, int> map) { typeCounts = map; }
        //getter returning the number of weapon's based on rarity
        unordered_map<bullet, int> getTypeCounts() const { return typeCounts; }
        //method for running the game
        bool run(ItemDatabase &, const string &);
        //method for simulation that simulates one run of the game and returns the results of the simulation as maps stored in a SimulationResult struct
        SimulationResult simulateOnce(ItemDatabase &);
        //method for aggregating the results of simulations into the maps attributes of the Game class
        void aggregate(const SimulationResult &);
        //printing the game's world
        void printWorld() const;
        //printing the game's menu
        void printMenu() const;
        //method for writing simulation results to output file
        void writeSimulation(const int &) const;
        //default destructor
        ~Game() {}
};

#endif