#include <iostream>
#include "Knapsack.hpp"

#define FILEPATH1 "data/input_A.txt"
#define FILEPATH2 "data/input_B.txt"
#define FILEPATH3 "data/input_C.txt"

int main(int argc, char *argv[])
{
    Knapsack knap = Knapsack();
    knap.readItemsFromFile(FILEPATH1);
    // knap.readItemsFromFile(FILEPATH2);
    // knap.readItemsFromFile(FILEPATH3);

    // knap.printInstance();
    // Knapsack::solution sol = knap.solveFractionalKnapsack();
    Knapsack::solution sol = knap.solveUnboundedKnapsack();
    knap.printSolution(sol);

    return 0;
}
