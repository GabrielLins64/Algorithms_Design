#ifndef __TESTS_HPP__
#define __TESTS_HPP__

#include "Graph.hpp"
#include <limits>
#include <iostream>

void testIfIsCyclic(Graph g)
{
    if(g.isCyclic())
        std::cout << "Graph isn't a DAG. It contains a cycle!\n";
    else
        std::cout << "Graph is a Directed Acyclic Graph!\n";
}

void testTopologicalSort(Graph g)
{
    std::stack<int> stack = g.topologicalSort();

    if (!stack.empty()) 
    {
        std::cout << "Topological Sort: ";
        while (!stack.empty())
        {
            std::cout << stack.top() << " ";
            stack.pop();
        }
        std::cout << "\n";
    }
}

void testShortestPath(Graph g, int src, int dest)
{
    Graph::Path shortestPath = g.shortestPath(src, dest);
    if (shortestPath.distance == std::numeric_limits<int>::max())
        std::cout << "There is no path between nodes " << src << " and " << dest << std::endl;
    else
        std::cout << "Shortest Path distance: " << shortestPath.distance << std::endl;
}

#endif
