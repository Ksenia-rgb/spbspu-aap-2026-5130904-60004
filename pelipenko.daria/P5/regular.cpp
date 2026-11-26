#include "regular.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace
{
  constexpr int kMinSides = 3;
  constexpr double kHalf = 2.0;
  constexpr double kQuarter = 4.0;
  constexpr double kPi = 3.14159265358979323846;
}

namespace pelipenko
{

  Regular::Regular(const point_t &center, int sides, double side_length):
    center_(center),
    sides_(sides),
    side_length_(side_length)
  {
    if (sides_ < kMinSides)
    {
      throw std::invalid_argument("Regular: sides must be >= 3");
    }

    if (side_length_ <= 0.0)
    {
      throw std::invalid_argument("Regular: side length must be > 0");
    }
  }

  double Regular::getArea() const
  {
    return (sides_ * side_length_ * side_length_) / (kQuarter * std::tan(kPi / sides_));
  }

  rectangle_t Regular::getFrameRect() const
  {
    const double radius = side_length_ / (kHalf * std::sin(kPi / sides_));
    const double angle_step = (kHalf * kPi) / sides_;
    const double start_angle = (-kPi / kHalf) - (kPi / sides_);

    double min_x = center_.x + (radius * std::cos(start_angle));
    double max_x = min_x;
    double min_y = center_.y + (radius * std::sin(start_angle));
    double max_y = min_y;

    for (int i = 0; i < sides_; ++i)
    {
      const double angle = start_angle + (i * angle_step);
      const double vx = center_.x + (radius * std::cos(angle));
      const double vy = center_.y + (radius * std::sin(angle));

      min_x = std::min(min_x, vx);
      max_x = std::max(max_x, vx);
      min_y = std::min(min_y, vy);
      max_y = std::max(max_y, vy);
    }

    return {max_x - min_x, max_y - min_y, {(min_x + max_x) / kHalf, (min_y + max_y) / kHalf}};
  }

  void Regular::move(const point_t &pos)
  {
    center_ = pos;
  }

  void Regular::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Regular::scale(double factor)
  {
    if (factor <= 0.0)
    {
      throw std::invalid_argument("Regular: factor must be > 0");
    }

    side_length_ *= factor;
  }

}
