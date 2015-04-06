
#include "PredictionAssistant.hpp"
#include "KNeighborsFinderBuilder.hpp"

namespace prediction
{

PredictionAssistant::PredictionAssistant(unsigned recordSize,
    PredictionFunction distanceFunc) :
        recordSize_(recordSize),
        distanceFunction_(distanceFunc) {}

void PredictionAssistant::addDatabaseFile(const std::string& file)
{
    databaseFiles_.emplace_back(file);
}

void PredictionAssistant::addTestFile(const std::string& file)
{
    testFiles_.emplace_back(file);
}

void PredictionAssistant::initPredictionAlgorithm()
{
    using namespace std::placeholders;

    finder_.reset(new BasicKNeighborFinder(
        buildKNeighborsFinder(databaseFiles_, recordSize_,
        std::bind(distanceFunction_, &functions_, _1))));
}

}
