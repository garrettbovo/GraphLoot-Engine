#include <cassert>
#include <vector>
#include <string>
#include <iostream>

#include "WorldGraph.hpp"

using namespace std;

void add_test_nodes(Graph &graph)
{
    graph.addNode("Lonely Labs", 1, 6);
    graph.addNode("Anvil Square", 1, 4);
    graph.addNode("Mega City", 5, 4);
    graph.addNode("Brutal Bastion", 1, 2);
    graph.addNode("Slappy Shores", 3, 2);
    graph.addNode("Frenzy Fields", 6, 2);
    graph.addNode("Faulty Splits", 3, 1);
    graph.addNode("Shattered Slabs", 3, 0);
}

void test_shortest_path() 
{
    Graph graph;
    vector<string> expected, result;

    add_test_nodes(graph);

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
    result = graph.aStar("Mega City", "Shattered Slabs");

    assert(result == expected);
    assert(result.size() == 4);
}

void test_same_start_end()
{
    Graph g;
    vector<string> expected, result;

    g.addVertex("Mega City");
    g.addNode("Mega City", 5, 4);

    expected = {"Mega City"};
    result = g.aStar("Mega City", "Mega City");

    assert(result == expected);
    assert(result.size() == 1);
}

void unreachable()
{
    Graph g;

    add_test_nodes(g);

    g.addEdge("Mega City", "Frenzy Fields", 5);
    g.addEdge("Anvil Square", "Slappy Shores", 3);

    assert(g.aStar("Mega City", "Slappy Shores").empty());
}

int main() {
    test_shortest_path();
    test_same_start_end();
    unreachable();
    
    cout << "All tests passed!\n";
    
    return 0;
}
