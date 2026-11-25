#include "Complexquad.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace romanov
{
  const double kHalf = 0.5;
  const double kEpsilon = 1e-9;
  const double kTwo = 2.0;
  const unsigned int kNumPoints = 4;
  double triangleArea(const point_t& a, const point_t& b, const point_t& c)
  {
    return kHalf
        * std::abs((a.getX() - c.getX()) * (b.getY() - c.getY()) - (b.getX() - c.getX()) * (a.getY() - c.getY()));
  }

  Complexquad::Complexquad(point_t a, point_t b, point_t c, point_t d):
    pos_(0.0, 0.0)
  {
    pts_[0] = a;
    pts_[1] = b;
    pts_[2] = c;
    pts_[3] = d;

    const double A1 = b.getY() - a.getY();
    const double B1 = a.getX() - b.getX();
    const double C1 = A1 * a.getX() + B1 * a.getY();

    const double A2 = d.getY() - c.getY();
    const double B2 = c.getX() - d.getX();
    const double C2 = A2 * c.getX() + B2 * c.getY();

    const double det = A1 * B2 - A2 * B1;
    if (std::abs(det) < kEpsilon)
    {
      throw std::invalid_argument("Lines are parallel, not a complexquad");
    }

    pos_.setX((B2 * C1 - B1 * C2) / det);
    pos_.setY((A1 * C2 - A2 * C1) / det);
  }

  double Complexquad::getArea() const
  {
    return triangleArea(pos_, pts_[0], pts_[3]) + triangleArea(pos_, pts_[1], pts_[2]);
  }

  rectangle_t Complexquad::getFrameRect() const
  {
    const double min_x = std::min({pts_[0].getX(), pts_[1].getX(), pts_[2].getX(), pts_[3].getX()});
    const double min_y = std::min({pts_[0].getY(), pts_[1].getY(), pts_[2].getY(), pts_[3].getY()});
    const double max_x = std::max({pts_[0].getX(), pts_[1].getX(), pts_[2].getX(), pts_[3].getX()});
    const double max_y = std::max({pts_[0].getY(), pts_[1].getY(), pts_[2].getY(), pts_[3].getY()});
    return rectangle_t(max_x - min_x, max_y - min_y, point_t((min_x + max_x) / kTwo, (min_y + max_y) / kTwo));
  }

  void Complexquad::move(double dx, double dy)
  {
    for (int i = 0; i < kNumPoints; ++i)
    {
      pts_[i].setX(pts_[i].getX() + dx);
      pts_[i].setY(pts_[i].getY() + dy);
    }
    pos_.setX(pos_.getX() + dx);
    pos_.setY(pos_.getY() + dy);
  }

  void Complexquad::move(const point_t& new_center)
  {
    move(new_center.getX() - pos_.getX(), new_center.getY() - pos_.getY());
  }

  void Complexquad::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("coefficient must be positive");
    }
    for (int i = 0; i < kNumPoints; ++i)
    {
      pts_[i].setX(pos_.getX() + (pts_[i].getX() - pos_.getX()) * k);
      pts_[i].setY(pos_.getY() + (pts_[i].getY() - pos_.getY()) * k);
    }
  }

}
