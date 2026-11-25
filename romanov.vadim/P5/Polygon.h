#pragma once
#include "shape.hpp"

namespace romanov
{

class Polygon : public Shape
{
private:
  point_t* vertices_;
  unsigned int size_;
  point_t pos_;

  void calculatePos();
public:
  Polygon(const point_t* vertices, unsigned int size);
  Polygon(const Polygon& other);
  Polygon& operator=(const Polygon& other);
  ~Polygon();

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t& newCenter) override;
  void scale(double k) override;
};

}
