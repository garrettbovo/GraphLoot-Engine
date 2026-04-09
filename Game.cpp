#include "Game.hpp"
#include "GameUtils.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;

//method for printing the game's world
void Game::printWorld() const
{
    cout << R"(

    ====================== WORLD GRAPH ======================

            [Lonely Labs] -----------------
            |                             |
            5.0                          6.5
            |                             |
            |                             |
        [Anvil Square] ---- 3.5 ---- [Mega City]
            |   \                    /    |
          4.0    3.0              2.0     | 5.5
            |       \            /        |
            |        \         /          |
    [Brutal Bastion] [Slappy Shores]   [Frenzy Fields] ----
                            |                      |      |     
                            4.0                    |      |  
                            |                      |      |       
                            |                      |      |       
                        [Faulty Splits] ---- 3.0 ---      |
                            |                             |
                            2.5                          4.5
                            |                             |
                            |                             |
                    [Shattered Slabs] ---------------------

    =========================================================

    Legend:
    - Lines = direct connections
    - Numbers = edge weights
    - Graph is undirected (travel both ways)
    - Only edges listed in buildWorld() are shown

    )";
}

//method for printing the game's menu
void Game::printMenu() const
{
    cout << "\n========================================\n";
    cout << "        FORTNITE: GRAPH LOOT ENGINE\n";
    cout << "========================================\n";
    cout << "Current Location: " << currentLoc << "\n\n";

    cout << "Choose an action:\n";
    cout << "  1) Travel to another location\n";
    cout << "  2) Loot a chest at this location\n";
    cout << "  3) Show map\n";
    cout << "  4) Quit game\n\n";

    cout << "Enter your choice: ";
}

