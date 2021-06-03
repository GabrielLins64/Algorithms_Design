#ifndef __GRAPH__
#define __GRAPH__

#include <list>
#include <map>
#include <stack>
#include <string>

class Graph
{
    int numVertices;
    bool isWeighted;
    std::list<int> *adjacencyList;
    std::map<std::pair<int, int>, int> weights;
    bool isCyclicAux(int v, bool visited[], bool *recursionStack);
    void topologicalSortAux(int v, bool visited[], std::stack<int> &stack);
    int shortestPathAux(int src, int dest);

public:
    Graph(int numVertices = 0, bool weighted = false);
    Graph(std::string filepath, bool weighted = false);
    struct Path
    {
        int distance;
        std::list<int> path;
    };
    void readFromFile(std::string filepath);
    void setNumVertices(int numVertices);
    int getNumVertices();
    void addArch(int u, int v, int w = 1);
    bool isCyclic();
    std::stack<int> topologicalSort();
    Path shortestPath(int src, int dest);
    void print(bool oneArchForLine = false);
};

#endif
