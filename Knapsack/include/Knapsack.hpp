#ifndef __KNAPSACK_HPP__
#define __KNAPSACK_HPP__

#include <map>
#include <list>
#include <vector>
#include <string>

class Knapsack
{
private:
    std::map<int, std::pair<float, float>> items;
    int size;

public:
    Knapsack() {};
    ~Knapsack() {};
    struct solution {
        int totalValue;
        std::vector<float> solution;
    };

    int getSize();
    void setSize(int size);
    void setItem(int index, int value, int weight);
    void readItemsFromFile(std::string filepath);
    solution solveFractionalKnapsack();
    void printInstance();
    void printSolution(solution sol);
};

#endif
