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

struct Node
{
    string name;
    double x, y;
};

class Graph
{
    //private member attributes for adjacency list and a*
    unordered_map<string, vector<Edge>> adjList;
    unordered_map<string, Node> nodes;

    public:
        //adding vertex to graph
        void addVertex(const string &);
        //adding edge to graph
        void addEdge(const string &, const string &, const double &);
        //adding two-dimensional location to given vertex
        void addNode(const string &, const double &, const double &);
        //method returning a vector of the shortest path from vertex A to vertex B
        vector<string> shortestPath(const string &, const string &);
        //method returning a vector of the a* path from vertex A to vertex B
        vector<string> aStar(const string &, const string &);
        //method for comparing path from vertex A to vertex B using shortest path and A*
        vector<string> comparePaths(const string &, const string &);
        //getter returning the graph's adjacency list
        const unordered_map<string, vector<Edge>> &getAdjList() const { return adjList; }
        //getter returning the graph's a* list
        const unordered_map<string, Node> &getNodes() const { return nodes; }
        //prints the graph's vertices and edge connections
        void print() const;
        //method for finding the distance between two nodes using x and y
        double heuristic(const string &, const string &);
};

#endif