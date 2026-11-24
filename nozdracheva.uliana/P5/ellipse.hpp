#pragma once
#include "shape.hpp"

namespace nozdracheva {
    class Ellipse : public Shape {
    private:
        double radiusX_;
        double radiusY_;
        point_t pos_;

    public:
        Ellipse(double radiusX, double radiusY, const point_t& pos);
        double getArea() const override;
        rectangle_t getFrameRect() const override;
        void move(const point_t& point) override;
        void move(double dx, double dy) override;
        void scale(double k) override;
    };
}