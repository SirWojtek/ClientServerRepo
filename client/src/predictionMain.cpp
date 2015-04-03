
#include "prediction/KNeighborsFinderBuilder.hpp"

#include <complex>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        return -1;
    }

    std::string dataFile(argv[1]);
    prediction::InputRecord x;
    x.beginX = 100;
    x.beginY = 200;
    x.steps = { { 5, 0 }, { 5, 0 }, { 0, -5 } };

    prediction::BasicKNeighborFinder finder =
        prediction::buildKNeighborsFinder(dataFile, 4,
            [&x](const prediction::InputRecord& a)
            {
                return std::abs(a.beginX - x.beginX) + std::abs(a.beginX - x.beginX);
            });

    auto neighbors = finder.getNeighbors(5);

    for (const auto& neighbor : neighbors)
    {
        std::cout << "deltaX: " << neighbor.deltaX << " deltaY: " << neighbor.deltaY;
    }

    return 0;
}
