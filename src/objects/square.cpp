#include "square.hpp"
#include "common.hpp"
#include "rectangle.hpp"

namespace pet {

Square Square::fromCorner(const Point2 &top_left, unsigned int size, Point2 scale, double thick) {
  Point2 p2 = Point2(top_left.x()+size, top_left.y()+size);
  return Square(top_left, p2, scale, thick);
}

Square Square::fromCenter(const Point2 &center, unsigned int size, Point2 scale, double thick) {
  Point2 p1 = Point2(center.x()-size/2, center.y()-size/2);
  Point2 p2 = Point2(center.x()+size/2, center.y()+size/2);
  return Square(p1, p2, scale, thick);
}

} // namespace pet
