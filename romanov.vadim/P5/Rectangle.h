#pragma once
#include "shape.hpp"
namespace romanov {
class Rectangle: public Shape
{
private:
  double width_, height_;
  point_t pos_;
public:
  Rectangle(point_t a, point_t b, point_t c, point_t d);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t& newCenter) override;
  void scale(double k) override;
};

}
