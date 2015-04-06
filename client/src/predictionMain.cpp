
#include "prediction/KNeighborsFinderBuilder.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        return -1;
    }

    prediction::FileVector files;

    for (int i = 1; i < argc; i++)
    {
        files.emplace_back(argv[i]);
    }

    return 0;
}
