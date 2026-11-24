#pragma once
#include "shape.hpp"

namespace nozdracheva {
    class Rubber : public Shape {
    private:
        double outerRadius_;
        double innerRadius_;
        point_t outerCenter_;
        point_t innerCenter_;

    public:
        Rubber(double outerRadius, double innerRadius, const point_t& outerCenter,
            const point_t& innerCenter);
        double getArea() const override;
        rectangle_t getFrameRect() const override;
        void move(const point_t& point) override;
        void move(double dx, double dy) override;
        void scale(double k) override;
    };
}