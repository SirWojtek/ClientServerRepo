#ifndef MODEL_OBJECT_HPP_
#define MODEL_OBJECT_HPP_

#include <string>
#include <memory>

namespace model
{

class Object
{
public:
    struct Position
    {
        int x,y;
    };

    Object();
    explicit Object(bool isStatic);
    explicit Object(Position position);
    Object(Position position, bool isStatic);

    Position position;
    bool isStatic;

    virtual void getTexture() const;
    virtual std::string getDescription() const;

    virtual bool operator<(const Object& a) const;
    virtual bool operator>(const Object& a) const;
    virtual bool operator==(const Object& a) const;
    virtual bool operator!=(const Object& a) const;
};
using ObjectPtr = std::shared_ptr<Object>;

}

#endif  // MODEL_OBJECT_HPP_
