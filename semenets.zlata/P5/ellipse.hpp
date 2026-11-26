#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP
#include "shape.hpp"

namespace semenets {
  class Ellipse: public Shape {
    double rx_;
    double ry_;
    point_t center_;
  public:
    Ellipse(const point_t& center, double rx, double ry);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  };
}
#endif
