#include "rubber.hpp"
#include <cmath>
#include <stdexcept>

nozdracheva::Rubber::Rubber(double outerRadius, double innerRadius,
    const point_t& outerCenter, const point_t& innerCenter) :
    outerRadius_(outerRadius), innerRadius_(innerRadius),
    outerCenter_(outerCenter), innerCenter_(innerCenter) {
    double dx = outerCenter_.x - innerCenter_.x;
    double dy = outerCenter_.y - innerCenter_.y;
    double distance = std::hypot(dx, dy);

    if (!std::isfinite(outerRadius_) || !std::isfinite(innerRadius_) ||
        !std::isfinite(outerCenter_.x) || !std::isfinite(outerCenter_.y) ||
        !std::isfinite(innerCenter_.x) || !std::isfinite(innerCenter_.y) ||
        outerRadius_ <= 0 || innerRadius_ <= 0 || distance <= 0 ||
        distance + innerRadius_ >= outerRadius_) {
        throw std::invalid_argument("Invalid rubber");
    }
}

double nozdracheva::Rubber::getArea() const {
    const double pi = std::acos(-1.0);
    return pi * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
}

nozdracheva::rectangle_t nozdracheva::Rubber::getFrameRect() const {
    return { 2 * outerRadius_, 2 * outerRadius_, outerCenter_ };
}

void nozdracheva::Rubber::move(const point_t& point) {
    move(point.x - innerCenter_.x, point.y - innerCenter_.y);
}

void nozdracheva::Rubber::move(double dx, double dy) {
    outerCenter_.x += dx;
    outerCenter_.y += dy;
    innerCenter_.x += dx;
    innerCenter_.y += dy;
}

void nozdracheva::Rubber::scale(double k) {
    if (!std::isfinite(k) || k <= 0) {
        throw std::invalid_argument("Invalid scale");
    }
    outerCenter_.x = innerCenter_.x + (outerCenter_.x - innerCenter_.x) * k;
    outerCenter_.y = innerCenter_.y + (outerCenter_.y - innerCenter_.y) * k;
    outerRadius_ *= k;
    innerRadius_ *= k;
}