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
bool Game::run(ItemDatabase &db)
{
    //variable declarations
    string input, destination;
    Chest chest;
    vector<string> neighbors, path;
    int intInput;

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
                
                //the vector path from the current location to the destination the user wants to go to is instantiated with the shortest path to the destination POI
                path = world.getShortestPath(currentLoc, destination);

                //checking if the path is empty to throw an error
                if (path.empty())
                {
                    cout << "No route exists to that destination.\n";
                    break;
                }
                    
                //displaying the fastest route to the destination path using a loop through the vector
                cout << "\nFastest route:" << endl;

                for (int i = 0; i < path.size(); i++)
                {
                    if (i + 1 != path.size())
                        cout << path[i] << " -> ";
                    else
                        cout << path[i];
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

void Game::simulate(ItemDatabase &db)
{
    Chest chest;

    currentLoc = world.randomPOI();

    for (int i = 0; i < STEPS; i++)
    {
        if (world.hasChest(currentLoc))
        {
            chest = db.openChest();

            rarityCounts[rarityToString(chest.getWeapon()->getRarityID())]++;
            typeCounts[chest.getWeapon()->getAmmo()]++;
        }
          
        currentLoc = world.randomNeighbor(currentLoc);
    }
}

void Game::writeSimulation(const int &runs) const
{
    ofstream file("Results.txt");
    int totalRolls = 0, count;
    vector<string> rarityOrder = {"Common", "Uncommon", "Rare", "Epic", "Legendary"};
    vector<bullet> gunOrder = {Medium, Shells, Light, Heavy};

    if (!file.is_open())
    {
        cerr << "Failed to open file." << endl;
        exit(0);
    }

    for (const auto &pair : rarityCounts)
        totalRolls += pair.second;

    file << "\n========================================\n";
    file << "      GRAPH LOOT ENGINE RESULTS\n";
    file << "========================================\n\n";

    file << "Simulation Runs: " << runs << endl;
    file << "Steps per Run: " << STEPS << endl;
    file << "Total Loot Rolls: " << totalRolls << endl;

    file << "\n----------------------------------------\n";
    file << "Rarity Distribution\n";
    file << "----------------------------------------\n";

    file << fixed << setprecision(2);

    for (int i = 0; i < rarityOrder.size(); i++)
    {
        auto it = rarityCounts.find(rarityOrder[i]);

        if (it != rarityCounts.end())
            count = rarityCounts.at(rarityOrder[i]);

        file << left << setw(12) << rarityOrder[i] << ": " << setw(6) << double (count) / totalRolls * 100 << "% (" << count << ")" << endl;
    }

    file << "\n----------------------------------------\n";
    file << "Weapon Type Distribution\n";
    file << "----------------------------------------\n";

    for (int i = 0; i < gunOrder.size(); i++)
    {
        auto it = typeCounts.find(gunOrder[i]);

        if (it != typeCounts.end())
            count = typeCounts.at(gunOrder[i]);

        
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
        
            file << ": " << setw(6) << double (count) / totalRolls * 100 << "% (" << count << ")" << endl;
    }

    file << "\n========================================\n";

    file.close();
}