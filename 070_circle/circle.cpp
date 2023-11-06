#include "circle.hpp"

#include <cmath>

Circle::Circle(const Point & center, double radius) : center(center), radius(radius) {
  // Use initializer list to set the center and the const radius
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);  // Use the Point class's move method to update the center
}

double Circle::intersectionArea(const Circle & otherCircle) {
  // Calculate the area of the intersection between this circle and otherCircle

  // Calculate the distance between the centers of the two circles
  double distance = center.distanceFrom(otherCircle.center);

  // If the distance is greater than the sum of the radii, there is no intersection
  if (distance >= radius + otherCircle.radius) {
    return 0.0;
  }

  // If one circle is completely within the other, the area of the smaller circle is the intersection
  if (distance + radius <= otherCircle.radius) {
    return M_PI * radius * radius;
  }

  if (distance + otherCircle.radius <= radius) {
    return M_PI * otherCircle.radius * otherCircle.radius;
  }

  // Calculate the area of the intersection using trigonometry
  double angle1 = 2 * acos((radius * radius + distance * distance -
                            otherCircle.radius * otherCircle.radius) /
                           (2 * radius * distance));
  double angle2 = 2 * acos((otherCircle.radius * otherCircle.radius +
                            distance * distance - radius * radius) /
                           (2 * otherCircle.radius * distance));

  double area1 = 0.5 * radius * radius * (angle1 - sin(angle1));
  double area2 = 0.5 * otherCircle.radius * otherCircle.radius * (angle2 - sin(angle2));
  return area1 + area2;
}
