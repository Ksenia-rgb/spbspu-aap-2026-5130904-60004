#include "Rectangle.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>
namespace romanov {
bool isSamePoint(const point_t&a, const point_t& b)
{
  const double meas_err = 1e-9;
  return (std::abs(a.getX()- b.getX()) < meas_err) && (std::abs(a.getY() - b.getY()) < meas_err);
}
Rectangle::Rectangle(point_t a, point_t b, point_t c, point_t d) :
  width_(0.0),
  height_(0.0),
  pos_(0.0, 0.0)
  {
    point_t pts[4] = {a, b, c, d};
    for (int i = 0; i < 4; ++i)
    {
      for (int j = i + 1; j < 4; ++j)
      {
        if (isSamePoint(pts[i], pts[j]))
          {
            throw std::invalid_argument("Not an rectangle");
          }
      }
    }
    double minX = std::min({a.getX(), b.getX(), c.getX(), d.getX()});
    double minY = std::min({a.getY(), b.getY(), c.getY(), d.getY()});
    double maxX = std::max({a.getX(), b.getX(), c.getX(), d.getX()});
    double maxY = std::max({a.getY(), b.getY(), c.getY(), d.getY()});
    width_ = maxX- minX;
    height_ = maxY- minY;
    const double meas_err = 1e-9;
    if (width_ <= meas_err || height_ <= meas_err)
    {
      throw std::invalid_argument("Not an rectangle");
    }
    for (int i = 0; i < 4; ++i)
    {
      bool validX = (std::abs(pts[i].getX() - minX) < meas_err) || (std::abs(pts[i].getX() - maxX) < meas_err);
      bool validY = (std::abs(pts[i].getY() - minY) < meas_err) || (std::abs(pts[i].getY() - maxY) < meas_err);
      if (!validX || !validY)
      {
        throw std::invalid_argument("Sides must be parallel to coordinate axes");
      }
    }
  pos_.setX((minX + maxX) / 2.0);
  pos_.setY((minY + maxY) / 2.0);
  }

double Rectangle::getArea() const
{
  return width_ * height_;
}
rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t(width_, height_, pos_);
}
void Rectangle::move(double dx, double dy)
{
  pos_.setX(pos_.getX() + dx);
  pos_.setY(pos_.getY() + dy);
}
void Rectangle::move(const point_t& newCenter)
{
  double dx = (newCenter.getX() - pos_.getX());
  double dy = (newCenter.getY() - pos_.getY());
  move(dx, dy);
}
void Rectangle::scale(double k)
{
  if (k <= 0.0)
  {
    throw std::invalid_argument("coefficent cant be negative");
  }
  width_ *= k;
  height_ *= k;
}

}
