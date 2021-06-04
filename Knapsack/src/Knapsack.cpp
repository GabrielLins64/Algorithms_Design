#include "Knapsack.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

#define _DEBUG false

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
    std::vector<std::pair<int, float>> costBenefictVec;

    costBenefictVec.push_back(
        std::make_pair(
            0, 
            this->items[0].first / this->items[0].second
        )
    );

    for (int i = 1; i < this->items.size(); i++)
    {
        float costBenefict = this->items[i].first
                           / this->items[i].second;

        int j = 0;
        while (j < costBenefictVec.size() && costBenefictVec[j].second >= costBenefict)
        {
            j++;
        }

        costBenefictVec.insert(
            costBenefictVec.begin() + j,
            std::make_pair(i, costBenefict)
        );
    }

#if _DEBUG
    std::cout << "Cost-benefict vec: ";
    for (auto it = costBenefictVec.begin(); it != costBenefictVec.end(); ++it)
        std::cout << "(" << it->first << ", " << it->second << ") ";
    std::cout << std::endl;
#endif

    float remainingWeight = float(this->size);
    float totalValue = 0;
    std::vector<float> fractionalVec;

    for (int i = 0; i < costBenefictVec.size(); i++)
        fractionalVec.push_back(0.0);

    int i;
    for (i = 0; i < costBenefictVec.size(); i++)
    {
        int itemValue = this->items[costBenefictVec[i].first].first;
        int itemWeight = this->items[costBenefictVec[i].first].second;

        if (remainingWeight - itemWeight < 0) {
            float lastItemPercentage = remainingWeight / itemWeight;
            fractionalVec[costBenefictVec[i].first] = lastItemPercentage;
            totalValue += itemValue * lastItemPercentage;
            break;
        }

        remainingWeight -= itemWeight;
        fractionalVec[costBenefictVec[i].first] = 1.0;
        totalValue += itemValue;
    }

    result.totalValue = totalValue;
    result.solution = fractionalVec;

    return result;
}

void Knapsack::printInstance()
{
    std::cout << "Knap size: " << Knapsack::getSize() << std::endl;
    std::cout << "All items: [";

    std::map<int, std::pair<float, float>>::iterator it;
    for (it = this->items.begin(); it != this->items.end(); it++)
    {
        std::cout << it->first << ": ("
                  << it->second.first << ", "
                  << it->second.second << "); ";
    }
    std::cout << std::endl;
}

void Knapsack::printSolution(Knapsack::solution sol)
{
    std::cout << "Solution value: " << sol.totalValue << std::endl;
    std::cout << "Solution: [ ";
    for (auto it = sol.solution.begin(); it != sol.solution.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "]" << std::endl;
}
