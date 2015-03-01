#ifndef OK_RESPONSE_HPP_
#define OK_RESPONSE_HPP_

#include <string>

namespace common
{

struct OkResponse
{
	bool serverAllows;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(type()), CEREAL_NVP(serverAllows));
    }

    static std::string type()
    {
        return std::string("OkResponse");
    }

    bool operator==(const OkResponse& a) const
    {
        return serverAllows == a.serverAllows;
    }
};

}

#endif