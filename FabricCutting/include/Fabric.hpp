#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>

/**
 * @brief This must be larger than the highest value in a or b.
 */
#define MAXVAL 50

struct Cut
{
	int a;
	int b;
	int p;
};

struct Fabric
{
	int n, x, y;
	std::vector<Cut> cuts;
	std::vector<int> frequencies;
	int bestValue;
	bool solved = false;
};

/**
 * @brief Reads the input as a fabric instance.
 * 
 * @return Fabric
 */
Fabric readInput()
{
	Fabric fabricInstance;
	fabricInstance.n = 0;

	std::cin >> fabricInstance.n;
	std::cin >> fabricInstance.x >> fabricInstance.y;

	fabricInstance.cuts.resize(fabricInstance.n);

	for (int i = 0; i < fabricInstance.n; i++)
	{
		std::cin >> fabricInstance.cuts[i].a;
	}

	for (int i = 0; i < fabricInstance.n; i++)
	{
		std::cin >> fabricInstance.cuts[i].b;
	}

	for (int i = 0; i < fabricInstance.n; i++)
	{
		std::cin >> fabricInstance.cuts[i].p;
	}

	return fabricInstance;
}

/**
 * @brief Prints the problem instance's details
 * 
 * @param instance Fabric instance problem.
 */
void printFabricInstance(Fabric *instance)
{
	std::cout << "~~~~~~ X ~~~~~~ X ~~~~~~" << std::endl;
	std::cout << "Number of possible cuts: " << instance->n << std::endl;
	std::cout << "Dimensions: " << instance->x << ", " << instance->y << std::endl;

	std::cout << "Cuts:" << std::endl;
	for (int i = 0; i < instance->n; i++)
	{
		std::cout << instance->cuts[i].a
				  << " x "
				  << instance->cuts[i].b
				  << " ~> R$ "
				  << instance->cuts[i].p
				  << std::endl;
	}

	if (instance->solved)
	{
		std::cout << "~~~~~~ X ~~~~~~" << std::endl;
		std::cout << "Best value: R$ " << instance->bestValue << std::endl;
		std::cout << "Frequencies of the cuts: ";

		for (int i : instance->frequencies)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "~~~~~~ X ~~~~~~ X ~~~~~~" << std::endl;
}

void solve(Fabric *instance)
{
	/**
	 * @brief Dynamic Programming Matrix for storing each cut combination values
	 */
	int cutsPrices[MAXVAL][MAXVAL] = {0};
	/**
	 * @brief Dynamic Programming Matrix for storing the frequencies of each cut index neatly
	 */
	std::multiset<int> cutsFrequencies[MAXVAL][MAXVAL];

	// Initializes the prices and frequencies matrices.
	for (int i = 0; i < instance->n; i++)
	{
		cutsPrices[instance->cuts[i].a][instance->cuts[i].b] = instance->cuts[i].p;
		cutsPrices[instance->cuts[i].b][instance->cuts[i].a] = instance->cuts[i].p;
		cutsFrequencies[instance->cuts[i].a][instance->cuts[i].b] = std::multiset<int>{i};
		cutsFrequencies[instance->cuts[i].b][instance->cuts[i].a] = std::multiset<int>{i};
	}

	for (int i = 0; i <= instance->x; i++)
	{
		for (int j = 0; j <= instance->y; j++)
		{
			std::multiset<int> localIdxFreq;
			int localBestVal = 0;

			for (int k = 0; k <= i / 2; k++)
			{
				if (localBestVal < cutsPrices[k][j] + cutsPrices[i - k][j])
				{
					localBestVal = cutsPrices[k][j] + cutsPrices[i - k][j];

					localIdxFreq.clear();

					for (auto w : cutsFrequencies[k][j])
						localIdxFreq.insert(w);

					for (auto w : cutsFrequencies[i - k][j])
						localIdxFreq.insert(w);
				}
			}

			for (int k = 0; k <= j / 2; k++)
			{
				if (localBestVal < cutsPrices[i][k] + cutsPrices[i][j - k])
				{
					localBestVal = cutsPrices[i][k] + cutsPrices[i][j - k];

					localIdxFreq.clear();

					for (auto w : cutsFrequencies[i][k])
						localIdxFreq.insert(w);

					for (auto w : cutsFrequencies[i][j - k])
						localIdxFreq.insert(w);
				}
			}

			cutsPrices[i][j] = localBestVal;
			cutsFrequencies[i][j] = localIdxFreq;
		}
	}

	std::vector<int> freq(instance->n, 0);
	for (int w : cutsFrequencies[instance->x][instance->y])
	{
		freq[w]++;
	}

	instance->bestValue = cutsPrices[instance->x][instance->y];
	instance->frequencies = freq;
	instance->solved = true;
}
