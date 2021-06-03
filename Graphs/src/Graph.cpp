#include "Graph.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <cmath>

Graph::Graph(int numVertices, bool weighted) : numVertices(numVertices),
                                               isWeighted(weighted)
{
    if (numVertices != 0)
    {
        adjacencyList = new std::list<int>[numVertices];
    }
}

Graph::Graph(std::string filepath, bool weighted)
{
    this->isWeighted = weighted;
    Graph::readFromFile(filepath);
}

void Graph::readFromFile(std::string filepath)
{
    std::ifstream file;
    file.open(filepath);

    int numVtx;
    file >> numVtx;

    Graph::setNumVertices(numVtx);

    if (isWeighted)
    {
        int u, v, w;
        while (true)
        {
            file >> u >> v >> w;
            Graph::addArch(u, v, w);
            if (file.eof())
                break;
        }
    }
    else
    {
        int u, v;
        while (true)
        {
            file >> u >> v;
            Graph::addArch(u, v);
            if (file.eof())
                break;
        }
    }
}

void Graph::setNumVertices(int numVertices)
{
    this->numVertices = numVertices;
    adjacencyList = new std::list<int>[numVertices];
}

int Graph::getNumVertices()
{
    return numVertices;
}

void Graph::addArch(int u, int v, int w)
{
    adjacencyList[u].push_back(v);
    weights[std::make_pair(u, v)] = w;
}

bool Graph::isCyclicAux(int v, bool visited[], bool *recursionStack)
{
    if (visited[v] == false)
    {
        visited[v] = true;
        recursionStack[v] = true;

        std::list<int>::iterator i;
        for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i)
        {
            if (!visited[*i] && isCyclicAux(*i, visited, recursionStack))
                return true;
            else if (recursionStack[*i])
                return true;
        }
    }

    recursionStack[v] = false;
    return false;
}

bool Graph::isCyclic()
{
    bool *visited = new bool[numVertices];
    bool *recursionStack = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        visited[i] = false;
        recursionStack[i] = false;
    }

    for (int i = 0; i < numVertices; i++)
    {
        if (Graph::isCyclicAux(i, visited, recursionStack))
        {
            return true;
        }
    }
    return false;
}

void Graph::topologicalSortAux(int v, bool visited[], std::stack<int> &stack)
{
    visited[v] = true;

    std::list<int>::iterator i;
    for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i)
    {
        if (!visited[*i])
            topologicalSortAux(*i, visited, stack);
    }
    stack.push(v);
}

std::stack<int> Graph::topologicalSort()
{
    std::stack<int> stack;

    if (isCyclic())
    {
        std::cout << "The Graph is not a DAG. Therefore isn't possible to topologically sort it.\n";
        return stack;
    }

    bool *visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;

    for (int i = 0; i < numVertices; i++)
    {
        if (!visited[i])
            Graph::topologicalSortAux(i, visited, stack);
    }

    return stack;
}

int Graph::shortestPathAux(int src, int dest)
{
    if (src == dest)
        return 0;
    else if (adjacencyList[src].size() == 0)
        return std::numeric_limits<int>::max();
    else
    {
        int minPath = std::numeric_limits<int>::max();

        std::list<int>::iterator i;
        for (i = adjacencyList[src].begin(); i != adjacencyList[src].end(); ++i)
        {
            int localDistance = weights[std::make_pair(src, *i)] + shortestPathAux(*i, dest);

            if (localDistance > 0 && localDistance < minPath)
            {
                minPath = localDistance;
            }
        }

        return minPath;
    }
}

Graph::Path Graph::shortestPath(int src, int dest)
{
    Graph::Path shortestPath;

    if (isCyclic())
    {
        std::cout << "The Graph must be a DAG!" << std::endl;
        shortestPath.distance = -1;
        return shortestPath;
    }

    shortestPath.distance = Graph::shortestPathAux(src, dest);
    return shortestPath;
}

void Graph::print(bool oneArchForLine)
{
    std::cout << "Graph num of vertices: " << numVertices << "\n";
    std::cout << "Archs:\n";
    for (int v = 0; v < numVertices; v++)
    {
        std::list<int>::iterator i;
        for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i)
        {
            std::cout << "(" << v << ", " << *i;
            if (isWeighted)
                std::cout << ", " << weights[std::make_pair(v, *i)];
            std::cout << ")";
            if (oneArchForLine)
                std::cout << std::endl;
            else
                std::cout << ", ";
        }
    }
    if (!oneArchForLine)
        std::cout << std::endl;
}
