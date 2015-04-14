
#include "prediction/PredictionAssistant.hpp"
#include "prediction/DistanceFunctions.hpp"
#include "prediction/DirectionChooseFunctions.hpp"

#include <iostream>
#include <algorithm>

using namespace prediction;

FileVector getFiles(int argc, char** argv)
{
    prediction::FileVector files;

    for (int i = 1; i < argc; i++)
    {
        files.emplace_back(argv[i]);
    }

    return files;
}

void runTest(const FileVector& files, PredictionAssistant::PredictionFunction func)
{
    PredictionAssistant assistant(3, 3, func, prediction::getDirectionWithMaxOccurence);

    for (unsigned i = 0; i < files.size() - 1; i++)
    {
        assistant.addDatabaseFile(files[i]);
    }

    assistant.addTestFile(files.back());
    assistant.initPredictionAlgorithm();
    std::vector<bool> results = assistant.runTest();

    int passed = std::count_if(results.begin(), results.end(), [](bool a){ return a; });
    float floatPassed = static_cast<float>(passed)/static_cast<float>(results.size());
    std::cout << "Percent prediction match: " << floatPassed * 100 << std::endl;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        return -1;
    }

    FileVector files = getFiles(argc, argv);

    // std::cout << "**** Testing with start points distance ***" << std::endl;
    // runTest(files, &DistanceFunctions::startPointsDistance);
    // std::cout << std::endl << "**** Testing with direction distance ***" << std::endl;
    // runTest(files, &DistanceFunctions::directionDistance);
    // std::cout << std::endl << "**** Testing with start points and direction distance ***" << std::endl;
    // runTest(files, &DistanceFunctions::startPointsDistanceAndDirection);

    // for (float i = 0.0; i < 0.01; i += 0.002)
    // {
    //     std::cout << std::endl << "**** Testing with start points and direction distance with weight: "
    //         << i << " ***" << std::endl;
    //     DistanceFunctions::setWeight(i);
    //     runTest(files, &DistanceFunctions::weightStartPointsDistanceAndDirection);
    // }

    // for (float i = 0.01; i < 0.1; i += 0.01)
    // {
    //     std::cout << std::endl << "**** Testing with start points and direction distance with weight: "
    //         << i << " ***" << std::endl;
    //     DistanceFunctions::setWeight(i);
    //     runTest(files, &DistanceFunctions::weightStartPointsDistanceAndDirection);
    // }

        DistanceFunctions::setWeight(1.0);
        runTest(files, &DistanceFunctions::weightStartPointsDistanceAndDirection);

    return 0;
}
