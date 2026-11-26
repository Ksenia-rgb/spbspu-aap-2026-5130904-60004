#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "shape.hpp"

namespace pelipenko
{

  class Polygon : public Shape
  {
  public:
    Polygon(const point_t *vertices, int size);
    Polygon(const Polygon &other);
    Polygon(Polygon &&other) noexcept;
    ~Polygon() override;

    Polygon &operator=(const Polygon &other);
    Polygon &operator=(Polygon &&other) noexcept;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

    void swap(Polygon &other) noexcept;

  private:
    point_t centroid_;
    point_t *vertices_;
    int size_;
  };

}

#endif
