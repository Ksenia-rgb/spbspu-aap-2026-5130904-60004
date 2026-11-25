#pragma once
#include "shape.hpp"

namespace romanov {

class Complexquad : public Shape
{
private:
  point_t pts_[4];
  point_t pos_;
public:
  Complexquad(point_t a, point_t b, point_t c, point_t d);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t& newCenter) override;
  void scale(double k) override;
};

}
