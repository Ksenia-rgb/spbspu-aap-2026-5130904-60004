#pragma once
#include "base-types.hpp"
namespace romanov {
class Shape
{
public:
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void move(const point_t& newCenter) = 0;
  virtual void scale(double k) = 0;
  virtual ~Shape() = default;
};

}
