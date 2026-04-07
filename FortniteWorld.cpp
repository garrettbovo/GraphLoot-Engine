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
    string vertexA, vertexB, strWeight, line, mapFile, strX, strY;
    double weight, x, y;
    vector<string> allDrops;

    //getting the name of the map from command line input
    mapFile = getArgValue(argc, argv, "--map");

    //checking if the user input a map file; if the user did not, an error is thrown and the program terminates
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
        //trimming whitespace
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

    //creating a vector containing all the POIs in the world
    allDrops = world.getAllDrops();

    //looping through each POI and adding a single chest to each location
    for (int i = 0; i < allDrops.size(); i++)
        world.addChest(allDrops[i], db.openChest());
    
    //closing the file
    file.close();

    //getting the name of the map from command line input
    mapFile = getArgValue(argc, argv, "--nodes");

    //checking if the user input a map file; if the user did not, default to using Nodes.csv
    if (mapFile.empty())
        mapFile = "Nodes.csv";
    
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
        //trimming whitespace
        if (line.find_first_not_of(" \t\r\n") == string::npos)
            continue;
        
        stringstream ss(line);
        
        //reading in the connection as to vertices and its x and y coordinates
        getline(ss, vertexA, ',');
        getline(ss, strX, ',');
        getline(ss, strY, ',');
        x = stod(strX);
        y = stod(strY);

        //adding POI positioning into the world
        world.addDistance(vertexA, x, y);
    }

    return world;
}