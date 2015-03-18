#ifndef FILE_POSITION_WRITER_HPP_
#define FILE_POSITION_WRITER_HPP_

#include <fstream>

#include "model/objects/Object.hpp"

#include "common/utilities/Console.hpp"

class FilePositionWriter
{
public:
    using Position = model::Object::Position;

    FilePositionWriter();

    void writePosition(const Position& pos);

private:
    std::ofstream dumpFile_;
    Console console_;
};

#endif  // FILE_POSITION_WRITER_HPP_
