#include "regular.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace {
constexpr int kMinSides = 3;
constexpr double kHalf = 2.0;
constexpr double kQuarter = 4.0;
constexpr double kPi = 3.14159265358979323846;
}

namespace pelipenko {

Regular::Regular(const point_t &center, int sides, double sideLength)
    : center_(center), sides_(sides), sideLength_(sideLength) {
  if (sides_ < kMinSides) {
    throw std::invalid_argument("Regular: sides must be >= 3");
  }
  if (sideLength_ <= 0.0) {
    throw std::invalid_argument("Regular: side length must be > 0");
  }
}

double Regular::getArea() const {
  return (sides_ * sideLength_ * sideLength_) /
         (kQuarter * std::tan(kPi / sides_));
}

rectangle_t Regular::getFrameRect() const {
  const double radius = sideLength_ / (kHalf * std::sin(kPi / sides_));
  const double angleStep = (kHalf * kPi) / sides_;
  const double startAngle = (-kPi / kHalf) - (kPi / sides_);

  double minX = center_.x + (radius * std::cos(startAngle));
  double maxX = minX;
  double minY = center_.y + (radius * std::sin(startAngle));
  double maxY = minY;

  for (int i = 0; i < sides_; ++i) {
    const double angle = startAngle + (i * angleStep);
    const double vx = center_.x + (radius * std::cos(angle));
    const double vy = center_.y + (radius * std::sin(angle));
    minX = std::min(minX, vx);
    maxX = std::max(maxX, vx);
    minY = std::min(minY, vy);
    maxY = std::max(maxY, vy);
  }

  return {
      maxX - minX, maxY - minY, {(minX + maxX) / kHalf, (minY + maxY) / kHalf}};
}

void Regular::move(const point_t &pos) { center_ = pos; }

void Regular::move(double dx, double dy) {
  center_.x += dx;
  center_.y += dy;
}

void Regular::scale(double factor) {
  if (factor <= 0.0) {
    throw std::invalid_argument("Regular: factor must be > 0");
  }
  sideLength_ *= factor;
}

}
