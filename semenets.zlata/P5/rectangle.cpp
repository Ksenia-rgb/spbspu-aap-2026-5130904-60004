#include "rectangle.hpp"
#include <stdexcept>

namespace semenets {
  Rectangle::Rectangle(double width, double height, const point_t& center):
    rect_(width, height, center)
  {
    if (height <= 0.0 || width <= 0.0) {
      throw std::invalid_argument("Rectangle width and height must be positive");
    }
  }
  double Rectangle::getArea() const
  {
    return rect_.height * rect_.width;
  }
  rectangle_t Rectangle::getFrameRect() const
  {
    return rect_;
  }
  void Rectangle::move(const point_t& pos)
  {
    rect_.pos = pos;
  }
  void Rectangle::move(double dx, double dy)
  {
    rect_.pos.x += dx;
    rect_.pos.y += dy;
  }
  void Rectangle::scale(double k)
  {
    if (k <= 0.0) {
      throw std::invalid_argument("The coefficient of the function scale must be positive");
    }
    rect_.height *= k;
    rect_.width *= k;
  }
}
