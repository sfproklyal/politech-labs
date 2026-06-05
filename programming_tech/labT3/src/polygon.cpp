#include "polygon.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>
#include <numeric>
#include <regex>
#include <sstream>
#include <stdexcept>

bool operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator<(const Point& lhs, const Point& rhs)
{
  return (lhs.x == rhs.x) ? (lhs.y < rhs.y) : (lhs.x < rhs.x);
}

bool operator==(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points.size() == rhs.points.size()
      && std::equal(lhs.points.cbegin(), lhs.points.cend(), rhs.points.cbegin());
}

namespace
{
  std::size_t parseUnsigned(const std::string& text)
  {
    if (text.empty() || !std::all_of(text.cbegin(), text.cend(), ::isdigit))
    {
      throw std::runtime_error("invalid unsigned number");
    }
    return static_cast< std::size_t >(std::stoull(text));
  }

  Point matchToPoint(const std::smatch& match)
  {
    return Point{ std::stoi(match[1].str()), std::stoi(match[2].str()) };
  }
}

double getArea(const Polygon& polygon)
{
  const std::size_t size = polygon.points.size();
  if (size < 3)
  {
    return 0.0;
  }

  std::vector< std::size_t > indexes(size);
  std::iota(indexes.begin(), indexes.end(), 0);

  const long long doubleArea = std::accumulate(
    indexes.cbegin(),
    indexes.cend(),
    0LL,
    [&polygon, size](long long sum, std::size_t index)
    {
      const Point& current = polygon.points[index];
      const Point& next = polygon.points[(index + 1) % size];

      return sum + static_cast< long long >(current.x) * next.y
                 - static_cast< long long >(next.x) * current.y;
    }
  );

  return std::abs(static_cast< double >(doubleArea)) / 2.0;
}

Polygon parsePolygon(const std::string& line)
{
  static const std::regex fullPattern(
    R"(^([0-9]+)( \(-?[0-9]+;-?[0-9]+\))+$)"
  );
  static const std::regex pointPattern(R"(\((-?[0-9]+);(-?[0-9]+)\))");

  std::smatch fullMatch;
  if (!std::regex_match(line, fullMatch, fullPattern))
  {
    throw std::runtime_error("invalid polygon format");
  }

  const std::size_t declaredSize = parseUnsigned(fullMatch[1].str());
  if (declaredSize < 3)
  {
    throw std::runtime_error("polygon must have at least 3 points");
  }

  std::vector< Point > points;
  std::transform(
    std::sregex_iterator(line.cbegin(), line.cend(), pointPattern),
    std::sregex_iterator(),
    std::back_inserter(points),
    matchToPoint
  );

  if (points.size() != declaredSize)
  {
    throw std::runtime_error("wrong number of points");
  }

  return Polygon{ points };
}

std::vector< Polygon > readPolygonsFromFile(const std::string& filename)
{
  std::ifstream input(filename);
  if (!input.is_open())
  {
    throw std::runtime_error("cannot open file");
  }

  std::vector< Polygon > polygons;
  std::string line;

  while (std::getline(input, line))
  {
    if (line.empty())
    {
      continue;
    }

    try
    {
      polygons.push_back(parsePolygon(line));
    }
    catch (const std::exception&)
    {
      // Некорректные строки из файла должны игнорироваться.
    }
  }

  return polygons;
}
