
#include <gtest/gtest.h>

#include "client/src/prediction/DirectionChooseFunctions.hpp"
#include "client/src/prediction/Records.hpp"

using namespace ::testing;
using namespace prediction;

class DirectionChooseFunctionShould : public ::testing::Test
{
protected:
    DirectionChooseFunctionShould()
    {}

    void SetUp()
    {
        delta1 = DeltaRecord({{ 0, 0 }, { 0, 5 }});
        delta2 = DeltaRecord({{ 0, 0 }, { 5, 0 }});


        BasicKNeighborFinder::OutputHistogram hist1 = {
            { delta1, 1 }, { delta2, 2 }
        };
        BasicKNeighborFinder::OutputHistogram hist2 = {
            { delta1, 3 }, { delta2, 1 }
        };

        InputRecord rec1({
            { 5, 5 }, { 5, 10 }, { 5, 15 }, { 5, 20 }, {5, 25}
        });
        InputRecord rec2({
            { 5, 5 }, { 5, 10 }, { 5, 15 }, { 5, 20 }, {5, 25}
        });

        neighbors = { { rec1, hist1 }, { rec2, hist2 } };
    }

    DeltaRecord delta1, delta2;
    BasicKNeighborFinder::NeighborsVector neighbors;
};

TEST_F(DirectionChooseFunctionShould, returnCorrectClosestNeighborDirectionWithMaxOccurence)
{
    ASSERT_EQ(delta2, getClosestNeighborDirectionWithMaxOccurence(neighbors));
}

TEST_F(DirectionChooseFunctionShould, returnCorrectDirectionWithMaxOccurence)
{
    ASSERT_EQ(delta1, getDirectionWithMaxOccurence(neighbors));
}
