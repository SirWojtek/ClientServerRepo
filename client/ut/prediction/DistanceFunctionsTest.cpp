
#include <gtest/gtest.h>
#include <vector>

#include "client/src/prediction/DistanceFunctions.hpp"

using namespace ::testing;
using namespace prediction;

class DistanceFunctionsShould : public ::testing::Test
{
protected:
    DistanceFunctionsShould()
    {}

    void SetUp()
    {
        std::vector<std::pair<int, int>> raw1 = {
            { 5, 5 }, { 5, 10 }, { 5, 15 }, { 5, 20 }, {5, 25}
        };
        std::vector<std::pair<int, int>> raw2 = {
            { 50, 20 }, { 55, 25 }, { 55, 25 }, { 40, 10 }, {30, 0}
        };

        input = InputRecord(raw1);
        comp = InputRecord(raw2);
        func.setInput(input);
    }

    InputRecord input;
    InputRecord comp;
    DistanceFunctions func;
};

TEST_F(DistanceFunctionsShould, returnCorrectStartPointsDistance)
{
    ASSERT_EQ(60, func.startPointsDistance(comp));
}

TEST_F(DistanceFunctionsShould, returnCorrectDirectionDistance)
{
    ASSERT_EQ(35, func.directionDistance(comp));
}

TEST_F(DistanceFunctionsShould, returnCorrectStartPointAndDirectionDistance)
{
    ASSERT_EQ(60 + 35, func.startPointsDistanceAndDirection(comp));
}

TEST_F(DistanceFunctionsShould, returnCorrectWeightStartPointAndDirectionDistance)
{
    const float weight = 0.4;
    DistanceFunctions::setWeight(weight);

    ASSERT_EQ(weight * 60 + (1 - weight) * 35, func.weightStartPointsDistanceAndDirection(comp));
}

TEST_F(DistanceFunctionsShould, returnCorrectReversedWeightStartPointAndDirectionDistance)
{
    const float weight = 0.4;
    DistanceFunctions::setWeight(weight);

    ASSERT_EQ((1 - weight) * 60 + weight * 35,
        func.reversedWeightStartPointsDistanceAndDirection(comp));
}
