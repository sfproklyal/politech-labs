#include "commands.h"

#include "methods.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
  void printInvalidCommand()
  {
    std::cout << "<INVALID COMMAND>" << '\n';
  }

  std::vector< std::string > splitWords(const std::string& line)
  {
    std::istringstream input(line);
    std::vector< std::string > words;

    std::copy(
      std::istream_iterator< std::string >(input),
      std::istream_iterator< std::string >(),
      std::back_inserter(words)
    );

    return words;
  }

  bool isUnsignedNumber(const std::string& text)
  {
    return !text.empty()
        && std::all_of(
             text.cbegin(),
             text.cend(),
             [](unsigned char ch)
             {
               return std::isdigit(ch);
             }
           );
  }

  std::size_t parseVertexCount(const std::string& text)
  {
    if (!isUnsignedNumber(text))
    {
      throw std::runtime_error("invalid vertex count");
    }

    const std::size_t result = static_cast< std::size_t >(std::stoull(text));

    if (result < 3)
    {
      throw std::runtime_error("invalid vertex count");
    }

    return result;
  }

  std::string getPolygonArgument(const std::string& line, const std::string& command)
  {
    if (line.size() <= command.size() + 1
        || line.compare(0, command.size(), command) != 0
        || line[command.size()] != ' ')
    {
      throw std::runtime_error("missing polygon argument");
    }

    return line.substr(command.size() + 1);
  }

  void processArea(const std::vector< Polygon >& polygons, const std::vector< std::string >& words)
  {
    if (words.size() != 2)
    {
      throw std::runtime_error("invalid AREA command");
    }

    const std::string& argument = words[1];

    std::cout << std::fixed << std::setprecision(1);

    if (argument == "EVEN")
    {
      std::cout << sumAreaEven(polygons) << '\n';
    }
    else if (argument == "ODD")
    {
      std::cout << sumAreaOdd(polygons) << '\n';
    }
    else if (argument == "MEAN")
    {
      std::cout << meanArea(polygons) << '\n';
    }
    else
    {
      std::cout << sumAreaByVertexCount(polygons, parseVertexCount(argument)) << '\n';
    }
  }

  void processMax(const std::vector< Polygon >& polygons, const std::vector< std::string >& words)
  {
    if (words.size() != 2)
    {
      throw std::runtime_error("invalid MAX command");
    }

    if (words[1] == "AREA")
    {
      std::cout << std::fixed << std::setprecision(1) << maxArea(polygons) << '\n';
    }
    else if (words[1] == "VERTEXES")
    {
      std::cout << maxVertexCount(polygons) << '\n';
    }
    else
    {
      throw std::runtime_error("invalid MAX argument");
    }
  }

  void processMin(const std::vector< Polygon >& polygons, const std::vector< std::string >& words)
  {
    if (words.size() != 2)
    {
      throw std::runtime_error("invalid MIN command");
    }

    if (words[1] == "AREA")
    {
      std::cout << std::fixed << std::setprecision(1) << minArea(polygons) << '\n';
    }
    else if (words[1] == "VERTEXES")
    {
      std::cout << minVertexCount(polygons) << '\n';
    }
    else
    {
      throw std::runtime_error("invalid MIN argument");
    }
  }

  void processCount(const std::vector< Polygon >& polygons, const std::vector< std::string >& words)
  {
    if (words.size() != 2)
    {
      throw std::runtime_error("invalid COUNT command");
    }

    if (words[1] == "EVEN")
    {
      std::cout << countEven(polygons) << '\n';
    }
    else if (words[1] == "ODD")
    {
      std::cout << countOdd(polygons) << '\n';
    }
    else
    {
      std::cout << countByVertexCount(polygons, parseVertexCount(words[1])) << '\n';
    }
  }

  void processPerms(const std::vector< Polygon >& polygons, const std::string& line)
  {
    const Polygon target = parsePolygon(getPolygonArgument(line, "PERMS"));

    std::cout << countPermutations(polygons, target) << '\n';
  }

  void processRightShapes(const std::vector< Polygon >& polygons, const std::vector< std::string >& words)
  {
    if (words.size() != 1)
    {
      throw std::runtime_error("invalid RIGHTSHAPES command");
    }

    std::cout << countRightShapes(polygons) << '\n';
  }
}

void processCommands(const std::vector< Polygon >& polygons)
{
  std::string line;

  while (std::getline(std::cin, line))
  {
    if (line.empty())
    {
      continue;
    }

    try
    {
      const std::vector< std::string > words = splitWords(line);

      if (words.empty())
      {
        continue;
      }

      if (words[0] == "AREA")
      {
        processArea(polygons, words);
      }
      else if (words[0] == "MAX")
      {
        processMax(polygons, words);
      }
      else if (words[0] == "MIN")
      {
        processMin(polygons, words);
      }
      else if (words[0] == "COUNT")
      {
        processCount(polygons, words);
      }
      else if (words[0] == "PERMS")
      {
        processPerms(polygons, line);
      }
      else if (words[0] == "RIGHTSHAPES")
      {
        processRightShapes(polygons, words);
      }
      else
      {
        throw std::runtime_error("unknown command");
      }
    }
    catch (const std::exception&)
    {
      printInvalidCommand();
    }
  }
}
