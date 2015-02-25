#ifndef NOT_IMPLEMENDED_EXCEPTION_HPP_
#define NOT_IMPLEMENDED_EXCEPTION_HPP_

#include <stdexcept>

class NotImplementedException : public std::logic_error
{
public:
    NotImplementedException() :
        std::logic_error("Function not implemented") {}
};

#endif  // NOT_IMPLEMENDED_EXCEPTION_HPP_
