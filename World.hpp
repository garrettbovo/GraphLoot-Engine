#ifndef WORLD_H
#define WORLD_H

#include "WorldGraph.hpp"
#include "Chest.hpp"

#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class World
{
    //private member attributes
    Graph graph;
    unordered_map<string, Chest> chests;

    public:
        //default constructor
        World() {}
        //adding vertex to graph
        void addDrop(const string &);
        //adding edge to graph
        void addConnection(const string &, const string &, const double &);
        //adding two-dimensional position to graph
        void addDistance(const string &, const double &, const double &);
        //adding chest to POI
        void addChest(const string &, const Chest &);
        //checking if given POI has an unlooted chest
        bool hasChest(const string &) const;
        //checking if the given string is a POI vertex in the graph
        bool hasLocation(const string &) const;
        //method returning a vector of all the neighbors a given POI has
        vector<string> getNeighbors(const string &) const;
        //method returning the shortest path from vertex A to vertex B
        vector<string> getShortestPath(const string &, const string &);
        //method returning the shortest path from vertex A to B const without modifying the player's location
        PathResult getShortestPathConst(const string &, const string &) const;
        //method returning the a* path from vertex A to vertex B
        vector<string> getAStar(const string &, const string &);
        //method returning the a* path from vertex A to B const without modifying the player's location
        PathResult getAStarConst(const string &, const string &) const;
        //method for returning the shortest path/a* path comparison from vertex A to vertex B
        vector<string> getComparison(const string &, const string &);
        //getter returning the chest at the given POI
        Chest &getChest(const string &);
        //erasing the method at the given POI
        void eraseChest(const string &);
        //returns a vector of all named locations on the map
        vector<string> getAllDrops() const;
        //method for getting random neighbor POI selection
        string randomNeighbor(const string &) const;
        //method for getting random POI selection
        string randomPOI() const;
        //default destructor
        ~World() {}
};

#endif