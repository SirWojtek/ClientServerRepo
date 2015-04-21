#ifndef KEY_GETTER_HPP_
#define KEY_GETTER_HPP_

#include "IKeyGetter.hpp"

class KeyGetter : public IKeyGetter
{
public:
    KeyGetter();
    ~KeyGetter();

    virtual char getPressedKey() const;
};

#endif  // KEY_GETTER_HPP_
