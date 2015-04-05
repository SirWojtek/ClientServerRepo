
#include "KNeighborsFinderBuilder.hpp"

#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>

namespace prediction
{

using DataVector = std::vector<std::pair<int, int>>;

DataVector readDataFile(const std::string& dataFile)
{
    std::ifstream file(dataFile);
    DataVector result;

    while(file)
    {
        int x, y;
        file >> x >> y;

        result.emplace_back(x, y);
    }

    return result;
}

std::vector<DataVector> splitDataVector(const DataVector& dataVector, unsigned fixedSize)
{
    std::vector<DataVector> result;
    result.resize(dataVector.size() / fixedSize);
    auto currentElement = dataVector.begin();

    for (auto& data : result)
    {
        std::copy(currentElement, currentElement + fixedSize, std::back_inserter(data));
        currentElement += fixedSize;
    }

    return result;
}

void feedKNeighborsFinder(BasicKNeighborFinder& finder,
    const std::vector<DataVector> partitionedData)
{
    for (const auto& part : partitionedData)
    {
        InputRecord inputRecord(part);
        DeltaRecord outputRecord(part);
        finder.insert(inputRecord, outputRecord);
    }
}

std::vector<DataVector> getPartitionedData(const std::string& dataFile, unsigned recordSize)
{
    DataVector rawData = readDataFile(dataFile);
    std::vector<DataVector> result;

    for (unsigned i = 0; i < recordSize; i++)
    {
        const auto splitedData = splitDataVector(rawData, recordSize);
        result.insert(result.end(), splitedData.begin(), splitedData.end());
        rawData.erase(rawData.begin());
    }

    return result;
}

BasicKNeighborFinder buildKNeighborsFinder(const std::string& dataFile,
    unsigned recordSize, std::function<int(const InputRecord&)> distFunc)
{
    BasicKNeighborFinder finder(distFunc);
    std::vector<DataVector> partitionedData = getPartitionedData(dataFile, recordSize);

    feedKNeighborsFinder(finder, partitionedData);

    return finder;
}

}