#include "point.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <cmath>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double dis = sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
  return dis;
}
