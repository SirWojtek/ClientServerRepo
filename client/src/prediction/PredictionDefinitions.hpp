#ifndef PREDICTION_DEFINITIONS_HPP_
#define PREDICTION_DEFINITIONS_HPP_

#include <vector>
#include <string>

namespace prediction
{

template<class T_input, class T_output>
class KNeighborsFinder;
struct InputRecord;
struct DeltaRecord;

using BasicKNeighborFinder = KNeighborsFinder<InputRecord, DeltaRecord>;
using FileVector = std::vector<std::string>;

}

#endif  // PREDICTION_DEFINITIONS_HPP_