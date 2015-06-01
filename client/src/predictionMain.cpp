
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

void runTest(const FileVector& files)
{
    PredictionAssistant assistant(0, 0, 0, nullptr, nullptr);
    float floatPassed = 0;
    double duration = 0.0;
    unsigned iterations = 1000;

    for (unsigned i = 0; i < files.size(); i++)
    {
        assistant.addDatabaseFile(files[i]);
    }

    std::cout << "Iteration: ";
    for (unsigned i = 0; i < iterations; i++)
    {
        std::cout << i + 1 << " ";
        std::cout.flush();
        std::vector<bool> results = assistant.runDeadReckoningTest();
        int passed = std::count_if(results.begin(), results.end(), [](bool a){ return a; });
        floatPassed += static_cast<float>(passed)/static_cast<float>(results.size());
        duration += assistant.getElapsedTime();
    }

    floatPassed /= iterations;
    duration /= iterations;
    std::cout << std::endl << "Percent prediction match: " << floatPassed * 100 << std::endl;
    std::cout << std::endl << "Elapsed time: " << duration << std::endl;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        return -1;
    }

    FileVector files = getFiles(argc, argv);

    std::cout << std::endl << "**** Testing Dead Reckoning ***" << std::endl;
    runTest(files);
    std::cout << std::endl;

    return 0;
}
