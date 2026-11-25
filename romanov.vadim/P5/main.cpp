#include <iostream>
#include <limits>
#include "Rectangle.hpp"
#include "Complexquad.hpp"
#include "Polygon.hpp"

namespace romanov
{

  void scaleRelativeToPoint(Shape* shape, const point_t& p, double k);
  void printInfo(Shape** shapes, unsigned int count);
  void freeShapes(Shape** shapes, unsigned int count);
  const double kTwo = 2.0;
  const double kThree = 3.0;
  const double kFour = 4.0;
  const double kOnePointFive = 1.5;
  const double kZero = 0.0;
  const unsigned int kShapesCount = 3;
  const unsigned int kRectPoints = 4;
  const unsigned int kPolygonPoints = 5;

}
using namespace romanov;

int main()
{
  const unsigned int SHAPES_COUNT = kShapesCount;
  Shape** const shapes = new Shape*[SHAPES_COUNT];
  for (unsigned int i = 0; i < SHAPES_COUNT; ++i)
  {
    shapes[i] = nullptr;
  }
  try
  {
    const point_t r_pts[kRectPoints] = {point_t(kZero, kZero),
      point_t(kTwo, kZero),
      point_t(kTwo, kTwo),
      point_t(kZero, kTwo)};
    shapes[0] = new Rectangle(r_pts[0], r_pts[1], r_pts[2], r_pts[kShapesCount]);

    shapes[1] = new Complexquad(point_t(kZero, kZero),
                                point_t(kFour, kFour),
                                point_t(kFour, kZero),
                                point_t(kZero, kFour));

    point_t p_pts[kPolygonPoints] = {point_t(kZero, kZero),
      point_t(kThree, kZero),
      point_t(kThree, kThree),
      point_t(kOnePointFive, kFour),
      point_t(kZero, kThree)};
    shapes[2] = new Polygon(p_pts, kPolygonPoints);

    std::cout << "--- BEFORE SCALING ---\n";
    printInfo(shapes, SHAPES_COUNT);

    double px = kZero;
    double py = kZero;
    double k = kZero;
    std::cout << "Enter scale point (x y) and coefficient (k): ";
    if (!(std::cin >> px >> py >> k))
    {
      std::cerr << "Error: invalid input format\n";
      freeShapes(shapes, SHAPES_COUNT);
      return 1;
    }

    if (k <= kZero)
    {
      std::cerr << "Error: coefficient must be positive\n";
      freeShapes(shapes, SHAPES_COUNT);
      return 1;
    }

    const point_t scale_point(px, py);
    for (unsigned int i = 0; i < SHAPES_COUNT; ++i)
    {
      scaleRelativeToPoint(shapes[i], scale_point, k);
    }

    std::cout << "--- AFTER SCALING ---\n";
    printInfo(shapes, SHAPES_COUNT);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    freeShapes(shapes, SHAPES_COUNT);
    return 1;
  }

  freeShapes(shapes, SHAPES_COUNT);
  return 0;
}

namespace romanov
{

  void scaleRelativeToPoint(Shape* shape, const point_t& p, double k)
  {
    const point_t c = shape->getFrameRect().getPos();
    shape->move(p);
    shape->scale(k);
    const point_t new_pos(p.getX() + k * (c.getX() - p.getX()), p.getY() + k * (c.getY() - p.getY()));
    shape->move(new_pos);
  }

  void printInfo(Shape** shapes, unsigned int count)
  {
    double total_area = kZero;
    double min_x = std::numeric_limits< double >::max();
    double min_y = std::numeric_limits< double >::max();
    double max_x = std::numeric_limits< double >::lowest();
    double max_y = std::numeric_limits< double >::lowest();

    for (unsigned int i = 0; i < count; ++i)
    {
      const double area = shapes[i]->getArea();
      total_area += area;
      std::cout << "Shape " << i + 1 << " area: " << area << "\n";

      const rectangle_t rect = shapes[i]->getFrameRect();
      std::cout << "Shape " << i + 1 << " frame rect: width=" << rect.getWidth() << ", height=" << rect.getHeight()
                << ", pos=(" << rect.getPos().getX() << ", " << rect.getPos().getY() << ")\n";

      const double r_min_x = rect.getPos().getX() - rect.getWidth() / kTwo;
      const double r_min_y = rect.getPos().getY() - rect.getHeight() / kTwo;
      const double r_max_x = rect.getPos().getX() + rect.getWidth() / kTwo;
      const double r_max_y = rect.getPos().getY() + rect.getHeight() / kTwo;

      if (r_min_x < min_x)
      {
        min_x = r_min_x;
      }
      if (r_min_y < min_y)
      {
        min_y = r_min_y;
      }
      if (r_max_x > max_x)
      {
        max_x = r_max_x;
      }
      if (r_max_y > max_y)
      {
        max_y = r_max_y;
      }
    }

    std::cout << "Total area: " << total_area << "\n";
    std::cout << "Global frame rect: width=" << (max_x - min_x) << ", height=" << (max_y - min_y) << ", pos=("
              << ((min_x + max_x) / kTwo) << ", " << ((min_y + max_y) / kTwo) << ")\n\n";
  }

  void freeShapes(Shape** shapes, unsigned int count)
  {
    for (unsigned int i = 0; i < count; ++i)
    {
      delete shapes[i];
    }
    delete[] shapes;
  }

}
