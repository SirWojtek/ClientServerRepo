
#include "PredictionAssistant.hpp"
#include "KNeighborsFinderBuilder.hpp"

#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace prediction
{

using namespace std::placeholders;

PredictionAssistant::PredictionAssistant(unsigned recordSize, unsigned k,
    PredictionFunction distanceFunc) :
        recordSize_(recordSize),
        k_(k),
        distanceFunction_(distanceFunc) {}

PredictionAssistant::~PredictionAssistant() {}

void PredictionAssistant::addDatabaseFile(const std::string& file)
{
    std::cout << "Adding " << file << " as database file" << std::endl;
    databaseFiles_.emplace_back(file);
}

void PredictionAssistant::addTestFile(const std::string& file)
{
    std::cout << "Adding " << file << " as test file" << std::endl;
    testFiles_.emplace_back(file);
}

void PredictionAssistant::initPredictionAlgorithm()
{
    finder_.reset(new BasicKNeighborFinder(
        buildKNeighborsFinder(databaseFiles_, recordSize_,
        std::bind(distanceFunction_, &functions_, _1))));
    std::cout << "Successful loaded prediction algorithm" << std::endl;
}

std::vector<bool> PredictionAssistant::runTest()
{
    TestData testData = getTestData();
    std::vector<bool> testResults;
    std::cout << "Test iterations: " << testData.size() << std::endl;

    std::cout << "Running test..." << std::endl;
    std::transform(testData.begin(), testData.end(), std::back_inserter(testResults),
        std::bind(&PredictionAssistant::getTestResult, this, _1));

    return testResults;
}

PredictionAssistant::TestData PredictionAssistant::getTestData() const
{
    std::vector<DataVector> rawData = getPartitionedData(testFiles_, 2);
    TestData result;

    std::transform(rawData.begin(), rawData.end(), std::inserter(result, result.begin()),
        std::bind(&PredictionAssistant::convertToTestData, this, _1));

    return result;
}

std::pair<InputRecord, DeltaRecord> PredictionAssistant::convertToTestData(
    const DataVector& raw) const
{
    return std::pair<InputRecord, DeltaRecord>{ InputRecord(raw), DeltaRecord(raw) };
}

bool PredictionAssistant::getTestResult(const std::pair<InputRecord, DeltaRecord>& test)
{
    functions_.setInput(test.first);
    BasicKNeighborFinder::NeighborsVector finderResults = finder_->getNeighbors(k_);

    if (finderResults.empty())
    {
        throw std::runtime_error("KNeighborsFinder returns empty vector");
    }

    BasicKNeighborFinder::OutputHistogram histogram = finderResults[0].second;

    auto bestMatch = std::max_element(histogram.begin(), histogram.end(),
        [](const std::pair<DeltaRecord, unsigned>& a, const std::pair<DeltaRecord, unsigned>& b)
        {
            return a.second < b.second;
        });

    return bestMatch->first == test.second;
}

}
