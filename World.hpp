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
    Graph graph;
    unordered_map<string, Chest> chests;

    public:
        World() {}
        void addDrop(const string &);
        void addConnection(const string &, const string &, const double &);
        void addChest(const string &, const Chest &);
        bool hasChest(const string &) const;
        bool hasLocation(const string &) const;
        vector<string> getNeighbors(const string &) const;
        vector<string> getShortestPath(const string &, const string &);
        Chest &getChest(const string &);
        void eraseChest(const string &);
        ~World() {}
};

#endif