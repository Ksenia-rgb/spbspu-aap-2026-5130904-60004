#ifndef REGULAR_HPP
#define REGULAR_HPP

#include "shape.hpp"

namespace pelipenko
{

  class Regular: public Shape
  {
  public:
    Regular(const point_t &center, int sides, double side_length);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    point_t center_;
    int sides_;
    double side_length_;
  };

}

#endif
