#include <iostream>
#include <stdexcept>

#include "polygon.hpp"
#include "rectangle.hpp"
#include "regular.hpp"

namespace
{
  void printShapes(const pelipenko::Shape *const *shapes, int count, const char *title)
  {
    std::cout << title << '\n';
    double total_area = 0.0;

    for (int i = 0; i < count; ++i)
    {
      const pelipenko::rectangle_t frame = shapes[i]->getFrameRect();
      const double area = shapes[i]->getArea();
      std::cout << "Area: " << area << " | Frame: " << frame.width << "x" << frame.height;
      std::cout << " at (" << frame.pos.x << ", " << frame.pos.y << ")\n";
      total_area += area;
    }

    std::cout << "Total Area: " << total_area << '\n';
  }

  void freeShapes(pelipenko::Shape **shapes, int count)
  {
    for (int i = 0; i < count; ++i)
    {
      delete shapes[i];
    }
  }
}

int main()
{
  constexpr int shapeCount = 3;
  constexpr double rectWidth = 4.0;
  constexpr double rectHeight = 2.0;
  constexpr int triangleSize = 3;
  constexpr int pentagonSides = 5;
  constexpr double pentagonSide = 2.0;

  pelipenko::Shape *shapes[shapeCount] = {nullptr, nullptr, nullptr};
  int index = 0;

  try
  {
    shapes[index++] = new pelipenko::Rectangle(rectWidth, rectHeight, {0.0, 0.0});

    const pelipenko::point_t triangle[triangleSize] = {{1.0, 1.0}, {5.0, 1.0}, {1.0, 4.0}};
    shapes[index++] = new pelipenko::Polygon(triangle, triangleSize);

    const pelipenko::point_t pentagonCenter = {-2.0, -2.0};
    shapes[index++] = new pelipenko::Regular(pentagonCenter, pentagonSides, pentagonSide);

    printShapes(shapes, shapeCount, "=== BEFORE ===");

    double cx = 0.0;
    double cy = 0.0;
    double factor = 0.0;

    if (!(std::cin >> cx >> cy >> factor))
    {
      std::cerr << "Error: invalid input\n";
      freeShapes(shapes, shapeCount);
      return 1;
    }

    if (factor <= 0.0)
    {
      std::cerr << "Error: factor must be > 0\n";
      freeShapes(shapes, shapeCount);
      return 1;
    }

    for (int i = 0; i < shapeCount; ++i)
    {
      shapes[i]->move(-cx, -cy);
      shapes[i]->scale(factor);
      shapes[i]->move(cx, cy);
    }

    printShapes(shapes, shapeCount, "=== AFTER ===");
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    freeShapes(shapes, shapeCount);
    return 2;
  }

  freeShapes(shapes, shapeCount);

  return 0;
}
