#include "Game.hpp"
#include "GameUtils.hpp"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void Game::printWorld() const
{
    cout << R"(

                               ^^^^^^^^^^^^^^^^^
                               |  BRUTAL BASTION |
                               ^^^^^^^^^^^^^^^^^
                                        |
                                      (4.0)
                                        |
        ^^^^^^^^^^^^^^^^^        =====================        ^^^^^^^^^^^^^^^^^
        |  LONELY LABS   |=======(5.0)  ANVIL SQUARE  (3.0)=======| SLAPPY SHORES |
        ^^^^^^^^^^^^^^^^^        =====================        ^^^^^^^^^^^^^^^^^
                                        |
                                      (3.5)
                                        |
                               ###################
                               |    MEGA CITY    |
                               ###################
                                  |           |
                                (2.0)       (5.5)
                                  |           |
        ~~~~~~~~~~~~~~~~      ###################      ...............
        | SLAPPY SHORES |=====(4.0) FAULTY SPLITS (3.0)====| FRENZY FIELDS |
        ~~~~~~~~~~~~~~~~      ###################      ...............
                                            |
                                          (2.5)
                                            |
                               vvvvvvvvvvvvvvvvvvvvv
                               |  SHATTERED SLABS   |
                               vvvvvvvvvvvvvvvvvvvvv

)";



}

bool Game::run(ItemDatabase &db)
{
    string input;
    Chest chest;
    vector<string> neighbors, path;

    cout << "WELCOME TO THE BATTLE BUS" << endl;
    cout << "Input \"QUIT\" to terminate the game." << endl;

    this->printWorld();

    do
    {
        cout << "Input a drop spot: ";
        getline(cin, input);

        inputLocation(input);

        if (!checkQuit(input))
            return false;
    } while (!world.hasLocation(input));

    currentLoc = input;

    do
    {
        this->printWorld();

        if (world.hasChest(currentLoc))
        {
            do
            {
                cout << "Would you like to loot a chest? (Yes/No): ";
                getline(cin, input);

                input.erase(0, input.find_first_not_of(" \t\n\r"));
                input.erase(input.find_last_not_of(" \t\n\r") + 1);

                for (int i = 0; i < input.size(); i++)
                    input[i] = tolower(input[i]);
            } while (input != "yes" && input != "no");

            if (input == "yes")
            {
                chest = db.openChest();
                world.eraseChest(currentLoc);
            }

            else if (!checkQuit(input))
                    return false;
        }

        cout << "You are at " << currentLoc << "Where would you like to go? (or type 'neighbors')";
        getline(cin, input);

        input.erase(0, input.find_first_not_of(" \t\n\r"));
        input.erase(input.find_last_not_of(" \t\n\r") + 1);

        for (int i = 0; i < input.size(); i++)
            input[i] = tolower(input[i]);
        
        if (input == "neighbors")
        {
            neighbors = world.getNeighbors(currentLoc);

            for (int i = 0; i < neighbors.size(); i++)
                cout << "> " << neighbors[i] << endl;
        }

        else
        {
            cout << "Invalid location, try again." << endl;
            continue;
        }

        inputLocation(input);
        
        if (!checkQuit(input))
            return false;

        path = world.getShortestPath(currentLoc, input);

        if (path.empty())
            cout << "No route exists" << endl;
        
        cout << "Fastest route:" << endl;

        for (int i = 0; i < path.size(); i++)
            cout << path[i] << " -> ";
        
        cout << "\nTravel this route? (Yes/No): ";
        getline(cin, input);

        input.erase(0, input.find_first_not_of(" \t\n\r"));
        input.erase(input.find_last_not_of(" \t\n\r") + 1);

        for (int i = 0; i < input.size(); i++)
            input[i] = tolower(input[i]);
        
        if (input == "yes")
        {
            chest = db.openChest();
            world.eraseChest(currentLoc);
        }

        else if (!checkQuit(input))
            return false;
    } while (1);
    
}