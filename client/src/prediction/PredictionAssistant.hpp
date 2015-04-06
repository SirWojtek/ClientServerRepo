#ifndef PREDICTION_ASSISTANT_HPP_
#define PREDICTION_ASSISTANT_HPP_

#include "DistanceFunctions.hpp"
#include "PredictionDefinitions.hpp"

#include <string>
#include <functional>
#include <memory>
#include <vector>

namespace prediction
{

class PredictionAssistant
{
public:
    using PredictionFunction =
        std::function<float(const DistanceFunctions*, const InputRecord&)>;

    PredictionAssistant(unsigned recordSize,
        PredictionFunction distanceFunc);

    void addDatabaseFile(const std::string& file);
    void addTestFile(const std::string& file);

    void initPredictionAlgorithm();

private:
    FileVector databaseFiles_;
    FileVector testFiles_;

    const unsigned recordSize_;
    const PredictionFunction distanceFunction_;

    DistanceFunctions functions_;
    std::unique_ptr<BasicKNeighborFinder> finder_;
};

}

#endif  // PREDICTION_ASSISTANT_HPP_