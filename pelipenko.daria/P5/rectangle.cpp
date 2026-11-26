#include "rectangle.hpp"

#include <stdexcept>

namespace pelipenko
{

  Rectangle::Rectangle(double width, double height, const point_t &center)
      : width_(width), height_(height), center_(center)
  {
    if ((width_ <= 0.0) || (height_ <= 0.0))
    {
      throw std::invalid_argument("Rectangle: width and height must be > 0");
    }
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return {width_, height_, center_};
  }

  void Rectangle::move(const point_t &pos)
  {
    center_ = pos;
  }

  void Rectangle::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Rectangle::scale(double factor)
  {
    if (factor <= 0.0)
    {
      throw std::invalid_argument("Rectangle: factor must be > 0");
    }
    width_ *= factor;
    height_ *= factor;
  }

} // namespace pelipenko
