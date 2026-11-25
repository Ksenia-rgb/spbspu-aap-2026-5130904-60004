#include "Complexquad.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace romanov
{

  double triangleArea(const point_t& a, const point_t& b, const point_t& c)
  {
    return 0.5
        * std::abs((a.getX() - c.getX()) * (b.getY() - c.getY()) - (b.getX() - c.getX()) * (a.getY() - c.getY()));
  }

  Complexquad::Complexquad(point_t a, point_t b, point_t c, point_t d):
    pos_(0.0, 0.0)
  {
    pts_[0] = a;
    pts_[1] = b;
    pts_[2] = c;
    pts_[3] = d;

    double A1 = b.getY() - a.getY();
    double B1 = a.getX() - b.getX();
    double C1 = A1 * a.getX() + B1 * a.getY();

    double A2 = d.getY() - c.getY();
    double B2 = c.getX() - d.getX();
    double C2 = A2 * c.getX() + B2 * c.getY();

    double det = A1 * B2 - A2 * B1;
    if (std::abs(det) < 1e-9)
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
    double min_x = std::min({pts_[0].getX(), pts_[1].getX(), pts_[2].getX(), pts_[3].getX()});
    double min_y = std::min({pts_[0].getY(), pts_[1].getY(), pts_[2].getY(), pts_[3].getY()});
    double max_x = std::max({pts_[0].getX(), pts_[1].getX(), pts_[2].getX(), pts_[3].getX()});
    double max_y = std::max({pts_[0].getY(), pts_[1].getY(), pts_[2].getY(), pts_[3].getY()});
    return rectangle_t(max_x - min_x, max_y - min_y, point_t((min_x + max_x) / 2.0, (min_y + max_y) / 2.0));
  }

  void Complexquad::move(double dx, double dy)
  {
    for (int i = 0; i < 4; ++i)
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
    for (int i = 0; i < 4; ++i)
    {
      pts_[i].setX(pos_.getX() + (pts_[i].getX() - pos_.getX()) * k);
      pts_[i].setY(pos_.getY() + (pts_[i].getY() - pos_.getY()) * k);
    }
  }

}
