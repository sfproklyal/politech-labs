#include <iomanip>
#include <iostream>

#include "Rectangle.h"

void printShape(const Shape& shape) {
    const Point center = shape.getCenter();

    std::cout << '[' << shape.getName() << ", ("
              << std::fixed << std::setprecision(2)
              << center.x << ", " << center.y << "), "
              << shape.getArea() << "]\n";
}

int main() {
    Rectangle rectangle({0, 0}, {3, 2});

    printShape(rectangle);
    rectangle.scale(2);
    printShape(rectangle);
}
