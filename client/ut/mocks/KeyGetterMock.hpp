#ifndef KEY_GETTER_MOCK_
#define KEY_GETTER_MOCK_

#include <memory>
#include <gmock/gmock.h>

#include "client/src/IKeyGetter.hpp"

class KeyGetterMock : public IKeyGetter
{
public:
    MOCK_CONST_METHOD0(getPressedKey, char());
};
using KeyGetterMockPtr = std::shared_ptr<KeyGetterMock>;

#endif  // KEY_GETTER_MOCK_
