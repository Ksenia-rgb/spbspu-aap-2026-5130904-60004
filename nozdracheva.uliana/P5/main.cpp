#include "rectangle.hpp"
#include "rubber.hpp"
#include "ellipse.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

void printRect(const nozdracheva::rectangle_t& rect) {
    std::cout << "center: (" << rect.pos.x << ", " << rect.pos.y << ")"
        << ", width: " << rect.width << ", height: " << rect.height << "\n";
}

void printShapes(nozdracheva::Shape* shapes[], int count) {
    double totalArea = 0;
    nozdracheva::rectangle_t rect = shapes[0]->getFrameRect();
    double left = rect.pos.x - rect.width / 2;
    double right = rect.pos.x + rect.width / 2;
    double bottom = rect.pos.y - rect.height / 2;
    double top = rect.pos.y + rect.height / 2;

    for (int i = 0; i < count; ++i) {
        std::cout << "Shape " << i + 1 << ":\n";
        double area = shapes[i]->getArea();
        std::cout << "Area: " << area << "\n";
        rect = shapes[i]->getFrameRect();
        std::cout << "Frame: ";
        printRect(rect);
        totalArea += area;

        double x1 = rect.pos.x - rect.width / 2;
        double x2 = rect.pos.x + rect.width / 2;
        double y1 = rect.pos.y - rect.height / 2;
        double y2 = rect.pos.y + rect.height / 2;

        if (x1 < left) {
            left = x1;
        }
        if (x2 > right) {
            right = x2;
        }
        if (y1 < bottom) {
            bottom = y1;
        }
        if (y2 > top) {
            top = y2;
        }
    }

    if (!std::isfinite(totalArea) || totalArea <= 0 ||
        !std::isfinite(right - left) || !std::isfinite(top - bottom)) {
        throw std::invalid_argument("Invalid scaling result");
    }

    std::cout << "Total area: " << totalArea << "\n";
    std::cout << "Total frame: ";
    printRect({ right - left, top - bottom,
        {(left + right) / 2, (bottom + top) / 2} });
}

void scaleShapes(nozdracheva::Shape* shapes[], int count,
    const nozdracheva::point_t& point, double k) {
    for (int i = 0; i < count; ++i) {
        nozdracheva::rectangle_t before = shapes[i]->getFrameRect();
        shapes[i]->move(point);
        nozdracheva::rectangle_t atPoint = shapes[i]->getFrameRect();
        double centerX = before.pos.x - (atPoint.pos.x - point.x);
        double centerY = before.pos.y - (atPoint.pos.y - point.y);
        shapes[i]->move({ centerX, centerY });
        shapes[i]->scale(k);
        shapes[i]->move((centerX - point.x) * (k - 1),
            (centerY - point.y) * (k - 1));

        nozdracheva::rectangle_t after = shapes[i]->getFrameRect();
        double area = shapes[i]->getArea();
        if (!std::isfinite(area) || area <= 0 ||
            !std::isfinite(after.width) || !std::isfinite(after.height) ||
            !std::isfinite(after.pos.x) || !std::isfinite(after.pos.y) ||
            after.width <= 0 || after.height <= 0) {
            throw std::invalid_argument("Invalid scaling result");
        }
    }
}

int main() {
    try {
        nozdracheva::Rectangle rectangle(4.0, 2.0, { 1.0, 1.0 });
        nozdracheva::Rubber rubber(5.0, 2.0, { 8.0, 3.0 }, { 9.0, 3.0 });
        nozdracheva::Ellipse ellipse(3.0, 1.5, { -4.0, 2.0 });
        nozdracheva::Shape* shapes[] = { &rectangle, &rubber, &ellipse };
        const int count = 3;

        std::cout << "Before scaling:\n";
        printShapes(shapes, count);

        nozdracheva::point_t point = {};
        double k = 0;
        std::cout << "Enter x, y and scale: ";
        if (!(std::cin >> point.x >> point.y >> k) ||
            !std::isfinite(point.x) || !std::isfinite(point.y) ||
            !std::isfinite(k) || k <= 0) {
            std::cerr << "Invalid scaling parameters\n";
            return 1;
        }

        scaleShapes(shapes, count, point, k);
        std::cout << "After scaling:\n";
        printShapes(shapes, count);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}