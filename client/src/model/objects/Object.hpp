#ifndef MODEL_OBJECT_HPP_
#define MODEL_OBJECT_HPP_

#include <string>
#include <memory>

#include <SFML/Graphics/Rect.hpp>

namespace model
{

class Object
{
public:
    struct Position
    {
        int x, y;

        bool operator==(const Position& pos) const
        {
            return x == pos.x && y == pos.y;
        }
    };

    Object(Position position = {0, 0}, unsigned size = 0, bool isStatic = false);
    explicit Object(bool isStatic);


    Position position;
    unsigned size;
    bool isStatic;

    virtual void getTexture() const;
    virtual std::string getDescription() const;
    virtual sf::FloatRect getPositionRect() const;

    virtual bool operator<(const Object& a) const;
    virtual bool operator>(const Object& a) const;
    virtual bool operator==(const Object& a) const;
    virtual bool operator!=(const Object& a) const;
};
using ObjectPtr = std::shared_ptr<Object>;

}

#endif  // MODEL_OBJECT_HPP_
