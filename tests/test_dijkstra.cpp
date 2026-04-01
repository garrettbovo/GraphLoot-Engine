#include <cassert>
#include <vector>
#include <string>
#include <iostream>

#include "WorldGraph.hpp"

using namespace std;

void test_shortest_path() {
    Graph graph;
    vector<string> expected, result;

    graph.addEdge("Lonely Labs", "Anvil Square", 5.0);
    graph.addEdge("Lonely Labs", "Mega City", 6.5);
    graph.addEdge("Brutal Bastion", "Anvil Square", 4.0);
    graph.addEdge("Anvil Square", "Mega City", 3.5);
    graph.addEdge("Anvil Square", "Slappy Shores", 3.0);
    graph.addEdge("Mega City", "Slappy Shores", 2.0);
    graph.addEdge("Mega City", "Frenzy Fields", 5.5);
    graph.addEdge("Slappy Shores", "Faulty Splits", 4.0);
    graph.addEdge("Faulty Splits", "Frenzy Fields", 3.0);
    graph.addEdge("Faulty Splits", "Shattered Slabs", 2.5);
    graph.addEdge("Frenzy Fields", "Shattered Slabs", 4.5);

    expected = {"Mega City", "Slappy Shores", "Faulty Splits", "Shattered Slabs"};
    result = graph.shortestPath("Mega City", "Shattered Slabs");

    assert(result == expected);
    assert(result.size() == 4);
}

int main() {
    test_shortest_path();
    
    cout << "All tests passed!\n";
    
    return 0;
}