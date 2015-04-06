#ifndef PREDICTION_ASSISTANT_HPP_
#define PREDICTION_ASSISTANT_HPP_

#include <string>
#include <functional>

class PredictionAssistant
{
public:
    PredictionAssistant(unsigned recordSize,
        std::function<float(const InputRecord&)> distanceFunc);

    void addDatabaseFile(const std::string& file);
    void addTestFile(const std::string& file);

    void initPredictionAlgorithm();

private:
    FileVector databaseFiles_;
    FileVector testFiles_;

    const unsigned recordSize_;
    const std::function<float(const InputRecord&)> distanceFunction_;

    DistanceFunctions functions_;
    BasicKNeighborFinder finder_;
};

#endif  // PREDICTION_ASSISTANT_HPP_