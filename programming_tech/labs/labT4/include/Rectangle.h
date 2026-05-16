#pragma once

#include <stdexcept>
#include <string>

#include "Shape.h"

class Rectangle : public Shape
{
private:
    Point leftBottom;
    Point rightTop;

public:
    Rectangle(Point leftBottom, Point rightTop)
        : leftBottom(leftBottom), rightTop(rightTop)
    {
        if (leftBottom.x >= rightTop.x || leftBottom.y >= rightTop.y) {
            throw std::invalid_argument("Invalid rectangle points");
        }
    }

    double getArea() const override {
        const double width = rightTop.x - leftBottom.x;
        const double height = rightTop.y - leftBottom.y;

        return width * height;
    }

    Point getCenter() const override {
        return {
            (leftBottom.x + rightTop.x) / 2,
            (leftBottom.y + rightTop.y) / 2
        };
    }

    void move(double dx, double dy) override {
        leftBottom.x += dx;
        leftBottom.y += dy;

        rightTop.x += dx;
        rightTop.y += dy;
    }

    void scale(double coefficient) override {
        if (coefficient <= 0) {
            throw std::invalid_argument("Scale coefficient must be greater than 0");
        }

        const Point center = getCenter();
        leftBottom.x = center.x + (leftBottom.x - center.x) * coefficient;
        leftBottom.y = center.y + (leftBottom.y - center.y) * coefficient;
        rightTop.x = center.x + (rightTop.x - center.x) * coefficient;
        rightTop.y = center.y + (rightTop.y - center.y) * coefficient;
    }

    std::string getName() const override {
        return "RECTANGLE";
    }
};
