#ifndef WORLDGRAPH_H
#define WORLDGRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Edge
{
    string to;
    double weight;
};

class Graph
{
    unordered_map<string, vector<Edge>> adjList;

    public:
        void addVertex(const string &);
        void addEdge(const string &, const string &, const double &);
        vector<string> shortestPath(const string &, const string &);
        unordered_map<string, vector<Edge>> getAdjList() const { return adjList; }
        void print() const;
};

#endif