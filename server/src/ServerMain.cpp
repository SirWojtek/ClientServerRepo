#include <stdexcept>
#include "Server.hpp"

int main(int argc, char* argv[])
{
  try
  {
    Server s();
  }
  catch(const std::runtime_error& e)
  {
    throw std::runtime_error(e.what());
  }
  
  return 0;
}