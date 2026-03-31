#include "WorldGraph.hpp"

#include <iostream>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
using namespace std;

//method for adding a vertex to the graph
void Graph::addVertex(const string &node)
{
    //checking if the node does not already exist
    for (auto it = adjList.begin(); it != adjList.end(); ++it)
        if (it->first == node)
            return;
    
    //creating the new node since it does not exist
    adjList[node] = {};
}

//method for connecting to vertices
void Graph::addEdge(const string &from, const string &to, const double &weight)
{
    //checking to make sure the from vertex exists
    if (adjList.find(from) == adjList.end())
        addVertex(from);
    
    //checking to make sure the to vertex exists
    if (adjList.find(to) == adjList.end())
        addVertex(to);

    //adding edges between the two vertices in both directions
    adjList[from].push_back({to, weight});
    adjList[to].push_back({from, weight});
}

vector<string> Graph::shortestPath(const string &from, const string &to)
{
    //dist stores the shortest known path from distance to each from node
    unordered_map<string, double> dist;
    //prev stores the previous node on the shortest path
    unordered_map<string, string> prev;
    string neighbor, current;
    double weight, newDist;
    //final path of ordered list of location
    vector<string> path;

    //makes sure the vector is not empty
    if (adjList.find(from) == adjList.end() || adjList.find(to) == adjList.end())
        return {};
    
    for (auto it = adjList.begin(); it != adjList.end(); ++it)
    {
        dist[it->first] = numeric_limits<double>::infinity();
        prev[it->first] = "";
    }

    //starting node has zero cost
    dist[from] = 0.0;

    using PQElement = pair<double, string>;

    priority_queue<PQElement, vector<PQElement>, greater<PQElement>> pq;

    //adding the first node to the priority queue
    pq.push({0.0, from});

    //looping while the priority queue is not empty
    while (!pq.empty())
    {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();

        //breaking from loop once the to node is encountered
        if (currentNode == to)
            break;

        if (currentDist > dist[currentNode])
            continue;

        //loop updating distance and reinserting the neighbor into the priority queue
        for (const Edge &edge : adjList.at(currentNode)) 
        {
            neighbor = edge.to;
            weight = edge.weight;
            newDist = dist[currentNode] + weight;

            if (newDist < dist[neighbor]) 
            {
                dist[neighbor] = newDist;
                prev[neighbor] = currentNode;
                pq.push({newDist, neighbor});
            }
        }
    }

    //making sure the graph is connected
    if (dist[to] == std::numeric_limits<double>::infinity())
        return {};
    
    current = to;

    while (current != from) 
    {
        path.push_back(current);
    
        if (prev.find(current) == prev.end() || prev[current] == "")
            return {};

        current = prev[current];
    }

    path.push_back(from);

    reverse(path.begin(), path.end());

    return path;
}

//method for printing each vertex and all the outgoing edges
void Graph::print() const
{
    for (auto it = adjList.begin(); it != adjList.end(); ++it)
    {
        cout << it->first << ": " << endl;
        for (auto it2 = adjList.at(it->first).begin(); it2 != adjList.at(it->first).end(); ++it2)
            cout << "(" << it2->to << ", " << it2->weight << ")" << endl;
    }
}