
#include "PredictionAssistant.hpp"
#include "KNeighborsFinderBuilder.hpp"
#include "DistanceFunctions.hpp"

namespace prediction
{

PredictionAssistant::PredictionAssistant(unsigned recordSize, 
    std::function<float(const InputRecord&)> distanceFunc) :
        recordSize_(recordSize),

{

}

void PredictionAssistant::addDatabaseFile(const std::string& file)
{
    databaseFiles_.emplace_front(file);
}

void PredictionAssistant::addTestFile(const std::string& file)
{
    testFiles_.emplace_front(file);
}

void PredictionAssistant::initPredictionAlgorithm()
{
    using namespace std::placeholders;

    finder_.reset(buildKNeighborsFinder(databaseFiles_, recordSize,
        std::bind(distanceFunction, functions, _1)));
}

}
