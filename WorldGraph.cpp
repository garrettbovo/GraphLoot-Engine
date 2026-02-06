#include "WorldGraph.hpp"

#include <iostream>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
using namespace std;

void Graph::addVertex(const string &node)
{
    for (auto it = adjList.begin(); it != adjList.end(); ++it)
        if (it->first == node)
            return;
    
    adjList[node] = {};
}

void Graph::addEdge(const string &from, const string &to, const double &weight)
{
    if (adjList.find(from) == adjList.end())
        addVertex(from);
    
    if (adjList.find(to) == adjList.end())
        addVertex(to);

    adjList[from].push_back({to, weight});
    adjList[to].push_back({from, weight});
}

vector<string> Graph::shortestPath(const string &from, const string &to)
{
    unordered_map<string, double> dist;
    unordered_map<string, string> prev;
    string neighbor, current;
    double weight, newDist;
    vector<string> path;

    if (adjList.find(from) == adjList.end() || adjList.find(to) == adjList.end())
        return {};
    
    for (auto it = adjList.begin(); it != adjList.end(); ++it)
    {
        dist[it->first] = numeric_limits<double>::infinity();
        prev[it->first] = "";
    }

    dist[from] = 0.0;

    using PQElement = pair<double, string>;

    priority_queue<PQElement, vector<PQElement>, greater<PQElement>> pq;


    pq.push({0.0, from});

    while (!pq.empty())
    {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();

        if (currentNode == to)
            break;

        if (currentDist > dist[currentNode])
            continue;

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

void Graph::print() const
{
    for (auto it = adjList.begin(); it != adjList.end(); ++it)
    {
        cout << it->first << ": " << endl;
        for (auto it2 = adjList.at(it->first).begin(); it2 != adjList.at(it->first).end(); ++it2)
            cout << "(" << it2->to << ", " << it2->weight << ")" << endl;
    }
}