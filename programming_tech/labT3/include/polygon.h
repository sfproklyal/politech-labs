#ifndef POLYGON_H
#define POLYGON_H

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>

struct Point
{
  int x;
  int y;
};

struct Polygon
{
  std::vector< Point > points;
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator<(const Point& lhs, const Point& rhs);
bool operator==(const Polygon& lhs, const Polygon& rhs);

double getArea(const Polygon& polygon);
Polygon parsePolygon(const std::string& line);
std::vector< Polygon > readPolygonsFromFile(const std::string& filename);

#endif
