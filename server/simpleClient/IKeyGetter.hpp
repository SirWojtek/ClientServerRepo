#ifndef IKEY_GETTER_HPP_
#define IKEY_GETTER_HPP_

#include <memory>

class IKeyGetter
{
public:
    virtual char getPressedKey() const = 0;
};
using KeyGetterPtr = std::shared_ptr<IKeyGetter>;

#endif  // IKEY_GETTER_HPP_