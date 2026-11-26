#include "ellipse.hpp"
#include <stdexcept>

namespace semenets {
  const double pi = 3.1415926535;
  Ellipse::Ellipse(const point_t& center, double rx, double ry):
    center_(center),
    rx_(rx),
    ry_(ry)
  {
    if (rx <= 0.0 || ry <= 0.0) {
      throw std::invalid_argument("Ellipse radii must be positive");
    }
  }
  double Ellipse::getArea() const
  {
    return pi * rx_ * ry_;
  }
  rectangle_t Ellipse::getFrameRect() const
  {
    return {2 * rx_, 2 * ry_, center_};
  }
  void Ellipse::move(const point_t& pos)
  {
    center_ = pos;
  }
  void Ellipse::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }
  void Ellipse::scale(double k)
  {
    if (k <= 0.0) {
      throw std::invalid_argument("The coefficient of the function scale must be positive");
    }
    rx_ *= k;
    ry_ *= k;
  }
}
