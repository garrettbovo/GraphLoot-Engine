#include "WorldGraph.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <cmath>
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

//adding two-dimensional location to given vertex
void Graph::addNode(const string &vertex, const double &x, const double &y)
{
    //adding new Node to map
    nodes[vertex] = {vertex, x, y};
}

//method for implementing Dijkstra's algorithm
vector<string> Graph::shortestPath(const string &from, const string &to)
{
    //dist stores the shortest known path from distance to each from node
    unordered_map<string, double> dist;
    //prev stores the previous node on the shortest path
    unordered_map<string, string> prev;
    string neighbor, current;
    double newDist;
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
            newDist = dist[currentNode] + edge.weight;

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

//method returning a vector of the a* path from vertex A to vertex B
vector<string> Graph::aStar(const string &from, const string &to)
{
    //dist stores the shortest known path from distance to each from node
    unordered_map<string, double> gScore, fScore;
    //prev stores the previous node on the shortest path
    unordered_map<string, string> prev;
    string neighbor, current;
    double tentativeG;
    //final path of ordered list of location
    vector<string> path;

    //makes sure the vector is not empty
    if (adjList.find(from) == adjList.end() || adjList.find(to) == adjList.end())
        return {};
    
    for (auto it = adjList.begin(); it != adjList.end(); ++it)
    {
        gScore[it->first] = numeric_limits<double>::infinity();
        fScore[it->first] = numeric_limits<double>::infinity();
        prev[it->first] = "";
    }

    //starting node has zero cost
    gScore[from] = 0.0;
    //starting node is this far away from the second node
    fScore[from] = heuristic(from, to);

    using PQElement = pair<double, string>;

    priority_queue<PQElement, vector<PQElement>, greater<PQElement>> pq;

    //adding the first node to the priority queue
    pq.push({fScore[from], from});

    //looping while the priority queue is not empty
    while (!pq.empty())
    {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();

        //breaking from loop once the to node is encountered
        if (currentNode == to)
            break;

        if (currentDist > fScore[currentNode])
            continue;

        //loop updating distance and reinserting the neighbor into the priority queue
        for (const Edge &edge : adjList.at(currentNode)) 
        {
            neighbor = edge.to;

            tentativeG = gScore[currentNode] + edge.weight;

            if (tentativeG < gScore[neighbor]) 
            {
                prev[neighbor] = currentNode;
                gScore[neighbor] = tentativeG;
                fScore[neighbor] = tentativeG + heuristic(neighbor, to);
                pq.push({fScore[neighbor], neighbor});
            }
        }
    }

    //making sure the graph is connected
    if (gScore[to] == std::numeric_limits<double>::infinity())
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

//method for comparing path from vertex A to vertex B using shortest path and A*
vector<string> Graph::comparePaths(const string &from, const string &to)
{
    //dist stores the shortest known path from distance to each from node
    unordered_map<string, double> dist, gScore, fScore;
    //prev stores the previous node on the shortest path
    unordered_map<string, string> prev;
    string neighbor, current;
    double newDist, tentativeG;
    int nodesVisited = 0;
    //final path of ordered list of location
    vector<string> path;
    //creating file for writing statistics
    ofstream file("CompareAlgorithms.txt");

    //checking if the file opened correctly
    if (!file.is_open())
    {
        cerr << "Failed to open file." << endl;
        exit(0);
    }

    //makes sure the vector is not empty
    if (adjList.find(from) == adjList.end() || adjList.find(to) == adjList.end())
        return {};

    //DIJKSTRA
    {
        //starting the timer to time how long it takes to run dijkstra's algorithm
        auto startTime = chrono::high_resolution_clock::now();
        
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
            
            nodesVisited++;

            //loop updating distance and reinserting the neighbor into the priority queue
            for (const Edge &edge : adjList.at(currentNode)) 
            {
                neighbor = edge.to;
                newDist = dist[currentNode] + edge.weight;

                if (newDist < dist[neighbor]) 
                {
                    dist[neighbor] = newDist;
                    prev[neighbor] = currentNode;
                    pq.push({newDist, neighbor});
                }
            }
        }

        //making sure the graph is connected
        if (dist[to] == numeric_limits<double>::infinity())
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

        //stopping timer that timed the duration of dijkstra's algorithm
        auto endTime = chrono::high_resolution_clock::now();

        file << "================ COMPARISON ================\n\n";
        file << "Start: " << from << "\n";
        file << "End: " << to << "\n\n";

        file << "Dijkstra:\n";
        file << "Path Cost: " << dist[to] << "\n";
        file << "Nodes Explored: " << nodesVisited << "\n";
        file << "Time: " << chrono::duration<double, milli>(endTime - startTime).count() << " ms\n\n";
    }

    //reseting counter and path for next run of A* algorithm
    nodesVisited = 0;
    path.clear();

    //A*
    {
        //starting the timer to time how long it takes to run A* algorithm
        auto startTime = chrono::high_resolution_clock::now();
        
        for (auto it = adjList.begin(); it != adjList.end(); ++it)
        {
            gScore[it->first] = numeric_limits<double>::infinity();
            fScore[it->first] = numeric_limits<double>::infinity();
            prev[it->first] = "";
        }

        //starting node has zero cost
        gScore[from] = 0.0;
        //starting node is this far away from the second node
        fScore[from] = heuristic(from, to);

        using PQElement = pair<double, string>;

        priority_queue<PQElement, vector<PQElement>, greater<PQElement>> pq;

        //adding the first node to the priority queue
        pq.push({fScore[from], from});

        //looping while the priority queue is not empty
        while (!pq.empty())
        {
            auto [currentDist, currentNode] = pq.top();
            pq.pop();

            //breaking from loop once the to node is encountered
            if (currentNode == to)
                break;

            if (currentDist > fScore[currentNode])
                continue;
            
            nodesVisited++;

            //loop updating distance and reinserting the neighbor into the priority queue
            for (const Edge &edge : adjList.at(currentNode)) 
            {
                neighbor = edge.to;
                tentativeG = gScore[currentNode] + edge.weight;

                if (tentativeG < gScore[neighbor]) 
                {
                    prev[neighbor] = currentNode;
                    gScore[neighbor] = tentativeG;
                    fScore[neighbor] = tentativeG + heuristic(neighbor, to);
                    pq.push({fScore[neighbor], neighbor});
                }
            }
        }

        //making sure the graph is connected
        if (gScore[to] == numeric_limits<double>::infinity())
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

        //stopping timer that timed the duration of A* algorithm
        auto endTime = chrono::high_resolution_clock::now();

        file << "A*:\n";
        file << "Path Cost: " << gScore[to] << "\n";
        file << "Nodes Explored: " << nodesVisited << "\n";
        file << "Time: " << chrono::duration<double, milli>(endTime - startTime).count() << " ms\n\n";
        file << "===========================================\n\n";
    }

    file.close();

    return path;
}

//method for showing fastest route from Dijkstra
vector<string> Graph::routeDijsktra(const string &from, const string &to) const
{
    //dist stores the shortest known path from distance to each from node
    unordered_map<string, double> dist;
    //prev stores the previous node on the shortest path
    unordered_map<string, string> prev;
    string neighbor, current;
    double newDist;
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
            newDist = dist[currentNode] + edge.weight;

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

//method for showing fastest route from A*
vector<string> Graph::routeAStar(const string &from, const string &to) const
{
    //dist stores the shortest known path from distance to each from node
    unordered_map<string, double> gScore, fScore;
    //prev stores the previous node on the shortest path
    unordered_map<string, string> prev;
    string neighbor, current;
    double tentativeG;
    //final path of ordered list of location
    vector<string> path;

    //makes sure the vector is not empty
    if (adjList.find(from) == adjList.end() || adjList.find(to) == adjList.end())
        return {};
    
    for (auto it = adjList.begin(); it != adjList.end(); ++it)
    {
        gScore[it->first] = numeric_limits<double>::infinity();
        fScore[it->first] = numeric_limits<double>::infinity();
        prev[it->first] = "";
    }

    //starting node has zero cost
    gScore[from] = 0.0;
    //starting node is this far away from the second node
    fScore[from] = heuristic(from, to);

    using PQElement = pair<double, string>;

    priority_queue<PQElement, vector<PQElement>, greater<PQElement>> pq;

    //adding the first node to the priority queue
    pq.push({fScore[from], from});

    //looping while the priority queue is not empty
    while (!pq.empty())
    {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();

        //breaking from loop once the to node is encountered
        if (currentNode == to)
            break;

        if (currentDist > fScore[currentNode])
            continue;

        //loop updating distance and reinserting the neighbor into the priority queue
        for (const Edge &edge : adjList.at(currentNode)) 
        {
            neighbor = edge.to;

            tentativeG = gScore[currentNode] + edge.weight;

            if (tentativeG < gScore[neighbor]) 
            {
                prev[neighbor] = currentNode;
                gScore[neighbor] = tentativeG;
                fScore[neighbor] = tentativeG + heuristic(neighbor, to);
                pq.push({fScore[neighbor], neighbor});
            }
        }
    }

    //making sure the graph is connected
    if (gScore[to] == std::numeric_limits<double>::infinity())
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

//method for finding the distance between two nodes using x and y
double Graph::heuristic(const string &A, const string &B) const
{
    //calculating the distance between two two-dimensional nodes
    return sqrt(pow((nodes.at(B).x - nodes.at(A).x), 2) + pow((nodes.at(B).y - nodes.at(A).y), 2));
}