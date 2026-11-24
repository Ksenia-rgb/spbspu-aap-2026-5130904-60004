#include "ellipse.hpp"
#include <cmath>
#include <stdexcept>

nozdracheva::Ellipse::Ellipse(double radiusX, double radiusY, const point_t& pos) :
    radiusX_(radiusX), radiusY_(radiusY), pos_(pos) {
    if (!std::isfinite(radiusX_) || !std::isfinite(radiusY_) ||
        !std::isfinite(pos_.x) || !std::isfinite(pos_.y) ||
        radiusX_ <= 0 || radiusY_ <= 0) {
        throw std::invalid_argument("Invalid ellipse");
    }
}

double nozdracheva::Ellipse::getArea() const {
    const double pi = std::acos(-1.0);
    return pi * radiusX_ * radiusY_;
}

nozdracheva::rectangle_t nozdracheva::Ellipse::getFrameRect() const {
    return { 2 * radiusX_, 2 * radiusY_, pos_ };
}

void nozdracheva::Ellipse::move(const point_t& point) {
    pos_ = point;
}

void nozdracheva::Ellipse::move(double dx, double dy) {
    pos_.x += dx;
    pos_.y += dy;
}

void nozdracheva::Ellipse::scale(double k) {
    if (!std::isfinite(k) || k <= 0) {
        throw std::invalid_argument("Invalid scale");
    }
    radiusX_ *= k;
    radiusY_ *= k;
}
