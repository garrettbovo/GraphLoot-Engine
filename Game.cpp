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
    string input, destination;
    Chest chest;
    vector<string> neighbors, path;

    cout << "WELCOME TO THE BATTLE BUS" << endl;
    cout << "Input \"QUIT\" to terminate the game." << endl;

    this->printWorld();

    do
    {
        cout << "Input a drop spot: ";
        getline(cin, destination);

        inputLocation(destination);

        if (!checkQuit(destination))
            return false;
    } while (!world.hasLocation(destination));

    currentLoc = destination;

    do
    {
        this->printWorld();

        if (world.hasChest(currentLoc))
        {
            do
            {
                cout << "Would you like to loot a chest? (Yes/No): ";
                getline(cin, input);
                
                inputLocation(input);
            } while (input != "Yes" && input != "No");

            if (input == "Yes")
            {
                chest = db.openChest();
                world.eraseChest(currentLoc);
            }

            else if (!checkQuit(destination))
                    return false;
        }

        do
        {
            cout << "You are at " << currentLoc << "Where would you like to go? (or type 'neighbors')";
            getline(cin, destination);

            inputLocation(destination);
            
            if (destination == "Neighbors")
            {
                neighbors = world.getNeighbors(currentLoc);

                for (int i = 0; i < neighbors.size(); i++)
                    cout << "> " << neighbors[i] << endl;
                
                continue;
            }

            else
                cout << "Invalid location, try again." << endl;
        } while (!world.hasLocation(destination));


        path = world.getShortestPath(currentLoc, destination);

        if (path.empty())
            cout << "No route exists" << endl;
        
        cout << "Fastest route:" << endl;

        for (int i = 0; i < path.size(); i++)
            cout << path[i] << " -> ";
        
        do
        {
            cout << "\nTravel this route? (Yes/No): ";
            getline(cin, input);

            inputLocation(input);
            
            if (input == "Yes")
                currentLoc = destination;

            else if (!checkQuit(input))
                return false;
        } while (input != "Yes" && input != "No");
    } while (1);

    return true;
}