//method for running the game
bool Game::run(ItemDatabase &db, const string &algorithm)
{
    //variable declarations
    string input, destination;
    Chest chest;
    vector<string> neighbors, path;
    int intInput;
    PathResult samplePath;

    //welcoming the user to the game and printing the map
    cout << "WELCOME TO THE BATTLE BUS" << endl;
    cout << "Input \"QUIT\" to terminate the game.";
    this->printWorld();

    //loop which iterates until the user enters a valid drop location
    do
    {
        cout << "Select a drop spot: ";
        getline(cin, destination);

        inputLocation(destination);

        if (!checkQuit(destination))
            return false;

        //printing an error message if the user does not enter a valid drop location
        if (!world.hasLocation(destination))
            cout << "\nInvalid drop location, try again.\n" << endl;
    } while (!world.hasLocation(destination));

    //setting the current location to the user's drop location
    currentLoc = destination;

    //loop which iterates until the user quits the game
    do
    {
        //printing the menu and getting the user's menu selection
        this->printMenu();
        getline(cin, input);

        //checking to make sure the user enters an integer
        try
        {
            intInput = stoi(input);
        }
        catch(const std::exception& e)
        {
            cout << "Invalid entry, try again." << endl;
            continue;
        }

        //switch statement outlining the course of the four menu options
        switch (intInput)
        {
            //scenario if the user wants to travel to a POI
            case 1:
                cout << "\nWhere would you like to go? (or type 'neighbors' to see what is close by): ";
                getline(cin, destination);

                inputLocation(destination);
                    
                //scenario if the user wants to see neighboring POIs
                if (destination == "Neighbors")
                {
                    neighbors = world.getNeighbors(currentLoc);

                    //looping through the neighbors in the world and printing them to the screen
                    for (int i = 0; i < neighbors.size(); i++)
                        cout << "> " << neighbors[i] << endl;
                        
                    continue;
                }

                //if the user did not want to see the neighbors and also input a field that not a POI, they are thrown an error message
                else if (!world.hasLocation(destination))
                {
                    cout << "Invalid location, try again." << endl;
                    continue;
                }
                    
                //running A* algorithm
                if (algorithm == "astar")
                    samplePath = world.getAStarConst(currentLoc, destination);
                        
                //running dijkstra's algorithm  
                else
                    samplePath = world.getShortestPathConst(currentLoc, destination);

                if (samplePath.path.empty())
                {
                    cout << "No route exists to that destination.\n";
                    continue;
                }

                //displaying the fastest route to the destination path using a loop through the vector
                cout << "\nFastest route:" << endl;

                for (int i = 0; i < samplePath.path.size(); i++)
                {
                    if (i + 1 != samplePath.path.size())
                        cout << samplePath.path[i] << " -> ";
                    else
                        cout << samplePath.path[i];
                }
                
                //looping until the user decides to travel that route or to not take that route while remaining at the current POI
                do
                {
                    cout << "\nTravel this route? (Yes/No): ";
                    getline(cin, input);

                    inputLocation(input);
                        
                    //if the user does want to travel to the destination POI, a slowed message will show how the user travels to each location in the vector path until the destination is reached
                    if (input == "Yes")
                    {
                        //running dijkstra's algorithm
                        if (algorithm == "dijkstra")
                            path = world.getShortestPath(currentLoc, destination);
                        
                        //running A* algorithm
                        else if (algorithm == "astar")
                            path = world.getAStar(currentLoc, destination);
                        
                        //running the both algorithms and comparing their results    
                        else
                        {
                            world.getComparison(currentLoc, destination);
                            path = samplePath.path;
                        }

                        //checking if the path is empty to throw an error
                        if (path.empty())
                        {
                            cout << "No route exists to that destination.\n";
                            break;
                        }

                        cout << "\nTraveling to " << destination << "...\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(700));

                        for (int i = 1; i < path.size(); i++)
                        {
                            cout << "\nTraveling from " << path[i - 1]
                                << " to " << path[i] << "...\n";

                            std::this_thread::sleep_for(std::chrono::milliseconds(800));

                            currentLoc = path[i];
                            cout << "Arrived at " << currentLoc << "!\n";
                        }

                        cout << "\nYou have reached your destination.\n";
                    }

                    //checking if the user typed "quit"; if so, the game is terminated
                    else if (!checkQuit(input))
                        return false;
                } while (input != "Yes" && input != "No");
                break;

                //scenario if the user wants to loot a chest at the current POI
                case 2:
                    //checking if the chest at the current POI has not been looted yet
                    if (world.hasChest(currentLoc))
                    {
                        //opening the chest at the current POI
                        chest = db.openChest();

                        //displaying the chests contents in a slowed manner
                        std::this_thread::sleep_for(std::chrono::milliseconds(700));
                        chest.displayChest();
                        std::this_thread::sleep_for(std::chrono::milliseconds(700));
                        
                        //erasing the chest from the POI
                        world.eraseChest(currentLoc);
                    }

                    //message showing there are no more chests at the POI if the chest has already been looted
                    else
                        cout << "There are no more chests at this location. You must travel to a different location if you would like to loot." << endl;
                    break;
                
                //scenario printing the world's map to the screen
                case 3:
                    this->printWorld();
                    break;
                
                //scenario to quit the game per the user's request
                case 4: 
                    return false;
        }
    } while (1);

    return true;
}

//method for simulation
void Game::simulate(ItemDatabase &db)
{
    //variable declaration
    Chest chest;
    unordered_map<string, int> visited;

    //assigning the simulation's location on the map to any named location
    currentLoc = world.randomPOI();

    //moving along the map STEPS number of times
    for (int i = 0; i < STEPS; i++)
    {
        //checking if the current named location has a chest that has not been looted
        if (world.hasChest(currentLoc))
        {
            //opening the chest
            chest = db.openChest();

            //adding the weapon's content to the two maps to be used in Results.txt
            rarityCounts[rarityToString(chest.getWeapon()->getRarityID())]++;
            typeCounts[chest.getWeapon()->getAmmo()]++;

            //marking down which POI has just been visited to ensure a chest is added back to the location
            visited[currentLoc] = 1;

            //removing the chest from the map
            world.eraseChest(currentLoc);
        }
        
        //moving the simulation to a random POI that is a neighbor to the current POI
        currentLoc = world.randomNeighbor(currentLoc);
    }

    //iterating through the map of visited POIs to add the chests back that were looted
    for (auto it = visited.begin(); it != visited.end(); it++)
        world.addChest(it->first, db.openChest());
}

