
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

    prediction::InputRecord x;
    x.beginX = 100;
    x.beginY = 200;
    x.steps = { { 5, 0 }, { 5, 0 }, { 0, -5 } };

    auto neighbors = finder.getNeighbors(5);

    for (const auto& neighbor : neighbors)
    {
        std::cout << "positionX: " << neighbor.first.beginX << " positionY: " << neighbor.first.beginY << std::endl; 
        
        for (const auto& output : neighbor.second)
        {
            std::cout << "deltaX: " << output.first.deltaX << " deltaY: " << output.first.deltaY << " count: " << output.second << std::endl;
        }
    }

    return 0;
}
