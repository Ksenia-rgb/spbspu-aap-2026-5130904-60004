#include "Polygon.hpp"
#include <cmath>
#include <stdexcept>
#include <limits>

namespace romanov
{
  const double kHalf = 0.5;
  const double kEpsilon = 1e-9;
  const double kSix = 6.0;
  const double kTwo = 2.0;
  Polygon::Polygon(const point_t* vertices, unsigned int size):
    size_(size),
    pos_(0.0, 0.0)
  {
    if (size < 3)
    {
      throw std::invalid_argument("Polygon must have at least 3 vertices");
    }
    vertices_ = new point_t[size];
    for (unsigned int i = 0; i < size; ++i)
    {
      vertices_[i] = vertices[i];
    }
    calculatePos();
  }

  Polygon::Polygon(const Polygon& other):
    size_(other.size_),
    pos_(other.pos_)
  {
    vertices_ = new point_t[size_];
    for (unsigned int i = 0; i < size_; ++i)
    {
      vertices_[i] = other.vertices_[i];
    }
  }

  Polygon& Polygon::operator=(const Polygon& other)
  {
    if (this != &other)
    {
      delete[] vertices_;
      size_ = other.size_;
      pos_ = other.pos_;
      vertices_ = new point_t[size_];
      for (unsigned int i = 0; i < size_; ++i)
      {
        vertices_[i] = other.vertices_[i];
      }
    }
    return *this;
  }

  Polygon::~Polygon()
  {
    delete[] vertices_;
  }

  void Polygon::calculatePos()
  {
    double signed_area = 0.0, cx = 0.0, cy = 0.0;
    for (unsigned int i = 0; i < size_; ++i)
    {
      const unsigned int j = (i + 1) % size_;
      const double cross = vertices_[i].getX() * vertices_[j].getY() - vertices_[j].getX() * vertices_[i].getY();
      signed_area += cross;
      cx += (vertices_[i].getX() + vertices_[j].getX()) * cross;
      cy += (vertices_[i].getY() + vertices_[j].getY()) * cross;
    }
    signed_area /= kTwo;
    if (std::abs(signed_area) < kEpsilon)
    {
      throw std::invalid_argument("Degenerate polygon");
    }
    pos_.setX(cx / (kSix * signed_area));
    pos_.setY(cy / (kSix * signed_area));
  }

  double Polygon::getArea() const
  {
    double area = 0.0;
    for (unsigned int i = 0; i < size_; ++i)
    {
      const unsigned int j = (i + 1) % size_;
      area += vertices_[i].getX() * vertices_[j].getY() - vertices_[j].getX() * vertices_[i].getY();
    }
    return std::abs(area) / kTwo;
  }

  rectangle_t Polygon::getFrameRect() const
  {
    double min_x = std::numeric_limits< double >::max();
    double min_y = std::numeric_limits< double >::max();
    double max_x = std::numeric_limits< double >::lowest();
    double max_y = std::numeric_limits< double >::lowest();

    for (unsigned int i = 0; i < size_; ++i)
    {
      if (vertices_[i].getX() < min_x)
      {
        min_x = vertices_[i].getX();
      }
      if (vertices_[i].getY() < min_y)
      {
        min_y = vertices_[i].getY();
      }
      if (vertices_[i].getX() > max_x)
      {
        max_x = vertices_[i].getX();
      }
      if (vertices_[i].getY() > max_y)
      {
        max_y = vertices_[i].getY();
      }
    }
    return rectangle_t(max_x - min_x, max_y - min_y, point_t((min_x + max_x) / kTwo, (min_y + max_y) / kTwo));
  }

  void Polygon::move(double dx, double dy)
  {
    for (unsigned int i = 0; i < size_; ++i)
    {
      vertices_[i].setX(vertices_[i].getX() + dx);
      vertices_[i].setY(vertices_[i].getY() + dy);
    }
    pos_.setX(pos_.getX() + dx);
    pos_.setY(pos_.getY() + dy);
  }

  void Polygon::move(const point_t& new_center)
  {
    move(new_center.getX() - pos_.getX(), new_center.getY() - pos_.getY());
  }

  void Polygon::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("coefficient must be positive");
    }
    for (unsigned int i = 0; i < size_; ++i)
    {
      vertices_[i].setX(pos_.getX() + (vertices_[i].getX() - pos_.getX()) * k);
      vertices_[i].setY(pos_.getY() + (vertices_[i].getY() - pos_.getY()) * k);
    }
  }

}
