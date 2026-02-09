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
    //private member attribute
    unordered_map<string, vector<Edge>> adjList;

    public:
        //adding vertex to graph
        void addVertex(const string &);
        //adding edge to graph
        void addEdge(const string &, const string &, const double &);
        //method returning a vector of the shortest path from vertex A to vertex B
        vector<string> shortestPath(const string &, const string &);
        //getter returning the graph's adjacency list
        const unordered_map<string, vector<Edge>> &getAdjList() const { return adjList; }
        //prints the graph's vertices and edge connections
        void print() const;
};

#endif