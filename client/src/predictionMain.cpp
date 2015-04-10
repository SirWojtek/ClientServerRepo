
#include "prediction/PredictionAssistant.hpp"
#include "prediction/DistanceFunctions.hpp"

#include <iostream>
#include <algorithm>

prediction::FileVector getFiles(int argc, char** argv)
{
    prediction::FileVector files;

    for (int i = 1; i < argc; i++)
    {
        files.emplace_back(argv[i]);
    }

    return files;
}

int main(int argc, char** argv)
{
    using namespace prediction;

    if (argc < 2)
    {
        return -1;
    }

    FileVector files = getFiles(argc, argv);
    PredictionAssistant assistant(3, 3, &DistanceFunctions::startPointsDistance);

    for (unsigned i = 0; i < files.size() - 1; i++)
    {
        std::cout << "Adding " << files[i] << " as database file" << std::endl;
        assistant.addDatabaseFile(files[i]);
    }

    std::cout << "Adding " << files.back() << " as test file" << std::endl;
    assistant.addTestFile(files.back());
    assistant.initPredictionAlgorithm();
    std::cout << "Successful loaded prediction algorithm" << std::endl;

    std::cout << "Running test..." << std::endl;
    std::vector<bool> results = assistant.runTest();

    int passed = std::count_if(results.begin(), results.end(), [](bool a){ return a; });
    float floatPassed = static_cast<float>(passed)/static_cast<float>(results.size());
    std::cout << "Percent prediction match: " << floatPassed * 100 << std::endl;

    return 0;
}
