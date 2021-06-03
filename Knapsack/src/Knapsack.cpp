#include "Knapsack.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

void Knapsack::setSize(int size)
{
    this->size = size;
}

int Knapsack::getSize()
{
    return this->size;
}

void Knapsack::readItemsFromFile(std::string filepath)
{
    std::ifstream file;
    file.open(filepath);

    int tmpSize;
    file >> tmpSize;
    Knapsack::setSize(tmpSize);

    int i = 0, v, w;
    while (true)
    {
        file >> v >> w;
        Knapsack::setItem(i++, v, w);
        if (file.eof())
            break;
    }
}

void Knapsack::setItem(int index, int value, int weight)
{
    this->items[index] = std::make_pair(value, weight);
}

Knapsack::solution Knapsack::solveFractionalKnapsack()
{
    Knapsack::solution result;
    std::vector<std::pair<int, float>> orderedCostBenefictVec;

    for (int i = 0; i < this->items.size(); i++)
    {
        float costBenefict = this->items[i].first 
                           / this->items[i].second;
    }
}

void Knapsack::printInstance()
{
    std::cout << "Knap size: " << Knapsack::getSize() << std::endl;
    std::cout << "Possible items: [";

    std::map<int, std::pair<int, int>>::iterator it;
    for (it = this->items.begin(); it != this->items.end(); it++)
    {
        std::cout << it->first << ": ("
                  << it->second.first << ", "
                  << it->second.second << "); ";
    }
    std::cout << std::endl;
}
