#include "Fabric.hpp"

#define _DEBUG false

int main (int argc, char **argv)
{
    Fabric fabricInstance = readInput();

#if _DEBUG
    printFabricInstance(&fabricInstance);
#endif

    solve(&fabricInstance);

    printFabricInstance(&fabricInstance);

    return 0;
}
