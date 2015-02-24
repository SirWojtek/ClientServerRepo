#ifndef MODEL_OBJECT_HPP_
#define MODEL_OBJECT_HPP_

#include <string>


namespace model
{

class Object
{
public:
    struct Position
    {
        int x,y;
    };

    Position position;
    bool isStatic;

    virtual void getTexture() const;
    virtual std::string getDescription() const;

    virtual bool operator<(const Object& a) const;
    virtual bool operator>(const Object& a) const;
    virtual bool operator==(const Object& a) const;
    virtual bool operator!=(const Object& a) const;
};
}

#endif  // MODEL_OBJECT_HPP_
