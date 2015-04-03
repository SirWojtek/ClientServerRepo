
#include "KNeighborsFinderBuilder.hpp"

#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>

namespace prediction
{

using DataVector = std::vector<std::pair<unsigned, unsigned>>;

DataVector readDataFile(const std::string& dataFile)
{
    std::ifstream file(dataFile);
    DataVector result;

    while(file)
    {
        unsigned x, y;
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

void feedKNeighborsFinder(KNeighborsFinder<InputRecord, DeltaRecord>& finder,
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
    return splitDataVector(rawData, recordSize);
}

KNeighborsFinder<InputRecord, DeltaRecord> buildKNeighborsFinder(const std::string& dataFile,
    unsigned recordSize, std::function<unsigned(InputRecord)> distFunc)
{
    KNeighborsFinder<InputRecord, DeltaRecord> finder(distFunc);
    std::vector<DataVector> partitionedData = getPartitionedData(dataFile, recordSize);

    feedKNeighborsFinder(finder, partitionedData);

    return finder;
}

}