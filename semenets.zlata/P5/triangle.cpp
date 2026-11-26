#include "triangle.hpp"
#include <algorithm>
#include <stdexcept>
#include <cmath>

namespace semenets {
  Triangle::Triangle(const point_t& a, const point_t& b, const point_t& c):
    a_(a),
    b_(b),
    c_(c)
  {
    if (getArea() == 0.0) {
      throw std::invalid_argument("Triangle sides must be positive");
    }
  }

  point_t Triangle::center() const
  {
    return {(a_.x + b_.x + c_.x) / 3, (a_.y + b_.y + c_.y) / 3};
  }

  double Triangle::getArea() const
  {
    const double abx = b_.x - a_.x;
    const double aby = b_.y - a_.y;
    const double acx = c_.x - a_.x;
    const double acy = c_.y - a_.y;

    return std::abs(abx * acy - aby * acx) / 2;
  }

  rectangle_t Triangle::getFrameRect() const
  {
    const double min_x = std::min({a_.x, b_.x, c_.x});
    const double max_x = std::max({a_.x, b_.x, c_.x});
    const double min_y = std::min({a_.y, b_.y, c_.y});
    const double max_y = std::max({a_.y, b_.y, c_.y});
    return {max_x - min_x, max_y - min_y, {(max_x + min_x) / 2, (max_y + min_y) / 2}};
  }

  void Triangle::move(const point_t& pos)
  {
    const point_t c = center();
    move(pos.x - c.x, pos.y - c.y);
  }

  void Triangle::move(double dx, double dy)
  {
    a_.x += dx;
    b_.x += dx;
    c_.x += dx;
    a_.y += dy;
    b_.y += dy;
    c_.y += dy;
  }

  void Triangle::scale(double k)
  {
    if (k <= 0.0) {
      throw std::invalid_argument("The coefficient of the function scale must be positive");
    }
    const point_t cent = center();
    a_ = {cent.x + (a_.x - cent.x) * k, cent.y + (a_.y - cent.y) * k};
    b_ = {cent.x + (b_.x - cent.x) * k, cent.y + (b_.y - cent.y) * k};
    c_ = {cent.x + (c_.x - cent.x) * k, cent.y + (c_.y - cent.y) * k};
  }
}
