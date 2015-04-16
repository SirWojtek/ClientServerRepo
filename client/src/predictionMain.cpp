
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

void runTest(const FileVector& files, PredictionAssistant::PredictionFunction func, unsigned n)
{
    PredictionAssistant assistant(3, n, 3, func, prediction::getDirectionWithMaxOccurence);
    float floatPassed = 0;
    unsigned iterations = 1000;

    for (unsigned i = 0; i < files.size() - 1; i++)
    {
        assistant.addDatabaseFile(files[i]);
    }
    assistant.addTestFile(files.back());

    std::cout << "Iteration: ";
    for (unsigned i = 0; i < iterations; i++)
    {
        std::cout << i << " ";
        std::cout.flush();
        assistant.initPredictionAlgorithm();
        std::vector<bool> results = assistant.runTest();
        int passed = std::count_if(results.begin(), results.end(), [](bool a){ return a; });
        floatPassed += static_cast<float>(passed)/static_cast<float>(results.size());
    }

    floatPassed /= iterations;
    std::cout << std::endl << "Percent prediction match: " << floatPassed * 100 << std::endl;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        return -1;
    }

    FileVector files = getFiles(argc, argv);
    DistanceFunctions::setWeight(0.01);
    std::vector<unsigned> recordsNumber = { 100, 200, 500, 1000, 2000, 5000, 10000 };

    for (unsigned number : recordsNumber)
    {
        std::cout << "**** Testing with n = "<< number << " ***" << std::endl;

        std::cout << std::endl << "**** Testing with weight start points and direction distance ***" << std::endl;
        runTest(files, &DistanceFunctions::weightStartPointsDistanceAndDirection, number);
        std::cout << std::endl;
    }


    return 0;
}
