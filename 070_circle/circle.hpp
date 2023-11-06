#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(const Point & center, double radius);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

#endif
