#include "World.hpp"
#include "WorldGraph.hpp"

//method for adding POI to the map
void World::addDrop(const string &vertex)
{
    graph.addVertex(vertex);
}

//method for adding an edge between two vertices
void World::addConnection(const string &vertexA, const string &vertexB, const double &weight)
{
    graph.addEdge(vertexA, vertexB, weight);
}

//adding two-dimensional position to graph
void World::addDistance(const string &vertex, const double &x, const double &y)
{
    graph.addNode(vertex, x, y);
}

//method for adding a chest to the given POI
void World::addChest(const string &location, const Chest &chest)
{
    chests[location] = chest;
}

//method for verifying if the given POI has an unlooted chest
bool World::hasChest(const string &location) const
{
    return chests.find(location) != chests.end();
}

//method for verifying if the given string is a POI on the map
bool World::hasLocation(const string &location) const
{
    return graph.getAdjList().find(location) != graph.getAdjList().end();
}

//method for returning a vector of POI locations that are neighbors to a given POI
vector<string> World::getNeighbors(const string &location) const
{
    vector<string> list;
    auto it = graph.getAdjList().find(location);

    if (it == graph.getAdjList().end())
        return list;

    if (this->hasLocation(location))
        for (int i = 0; i < it->second.size(); i++)
            list.push_back(it->second[i].to);

    return list;
}

//method for finding the shortest path from one vertex to another
vector<string> World::getShortestPath(const string &from, const string &to)
{
    return graph.shortestPath(from, to);
}

//method returning the a* path from vertex A to vertex B
vector<string> World::getAStar(const string &vertexA, const string &vertexB)
{
    return graph.aStar(vertexA, vertexB);
}

//getter returning the chest at the given POI
Chest &World::getChest(const string &location)
{
    auto it = chests.find(location);

    return it->second;
}

//method for erasing the chest at the specified location
void World::eraseChest(const string &location)
{
    chests.erase(location);
}

//method for returning a vector of all named locations on the Fortnite map
vector<string> World::getAllDrops() const
{
    //variable declaration
    vector<string> drops;
    
    //for loop which iterates over each first item in the adjacency list and adds it to drops which is a vector storing the unique named locations
    for (auto it = graph.getAdjList().begin(); it != graph.getAdjList().end(); ++it)
        drops.push_back(it->first);
    
    return drops;
}

//method for generating a random neighboring POI in reference to the current POI given as an argument
string World::randomNeighbor(const string &current) const
{
    //declaring and initializing a vector of all neighbors to the current POI
    vector<string> allPOIs = this->getNeighbors(current);

    //randomly returning the name of the POI generated using random number generation
    return allPOIs[rand() % allPOIs.size()];
}

//method for generating a random drop POI at the beginning of the match
string World::randomPOI() const
{
    //declaring and initializing a vector of all the named POIs
    vector<string> allPOIs = this->getAllDrops();

    //randomly returning the name of the POI generated using random number generation
    return allPOIs[rand() % allPOIs.size()];
}