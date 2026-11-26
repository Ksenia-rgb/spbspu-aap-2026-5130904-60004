#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"

namespace semenets {
  class Triangle: public Shape {
    point_t a_;
    point_t b_;
    point_t c_;
    point_t center() const;
  public:
    Triangle(const point_t& a, const point_t& b, const point_t& c);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  };
}
#endif
