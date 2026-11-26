#include "polygon.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace {
constexpr int kMinVertices = 3;
constexpr double kHalf = 2.0;
}

namespace pelipenko {

Polygon::Polygon(const point_t *vertices, int size)
    : centroid_{0.0, 0.0}, vertices_(nullptr), size_(size) {
  if ((vertices == nullptr) || (size_ < kMinVertices)) {
    throw std::invalid_argument("Polygon: invalid vertices or size < 3");
  }

  vertices_ = new point_t[size_];
  for (int i = 0; i < size_; ++i) {
    vertices_[i] = vertices[i];
    centroid_.x += vertices[i].x;
    centroid_.y += vertices[i].y;
  }
  centroid_.x /= size_;
  centroid_.y /= size_;

  if (getArea() <= 0.0) {
    delete[] vertices_;
    throw std::invalid_argument("Polygon: area must be > 0");
  }
}

Polygon::Polygon(const Polygon &other)
    : centroid_(other.centroid_), vertices_(new point_t[other.size_]),
      size_(other.size_) {
  std::copy(other.vertices_, other.vertices_ + size_, vertices_);
}

Polygon::Polygon(Polygon &&other) noexcept
    : centroid_{0.0, 0.0}, vertices_(nullptr), size_(0) {
  swap(other);
}

Polygon::~Polygon() { delete[] vertices_; }

Polygon &Polygon::operator=(const Polygon &other) {
  if (this != &other) {
    Polygon temp(other);
    swap(temp);
  }
  return *this;
}

Polygon &Polygon::operator=(Polygon &&other) noexcept {
  if (this != &other) {
    swap(other);
  }
  return *this;
}

void Polygon::swap(Polygon &other) noexcept {
  std::swap(centroid_, other.centroid_);
  std::swap(vertices_, other.vertices_);
  std::swap(size_, other.size_);
}

double Polygon::getArea() const {
  double sum = 0.0;
  for (int i = 0; i < size_; ++i) {
    const int next = (i + 1) % size_;
    sum += (vertices_[i].x * vertices_[next].y) -
           (vertices_[next].x * vertices_[i].y);
  }
  return std::abs(sum) / kHalf;
}

rectangle_t Polygon::getFrameRect() const {
  double minX = vertices_[0].x;
  double maxX = vertices_[0].x;
  double minY = vertices_[0].y;
  double maxY = vertices_[0].y;

  for (int i = 1; i < size_; ++i) {
    minX = std::min(minX, vertices_[i].x);
    maxX = std::max(maxX, vertices_[i].x);
    minY = std::min(minY, vertices_[i].y);
    maxY = std::max(maxY, vertices_[i].y);
  }

  return {
      maxX - minX, maxY - minY, {(minX + maxX) / kHalf, (minY + maxY) / kHalf}};
}

void Polygon::move(const point_t &pos) {
  move(pos.x - centroid_.x, pos.y - centroid_.y);
}

void Polygon::move(double dx, double dy) {
  centroid_.x += dx;
  centroid_.y += dy;
  for (int i = 0; i < size_; ++i) {
    vertices_[i].x += dx;
    vertices_[i].y += dy;
  }
}

void Polygon::scale(double factor) {
  if (factor <= 0.0) {
    throw std::invalid_argument("Polygon: factor must be > 0");
  }
  for (int i = 0; i < size_; ++i) {
    vertices_[i].x = centroid_.x + ((vertices_[i].x - centroid_.x) * factor);
    vertices_[i].y = centroid_.y + ((vertices_[i].y - centroid_.y) * factor);
  }
}

}
