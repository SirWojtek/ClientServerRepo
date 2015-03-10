
#include "MapContainer.hpp"

#include <tmx/MapLoader.h>

namespace maps
{

MapContainer::MapContainer()
{
    tmx::MapLoader ml("path/to/maps");
    ml.Load("aaa");
}

}
