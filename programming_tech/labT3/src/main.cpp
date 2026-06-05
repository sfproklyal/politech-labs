#include "commands.h"
#include "polygon.h"

#include <exception>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: filename is not specified" << '\n';
    return 1;
  }

  try
  {
    const std::vector< Polygon > polygons = readPolygonsFromFile(argv[1]);
    processCommands(polygons);
  }
  catch (const std::exception& exception)
  {
    std::cerr << "Error: " << exception.what() << '\n';
    return 1;
  }

  return 0;
}
