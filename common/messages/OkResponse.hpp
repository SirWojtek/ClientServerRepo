#ifndef OK_RESPONSE_HPP_
#define OK_RESPONSE_HPP_

#include <string>
#include <cereal/types/utility.hpp>

namespace common
{

struct OkResponse
{
	bool serverAllows;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(type, serverAllows);
    }

private:
    std::string type = "OkResponse";
};

}

#endif