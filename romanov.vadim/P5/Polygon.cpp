#include "Polygon.h"
#include <cmath>
#include <stdexcept>
#include <limits>

namespace romanov
{

Polygon::Polygon(const point_t* vertices, unsigned int size) :
  size_(size), pos_(0.0, 0.0)
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

Polygon::Polygon(const Polygon& other) :
  size_(other.size_), pos_(other.pos_)
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
  double signedArea = 0.0, cx = 0.0, cy = 0.0;
  for (unsigned int i = 0; i < size_; ++i)
  {
    unsigned int j = (i + 1) % size_;
    double cross = vertices_[i].getX() * vertices_[j].getY() -
                   vertices_[j].getX() * vertices_[i].getY();
    signedArea += cross;
    cx += (vertices_[i].getX() + vertices_[j].getX()) * cross;
    cy += (vertices_[i].getY() + vertices_[j].getY()) * cross;
  }
  signedArea /= 2.0;
  if (std::abs(signedArea) < 1e-9)
  {
    throw std::invalid_argument("Degenerate polygon");
  }
  pos_.setX(cx / (6.0 * signedArea));
  pos_.setY(cy / (6.0 * signedArea));
}

double Polygon::getArea() const
{
  double area = 0.0;
  for (unsigned int i = 0; i < size_; ++i)
  {
    unsigned int j = (i + 1) % size_;
    area += vertices_[i].getX() * vertices_[j].getY() -
            vertices_[j].getX() * vertices_[i].getY();
  }
  return std::abs(area) / 2.0;
}

rectangle_t Polygon::getFrameRect() const
{
  double minX = std::numeric_limits<double>::max();
  double minY = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::lowest();
  double maxY = std::numeric_limits<double>::lowest();

  for (unsigned int i = 0; i < size_; ++i)
  {
    if (vertices_[i].getX() < minX) minX = vertices_[i].getX();
    if (vertices_[i].getY() < minY) minY = vertices_[i].getY();
    if (vertices_[i].getX() > maxX) maxX = vertices_[i].getX();
    if (vertices_[i].getY() > maxY) maxY = vertices_[i].getY();
  }
  return rectangle_t(maxX - minX, maxY - minY,
                     point_t((minX + maxX) / 2.0, (minY + maxY) / 2.0));
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

void Polygon::move(const point_t& newCenter)
{
  move(newCenter.getX() - pos_.getX(), newCenter.getY() - pos_.getY());
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
