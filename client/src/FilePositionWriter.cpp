
#include "FilePositionWriter.hpp"

#include <chrono>
#include <sstream>


FilePositionWriter::FilePositionWriter() : console_("FilePositionWriter")
{
    using namespace std::chrono;

    std::stringstream stream;

    stream << time_point_cast<seconds>(system_clock::now()).time_since_epoch().count();

    std::string filename("position_" + stream.str() + ".log");
    dumpFile_.open(filename);

    console_.info << "Opened position dump file:" << filename;
}

void FilePositionWriter::writePosition(const model::Object::Position& pos)
{
    dumpFile_ << pos.x << "\t" << pos.y << std::endl;
}
