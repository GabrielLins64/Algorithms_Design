#include "Knapsack.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>

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
    std::vector<float> fractionalVec(costBenefictVec.size(), 0.0);

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

Knapsack::solution Knapsack::solveUnboundedKnapsack()
{
    Knapsack::solution result;
    std::vector<float> solution[this->size + 1];
    for (int i = 0; i <= this->size; i++)
        solution[i] = std::vector<float>(this->items.size(), 0.0);
    int valueForWeight[this->size + 1];
    std::memset(valueForWeight, 0, sizeof valueForWeight);

    for (int i = 0; i <= this->size; i++)
    {
        for (int j = 0; j < this->items.size(); j++)
        {
            int w = this->items[j].second;
            if (w <= i) {
                int val = this->items[j].first;
                if (valueForWeight[i - w] + val > valueForWeight[i]) {
                    valueForWeight[i] = valueForWeight[i - w] + val;
                    solution[i] = solution[i - w];
                    solution[i][j] += 1;
                }
            }
        }
    }

    result.totalValue = valueForWeight[this->size];
    result.solution = solution[this->size];

    return result;
}

Knapsack::solution Knapsack::solve01Knapsack()
{
    Knapsack::solution result;
    int values[this->items.size() + 1][this->size + 1];
    std::vector<float> solution(this->items.size(), 0.0);

    for (int i = 0; i <= this->items.size(); i++)
        std::memset(values[i], 0, sizeof values[i]);
    
    for (int i = 1; i <= this->items.size(); i++)
    {
        for (int w = 1; w <= this->size; w++)
        {
            int preWeight = this->items[i - 1].second;
            if (preWeight <= w) {
                int preVal = this->items[i - 1].first;
                if (preVal + values[i - 1][w - preWeight] > values[i - 1][w]) {
                    values[i][w] = preVal + values[i - 1][w - preWeight];
                }
                else {
                    values[i][w] = values[i - 1][w];
                }
            }
            else
                values[i][w] = values[i - 1][w];
        }
    }

    int maxVal = values[this->items.size()][this->size];
    result.totalValue = maxVal;

    for (int i = this->items.size(), w = this->size; i > 0 && maxVal > 0; i--)
    {
        if (maxVal == values[i - 1][w])
            continue;
        else {
            solution[i - 1] = 1;
            maxVal -= this->items[i - 1].first;
            w -= this->items[i - 1].second;
        }
    }

    result.solution = solution;

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