//method for writing simulation results to output file
void Game::writeSimulation(const int &runs) const
{
    //variable declarations and initializations
    ofstream file("Results.txt");
    int totalRolls = 0, count;
    vector<string> rarityOrder = {"Common", "Uncommon", "Rare", "Epic", "Legendary"};
    vector<bullet> gunOrder = {Medium, Shells, Light, Heavy};

    //checking if the file opened correctly
    if (!file.is_open())
    {
        cerr << "Failed to open file." << endl;
        exit(0);
    }

    //counting the total number of times the simulation opened chests
    for (const auto &pair : rarityCounts)
        totalRolls += pair.second;
    
    //printing menu
    file << "\n========================================\n";
    file << "      GRAPH LOOT ENGINE RESULTS\n";
    file << "========================================\n\n";

    //printing simulation statistics
    file << "Simulation Runs: " << runs << endl;
    file << "Steps per Run: " << STEPS << endl;
    file << "Total Loot Rolls: " << totalRolls << endl;

    if (totalRolls == 0)
    {
        file << "\nNo loot rolls were recorded.\n";
        file << "\n========================================\n";
        file.close();
        return;
    }

    //printing menu
    file << "\n----------------------------------------\n";
    file << "Rarity Distribution\n";
    file << "----------------------------------------\n";

    //setting decimal precision to two decimal places
    file << fixed << setprecision(2);

    //iterating through all the instances of rarity types
    for (int i = 0; i < rarityOrder.size(); i++)
    {
        //checking if the current key in the map is a rarity type found in the vector
        auto it = rarityCounts.find(rarityOrder[i]);

        //checking if the iterator is pointing to a valid key; if so, get the value from the map
        if (it != rarityCounts.end())
            count = rarityCounts.at(rarityOrder[i]);
        //otherwise, report zero instead of reusing the previous loop's count
        else
            count = 0;

        //printing weapon rarity statistics to the file
        file << left << setw(12) << rarityOrder[i] << ": " << setw(6) << double (count) / totalRolls * 100 << "% (" << count << ")" << endl;
    }

    //printing menu
    file << "\n----------------------------------------\n";
    file << "Weapon Type Distribution\n";
    file << "----------------------------------------\n";

    //iterating through the different weapon types to print weapon statistics to the file
    for (int i = 0; i < gunOrder.size(); i++)
    {
        //iterator to move through the weapon types map
        auto it = typeCounts.find(gunOrder[i]);

        //checking to see if the simulation encountered the current weapon type; if so, tally the total number the weapon type was looted
        if (it != typeCounts.end())
            count = typeCounts.at(gunOrder[i]);
        //otherwise, report zero instead of reusing the previous loop's count
        else
            count = 0;

        //printing the weapon name based on the predefined order for weapon display noted in gunOrder vector
        switch (gunOrder[i])
        {
            case Medium: 
                file << left << setw(12) << "AR";
                break;
            case Shells: 
                file << left << setw(12) << "Shotgun";
                break;
            case Light: 
                file << left << setw(12) << "SMG";
                break;
            case Heavy: 
                file << left << setw(12) << "Heavy";
                break;
            default: 
                break;
        }
        
        //writing the weapon type statistics to the file
        file << ": " << setw(6) << double (count) / totalRolls * 100 << "% (" << count << ")" << endl;
    }

    //printing menu
    file << "\n========================================\n";

    //closing the file
    file.close();
}
