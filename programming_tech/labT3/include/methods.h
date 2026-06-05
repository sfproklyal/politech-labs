#ifndef METHODS_H
#define METHODS_H

#include "polygon.h"

#include <cstddef>
#include <vector>

std::size_t getVertexCount(const Polygon& polygon);

std::size_t countEven(const std::vector< Polygon >& polygons);
std::size_t countOdd(const std::vector< Polygon >& polygons);
std::size_t countByVertexCount(const std::vector< Polygon >& polygons, std::size_t vertexCount);

std::size_t maxVertexCount(const std::vector< Polygon >& polygons);
std::size_t minVertexCount(const std::vector< Polygon >& polygons);
double maxArea(const std::vector< Polygon >& polygons);
double minArea(const std::vector< Polygon >& polygons);

double sumAreaEven(const std::vector< Polygon >& polygons);
double sumAreaOdd(const std::vector< Polygon >& polygons);
double sumAreaByVertexCount(const std::vector< Polygon >& polygons, std::size_t vertexCount);
double meanArea(const std::vector< Polygon >& polygons);

bool isPermutationOfPolygon(const Polygon& lhs, const Polygon& rhs);
std::size_t countPermutations(const std::vector< Polygon >& polygons, const Polygon& target);

bool hasRightAngle(const Polygon& polygon);
std::size_t countRightShapes(const std::vector< Polygon >& polygons);

#endif
