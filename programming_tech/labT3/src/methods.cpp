#include "methods.h"

#include <algorithm>
#include <numeric>
#include <stdexcept>

namespace
{
  bool hasVertexCount(const Polygon& polygon, std::size_t vertexCount)
  {
    return getVertexCount(polygon) == vertexCount;
  }

  bool hasEvenVertexCount(const Polygon& polygon)
  {
    return getVertexCount(polygon) % 2 == 0;
  }

  bool hasOddVertexCount(const Polygon& polygon)
  {
    return getVertexCount(polygon) % 2 != 0;
  }

  void requireNonEmpty(const std::vector< Polygon >& polygons)
  {
    if (polygons.empty())
    {
      throw std::runtime_error("empty polygon sequence");
    }
  }

  long long dotProduct(const Point& lhs, const Point& center, const Point& rhs)
  {
    const long long firstX = lhs.x - center.x;
    const long long firstY = lhs.y - center.y;
    const long long secondX = rhs.x - center.x;
    const long long secondY = rhs.y - center.y;

    return firstX * secondX + firstY * secondY;
  }
}

std::size_t getVertexCount(const Polygon& polygon)
{
  return polygon.points.size();
}

std::size_t countEven(const std::vector< Polygon >& polygons)
{
  return static_cast< std::size_t >(
    std::count_if(polygons.cbegin(), polygons.cend(), hasEvenVertexCount)
  );
}

std::size_t countOdd(const std::vector< Polygon >& polygons)
{
  return static_cast< std::size_t >(
    std::count_if(polygons.cbegin(), polygons.cend(), hasOddVertexCount)
  );
}

std::size_t countByVertexCount(const std::vector< Polygon >& polygons, std::size_t vertexCount)
{
  return static_cast< std::size_t >(
    std::count_if(
      polygons.cbegin(),
      polygons.cend(),
      [vertexCount](const Polygon& polygon)
      {
        return hasVertexCount(polygon, vertexCount);
      }
    )
  );
}

std::size_t maxVertexCount(const std::vector< Polygon >& polygons)
{
  requireNonEmpty(polygons);

  return getVertexCount(
    *std::max_element(
      polygons.cbegin(),
      polygons.cend(),
      [](const Polygon& lhs, const Polygon& rhs)
      {
        return getVertexCount(lhs) < getVertexCount(rhs);
      }
    )
  );
}

std::size_t minVertexCount(const std::vector< Polygon >& polygons)
{
  requireNonEmpty(polygons);

  return getVertexCount(
    *std::min_element(
      polygons.cbegin(),
      polygons.cend(),
      [](const Polygon& lhs, const Polygon& rhs)
      {
        return getVertexCount(lhs) < getVertexCount(rhs);
      }
    )
  );
}

double maxArea(const std::vector< Polygon >& polygons)
{
  requireNonEmpty(polygons);

  return getArea(
    *std::max_element(
      polygons.cbegin(),
      polygons.cend(),
      [](const Polygon& lhs, const Polygon& rhs)
      {
        return getArea(lhs) < getArea(rhs);
      }
    )
  );
}

double minArea(const std::vector< Polygon >& polygons)
{
  requireNonEmpty(polygons);

  return getArea(
    *std::min_element(
      polygons.cbegin(),
      polygons.cend(),
      [](const Polygon& lhs, const Polygon& rhs)
      {
        return getArea(lhs) < getArea(rhs);
      }
    )
  );
}

double sumAreaEven(const std::vector< Polygon >& polygons)
{
  return std::accumulate(
    polygons.cbegin(),
    polygons.cend(),
    0.0,
    [](double sum, const Polygon& polygon)
    {
      return hasEvenVertexCount(polygon) ? sum + getArea(polygon) : sum;
    }
  );
}

double sumAreaOdd(const std::vector< Polygon >& polygons)
{
  return std::accumulate(
    polygons.cbegin(),
    polygons.cend(),
    0.0,
    [](double sum, const Polygon& polygon)
    {
      return hasOddVertexCount(polygon) ? sum + getArea(polygon) : sum;
    }
  );
}

double sumAreaByVertexCount(const std::vector< Polygon >& polygons, std::size_t vertexCount)
{
  return std::accumulate(
    polygons.cbegin(),
    polygons.cend(),
    0.0,
    [vertexCount](double sum, const Polygon& polygon)
    {
      return hasVertexCount(polygon, vertexCount) ? sum + getArea(polygon) : sum;
    }
  );
}

double meanArea(const std::vector< Polygon >& polygons)
{
  requireNonEmpty(polygons);

  const double areaSum = std::accumulate(
    polygons.cbegin(),
    polygons.cend(),
    0.0,
    [](double sum, const Polygon& polygon)
    {
      return sum + getArea(polygon);
    }
  );

  return areaSum / polygons.size();
}

bool isPermutationOfPolygon(const Polygon& lhs, const Polygon& rhs)
{
  if (lhs.points.size() != rhs.points.size())
  {
    return false;
  }

  std::vector< Point > lhsPoints = lhs.points;
  std::vector< Point > rhsPoints = rhs.points;
  std::sort(lhsPoints.begin(), lhsPoints.end());
  std::sort(rhsPoints.begin(), rhsPoints.end());

  return lhsPoints == rhsPoints;
}

std::size_t countPermutations(const std::vector< Polygon >& polygons, const Polygon& target)
{
  return static_cast< std::size_t >(
    std::count_if(
      polygons.cbegin(),
      polygons.cend(),
      [&target](const Polygon& polygon)
      {
        return isPermutationOfPolygon(polygon, target);
      }
    )
  );
}

bool hasRightAngle(const Polygon& polygon)
{
  const std::size_t size = polygon.points.size();
  if (size < 3)
  {
    return false;
  }

  std::vector< std::size_t > indexes(size);
  std::iota(indexes.begin(), indexes.end(), 0);

  return std::any_of(
    indexes.cbegin(),
    indexes.cend(),
    [&polygon, size](std::size_t index)
    {
      const Point& previous = polygon.points[(index + size - 1) % size];
      const Point& current = polygon.points[index];
      const Point& next = polygon.points[(index + 1) % size];

      return dotProduct(previous, current, next) == 0;
    }
  );
}

std::size_t countRightShapes(const std::vector< Polygon >& polygons)
{
  return static_cast< std::size_t >(
    std::count_if(polygons.cbegin(), polygons.cend(), hasRightAngle)
  );
}
