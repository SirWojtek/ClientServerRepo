
#include "KNeighborsFinderBuilder.hpp"

#include <utility>
#include <fstream>
#include <algorithm>

namespace prediction
{

DataVector readDataFile(const std::string& dataFile)
{
    std::ifstream file(dataFile);
    DataVector result;
    int x, y;

    while((file >> x >> y))
    {
        result.emplace_back(x, y);
    }

    return result;
}

std::vector<DataVector> readFiles(const FileVector& dataFiles)
{
    std::vector<DataVector> result;

    for (const auto& file : dataFiles)
    {
        result.emplace_back(readDataFile(file));
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

void fillPartitionedData(DataVector& rawData,
    std::vector<DataVector>& partitionedData, unsigned recordSize)
{
    for (unsigned i = 0; i < recordSize; i++)
    {
        if (rawData.size() < recordSize)
        {
            break;
        }

        const auto splitedData = splitDataVector(rawData, recordSize);
        partitionedData.insert(partitionedData.end(), splitedData.begin(), splitedData.end());
        rawData.erase(rawData.begin());
    }
}

std::vector<DataVector> getPartitionedData(const FileVector& dataFiles, unsigned recordSize)
{
    std::vector<DataVector> rawData = readFiles(dataFiles);
    std::vector<DataVector> partitionedData;

    for (DataVector& dataFromFile : rawData)
    {
        fillPartitionedData(dataFromFile, partitionedData, recordSize);
    }

    return partitionedData;
}

BasicKNeighborFinder buildKNeighborsFinder(const FileVector& dataFiles,
    unsigned recordSize, std::function<float(const InputRecord&)> distFunc)
{
    BasicKNeighborFinder finder(distFunc);
    std::vector<DataVector> partitionedData = getPartitionedData(dataFiles, recordSize);

    feedKNeighborsFinder(finder, partitionedData);

    return finder;
}

}