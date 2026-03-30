#include "FortniteWorld.hpp"
#include "ItemDatabase.hpp"
#include "GameUtils.hpp"

#include <fstream>
#include <sstream>
#include <string>

//function for building the Fortnite map
World buildWorld(const int &argc, char *argv[], ItemDatabase &db)
{
    //variable declarations
    World world;
    ifstream file;
    string vertexA, vertexB, strWeight, line, mapFile;
    double weight;
    vector<string> allDrops;

    mapFile = getArgValue(argc, argv, "--map");

    if (mapFile.empty())
    {
        cerr << "No map file provided." << endl;
        exit(1);
    }

    //opening the file
    file.open(mapFile);

    //checking if the file opened successfully; otherwise, the program will terminate
    if (!file.is_open())
    {
        cerr << "Unable to open file." << endl;
        exit(1);
    }

    //reading each line of the file
    while (getline(file, line))
    {
        if (line.find_first_not_of(" \t\r\n") == string::npos)
            continue;
        
        stringstream ss(line);
        
        //reading in the connection as to vertices and a weight
        getline(ss, vertexA, ',');
        getline(ss, vertexB, ',');
        getline(ss, strWeight, ',');
        weight = stod(strWeight);

        //adding POIs to the map
        world.addDrop(vertexA);
        world.addDrop(vertexB);

        //adding weighted, undirected connections between edges starting at Lonely Labs
        world.addConnection(vertexA, vertexB, weight);
    }

    allDrops = world.getAllDrops();

    for (int i = 0; i < allDrops.size(); i++)
        world.addChest(allDrops[i], db.openChest());
    
    file.close();

    return world;
}