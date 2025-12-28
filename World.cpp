#include "World.hpp"
#include "WorldGraph.hpp"

void World::addDrop(const string &vertex)
{
    graph.addVertex(vertex);
}

void World::addConnection(const string &vertexA, const string &vertexB, const double &weight)
{
    graph.addEdge(vertexA, vertexB, weight);
}

void World::addChest(const string &location, const Chest &chest)
{
    chests[location] = chest;
}

bool World::hasChest(const string &location) const
{
    return chests.find(location) != chests.end();
}

bool World::hasLocation(const string &location) const
{
    return graph.getAdjList().find(location) != graph.getAdjList().end();
}

vector<string> World::getNeighbors(const string &location) const
{
    vector<string> list;
    auto it = graph.getAdjList().find(location);

    if (this->hasLocation(location))
        for (int i = 0; i < it->second.size(); i++)
            list.push_back(it->second[i].to);

    return list;
}

vector<string> World::getShortestPath(const string &from, const string &to)
{
    return graph.shortestPath(from, to);
}

Chest &World::getChest(const string &location)
{
    auto it = chests.find(location);

    return it->second;
}

void World::eraseChest(const string &location)
{
    chests.erase(location);
}