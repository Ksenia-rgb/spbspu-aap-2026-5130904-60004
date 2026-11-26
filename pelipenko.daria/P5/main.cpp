#include "polygon.hpp"
#include "rectangle.hpp"
#include "regular.hpp"
#include <iostream>
#include <stdexcept>

namespace {
void printShapes(const pelipenko::Shape *const *shapes, int count,
                 const char *title) {
  std::cout << title << '\n';
  double total_area = 0.0;
  for (int i = 0; i < count; ++i) {
    const pelipenko::rectangle_t frame = shapes[i]->getFrameRect();
    const double area = shapes[i]->getArea();
    std::cout << "Area: " << area << " | Frame: " << frame.width << "x"
              << frame.height << " at (" << frame.pos.x << ", " << frame.pos.y
              << ")\n";
    total_area += area;
  }
  std::cout << "Total Area: " << total_area << '\n';
}

void freeShapes(pelipenko::Shape **shapes, int count) {
  for (int i = 0; i < count; ++i) {
    delete shapes[i];
  }
}

int main() {
  constexpr int shape_count = 3;
  constexpr double rect_width = 4.0;
  constexpr double rect_height = 2.0;
  constexpr int triangle_size = 3;
  constexpr int pentagon_sides = 5;
  constexpr double pentagon_side = 2.0;

  pelipenko::Shape *shapes[shape_count] = {nullptr, nullptr, nullptr};
  int index = 0;

  try {
    shapes[index++] =
        new pelipenko::Rectangle(rect_width, rect_height, {0.0, 0.0});

    const pelipenko::point_t triangle[triangle_size] = {
        {1.0, 1.0}, {5.0, 1.0}, {1.0, 4.0}};
    shapes[index++] = new pelipenko::Polygon(triangle, triangle_size);

    const pelipenko::point_t pentagonCenter = {-2.0, -2.0};
    shapes[index++] =
        new pelipenko::Regular(pentagonCenter, pentagon_sides, pentagon_side);

    printShapes(shapes, shape_count, "=== BEFORE ===");

    double cx = 0.0;
    double cy = 0.0;
    double factor = 0.0;

    if (!(std::cin >> cx >> cy >> factor)) {
      std::cerr << "Error: invalid input\n";
      freeShapes(shapes, shape_count);
      return 1;
    }

    if (factor <= 0.0) {
      std::cerr << "Error: factor must be > 0\n";
      freeShapes(shapes, shape_count);
      return 1;
    }

    for (int i = 0; i < shape_count; ++i) {
      shapes[i]->move(-cx, -cy);
      shapes[i]->scale(factor);
      shapes[i]->move(cx, cy);
    }

    printShapes(shapes, shape_count, "=== AFTER ===");

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    freeShapes(shapes, shape_count);
    return 2;
  }

  freeShapes(shapes, shape_count);

  std::cout << "Press Enter to exit...\n";
  std::cin.get();
  std::cin.get();

  return 0;
}
