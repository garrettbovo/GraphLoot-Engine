#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <iomanip>

#include "WorldGraph.hpp"

using namespace std;
using namespace std::chrono;

struct BenchmarkResult
{
    string scenario;
    string algorithm;
    double avgMicros;
    double cost;
    int nodesVisited;
    int pathLength;
};

Graph buildPOIGraph()
{
    Graph g;
    g.addNode("Lonely Labs", 1, 6);
    g.addNode("Anvil Square", 1, 4);
    g.addNode("Mega City", 5, 4);
    g.addNode("Brutal Bastion", 1, 2);
    g.addNode("Slappy Shores", 3, 2);
    g.addNode("Frenzy Fields", 6, 2);
    g.addNode("Faulty Splits", 3, 1);
    g.addNode("Shattered Slabs", 3, 0);

    g.addEdge("Lonely Labs", "Anvil Square", 5.0);
    g.addEdge("Lonely Labs", "Mega City", 6.5);
    g.addEdge("Brutal Bastion", "Anvil Square", 4.0);
    g.addEdge("Anvil Square", "Mega City", 3.5);
    g.addEdge("Anvil Square", "Slappy Shores", 3.0);
    g.addEdge("Mega City", "Slappy Shores", 2.0);
    g.addEdge("Mega City", "Frenzy Fields", 5.5);
    g.addEdge("Slappy Shores", "Faulty Splits", 4.0);
    g.addEdge("Faulty Splits", "Frenzy Fields", 3.0);
    g.addEdge("Faulty Splits", "Shattered Slabs", 2.5);
    g.addEdge("Frenzy Fields", "Shattered Slabs", 4.5);
    return g;
}

Graph buildGrid(int rows, int cols)
{
    Graph g;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            g.addNode(to_string(r) + "," + to_string(c), (double)c, (double)r);

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            string cur = to_string(r) + "," + to_string(c);
            if (c + 1 < cols)
                g.addEdge(cur, to_string(r) + "," + to_string(c + 1), 1.0);
            if (r + 1 < rows)
                g.addEdge(cur, to_string(r + 1) + "," + to_string(c), 1.0);
            if (r + 1 < rows && c + 1 < cols)
                g.addEdge(cur, to_string(r + 1) + "," + to_string(c + 1), 1.414);
        }
    }
    return g;
}

BenchmarkResult runBenchmark(const string &scenario, const string &algo,
                             const Graph &g, const string &from, const string &to,
                             int iters)
{
    long long total = 0;
    PathResult last;
    for (int i = 0; i < iters; i++)
    {
        auto t0 = high_resolution_clock::now();
        last = (algo == "Dijkstra") ? g.runDijkstra(from, to) : g.runAStar(from, to);
        auto t1 = high_resolution_clock::now();
        total += duration_cast<microseconds>(t1 - t0).count();
    }
    return {scenario, algo, (double)total / iters, last.cost, last.nodesVisited, (int)last.path.size()};
}

void printTable(const vector<BenchmarkResult> &results)
{
    cout << "\n"
         << left
         << setw(22) << "Scenario"
         << setw(12) << "Algorithm"
         << setw(14) << "Avg (us)"
         << setw(10) << "Cost"
         << setw(14) << "NodesVisited"
         << setw(10) << "PathLen"
         << "\n"
         << string(82, '-') << "\n";

    for (const auto &r : results)
    {
        cout << left
             << setw(22) << r.scenario
             << setw(12) << r.algorithm
             << setw(14) << fixed << setprecision(3) << r.avgMicros
             << setw(10) << fixed << setprecision(2) << r.cost
             << setw(14) << r.nodesVisited
             << setw(10) << r.pathLength
             << "\n";
    }
    cout << "\n";
}

int main()
{
    const int ITERS = 1000;
    vector<BenchmarkResult> results;

    {
        Graph g = buildPOIGraph();
        results.push_back(runBenchmark("POI (8 nodes)", "Dijkstra", g, "Lonely Labs", "Shattered Slabs", ITERS));
        results.push_back(runBenchmark("POI (8 nodes)", "A*", g, "Lonely Labs", "Shattered Slabs", ITERS));
    }

    {
        Graph g = buildGrid(15, 15);
        results.push_back(runBenchmark("Grid 15x15", "Dijkstra", g, "0,0", "14,14", ITERS));
        results.push_back(runBenchmark("Grid 15x15", "A*", g, "0,0", "14,14", ITERS));
    }

    {
        Graph g = buildGrid(30, 30);
        results.push_back(runBenchmark("Grid 30x30", "Dijkstra", g, "0,0", "29,29", ITERS));
        results.push_back(runBenchmark("Grid 30x30", "A*", g, "0,0", "29,29", ITERS));
    }

    printTable(results);

    cout << "Speedup (Dijkstra avg / A* avg):\n";
    for (size_t i = 0; i + 1 < results.size(); i += 2)
    {
        double speedup = results[i].avgMicros / results[i + 1].avgMicros;
        cout << "  " << results[i].scenario << ": "
             << fixed << setprecision(2) << speedup << "x\n";
    }
    cout << "\n";

    return 0;
}
