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
  const double k2 = 2.0;
  const double k3 = 3.0;
  const double k4 = 4.0;
  const double k15 = 1.5;
  const double k0 = 0.0;
  const unsigned int kShpsCnt = 3;
  const unsigned int kRctPints = 4;
  const unsigned int kPlgnPnts = 5;

}
using namespace romanov;

int main()
{
  const unsigned int SHAPES_COUNT = kShpsCnt;
  Shape** const shapes = new Shape*[SHAPES_COUNT];
  for (unsigned int i = 0; i < SHAPES_COUNT; ++i)
  {
    shapes[i] = nullptr;
  }
  try
  {
    const point_t r_pts[kRctPints] = {point_t(k0, k0), point_t(k2, k0), point_t(k2, k2), point_t(k0, k2)};
    shapes[0] = new Rectangle(r_pts[0], r_pts[1], r_pts[2], r_pts[kShpsCnt]);

    shapes[1] = new Complexquad(point_t(k0, k0), point_t(k4, k4), point_t(k4, k0), point_t(k0, k4));

    point_t p_pts[kPlgnPnts] = {point_t(k0, k0), point_t(k3, k0), point_t(k3, k3), point_t(k15, k4), point_t(k0, k3)};
    shapes[2] = new Polygon(p_pts, kPlgnPnts);

    std::cout << "--- BEFORE SCALING ---\n";
    printInfo(shapes, SHAPES_COUNT);

    double px = k0;
    double py = k0;
    double k = k0;
    std::cout << "Enter scale point (x y) and coefficient (k): ";
    if (!(std::cin >> px >> py >> k))
    {
      std::cerr << "Error: invalid input format\n";
      freeShapes(shapes, SHAPES_COUNT);
      return 1;
    }

    if (k <= k0)
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
    double total_area = k0;
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

      const double r_min_x = rect.getPos().getX() - rect.getWidth() / k2;
      const double r_min_y = rect.getPos().getY() - rect.getHeight() / k2;
      const double r_max_x = rect.getPos().getX() + rect.getWidth() / k2;
      const double r_max_y = rect.getPos().getY() + rect.getHeight() / k2;

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
              << ((min_x + max_x) / k2) << ", " << ((min_y + max_y) / k2) << ")\n\n";
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
