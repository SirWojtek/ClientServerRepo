
#include "PredictionAssistant.hpp"
#include "KNeighborsFinderBuilder.hpp"

#include <algorithm>
#include <stdexcept>
#include <iostream>


namespace prediction
{

namespace
{
using namespace std::placeholders;

std::vector<DeltaRecord> possibleDirections{ {5, 0}, {-5, 0}, {0, 5}, {0, -5} };

}

PredictionAssistant::PredictionAssistant(unsigned recordSize, unsigned k,
    PredictionFunction distanceFunc, DirectionChooseFunction chooseFunc) :
        recordSize_(recordSize),
        recordsNumber_(-1),
        k_(k),
        distanceFunction_(distanceFunc),
        chooseFunction_(chooseFunc),
        deadReckoning_(possibleDirections),
        elapsedSec_(0.0) {}

PredictionAssistant::PredictionAssistant(unsigned recordSize, int recordsNumber, unsigned k,
    PredictionFunction distanceFunc, DirectionChooseFunction chooseFunc) :
        recordSize_(recordSize),
        recordsNumber_(recordsNumber),
        k_(k),
        distanceFunction_(distanceFunc),
        chooseFunction_(chooseFunc),
        elapsedSec_(0.0) {}

PredictionAssistant::~PredictionAssistant() {}

void PredictionAssistant::addDatabaseFile(const std::string& file)
{
    // std::cout << "Adding " << file << " as database file" << std::endl;
    databaseFiles_.emplace_back(file);
}

void PredictionAssistant::addTestFile(const std::string& file)
{
    // std::cout << "Adding " << file << " as test file" << std::endl;
    testFiles_.emplace_back(file);
}

void PredictionAssistant::initPredictionAlgorithm()
{
    elapsedSec_ = std::chrono::duration<double>(0.0);
    testDataSize_ = 0;
    finder_.reset(new BasicKNeighborFinder(
        buildKNeighborsFinder(databaseFiles_, recordSize_, recordsNumber_,
        std::bind(distanceFunction_, &functions_, _1))));
    // std::cout << "Successful loaded prediction algorithm" << std::endl;
    // finder_->printInfo();
}

std::vector<bool> PredictionAssistant::runTest()
{
    TestData testData = getTestData();
    testDataSize_ = testData.size();
    std::vector<bool> testResults;
    // std::cout << "Test iterations: " << testData.size() << std::endl;

    // std::cout << "Running test..." << std::endl;

    std::transform(testData.begin(), testData.end(), std::back_inserter(testResults),
        std::bind(&PredictionAssistant::getTestResult, this, _1));

    // std::cout << "Average getNeighbors time: " << elapsedSec_.count() / testData.size()
    //     << "s" << std::endl;

    return testResults;
}

std::vector<bool> PredictionAssistant::runDeadReckoningTest()
{
    TestData testData = getTestData();
    testDataSize_ = testData.size();
    std::vector<bool> testResults;
    // std::cout << "Test iterations: " << testData.size() << std::endl;

    // std::cout << "Running test..." << std::endl;

    std::transform(testData.begin(), testData.end(), std::back_inserter(testResults),
        std::bind(&PredictionAssistant::getTestResult, this, _1));

    // std::cout << "Average getNeighbors time: " << elapsedSec_.count() / testData.size()
    //     << "s" << std::endl;

    return testResults;
}

double PredictionAssistant::getElapsedTime() const
{
    return elapsedSec_.count() / testDataSize_;
}

PredictionAssistant::TestData PredictionAssistant::getTestData() const
{
    std::vector<DataVector> rawData = getPartitionedData(testFiles_, recordSize_);
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
    std::chrono::time_point<std::chrono::system_clock> start, end;
    functions_.setInput(test.first);

    start = std::chrono::system_clock::now();
    BasicKNeighborFinder::NeighborsVector finderResults = finder_->getNeighbors(k_);
    end = std::chrono::system_clock::now();

    elapsedSec_ += end - start;

    if (finderResults.empty())
    {
        throw std::runtime_error("KNeighborsFinder returns empty vector");
    }

    return chooseFunction_(finderResults) == test.second;
}

bool PredictionAssistant::getDeadReckoningTestResult(const std::pair<InputRecord, DeltaRecord>& test)
{
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    DeltaRecord output = deadReckoning_.getDeadReckoningPrediction(test.first);
    end = std::chrono::system_clock::now();

    elapsedSec_ += end - start;

    return output == test.second;
}

}
