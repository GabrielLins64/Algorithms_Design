#include <iostream>
#include "Knapsack.hpp"

#define FILEPATH1 "data/input_A.txt"
#define FILEPATH2 "data/input_B.txt"
#define FILEPATH3 "data/input_C.txt"
#define FILEPATH4 "data/input_D.txt"

int main(int argc, char *argv[])
{
    Knapsack knap = Knapsack();
    knap.readItemsFromFile(FILEPATH3);

    // knap.printInstance();
    // Knapsack::solution sol = knap.solveFractionalKnapsack();
    Knapsack::solution sol = knap.solveUnboundedKnapsack();
    // Knapsack::solution sol = knap.solveGreedyUnboundedKnapsack();
    // Knapsack::solution sol = knap.solve01Knapsack();
    knap.printSolution(sol);

    return 0;
}
