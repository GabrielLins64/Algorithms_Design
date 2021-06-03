#include "Graph.hpp"
#include "Tests.hpp"
#include <iostream>

#define FILEPATH1 "data/digraph1.txt"
#define FILEPATH2 "data/digraph2.txt"
#define FILEPATH3 "data/weightedDigraph.txt"

int main()
{
    // Graph g(FILEPATH1);
    // Graph g(FILEPATH2);
    Graph g(FILEPATH3, true);

    // g.print();

    // testIfIsCyclic(g);
    // testTopologicalSort(g);
    testShortestPath(g, 2, 12);

    return 0;
}