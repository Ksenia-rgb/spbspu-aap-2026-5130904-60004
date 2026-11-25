#include <iostream>
#include <limits>
#include "Rectangle.h"
#include "Complexquad.h"
#include "Polygon.h"

namespace romanov
{

void scaleRelativeToPoint(Shape* shape, const point_t& p, double k);
void printInfo(Shape** shapes, unsigned int count);
void freeShapes(Shape** shapes, unsigned int count);

}
using namespace romanov;

int main()
{
  const unsigned int SHAPES_COUNT = 3;
  Shape** shapes = new Shape*[SHAPES_COUNT];
  for (unsigned int i = 0; i < SHAPES_COUNT; ++i)
  {
    shapes[i] = nullptr;
  }
  try
  {
    point_t rPts[4] = {
      point_t(0.0, 0.0), point_t(2.0, 0.0),
      point_t(2.0, 2.0), point_t(0.0, 2.0)
    };
    shapes[0] = new Rectangle(rPts[0], rPts[1], rPts[2], rPts[3]);

    shapes[1] = new Complexquad(
      point_t(0.0, 0.0), point_t(4.0, 4.0),
      point_t(4.0, 0.0), point_t(0.0, 4.0));

    point_t pPts[5] = {
      point_t(0.0, 0.0), point_t(3.0, 0.0),
      point_t(3.0, 3.0), point_t(1.5, 4.0),
      point_t(0.0, 3.0)
    };
    shapes[2] = new Polygon(pPts, 5);

    std::cout << "--- BEFORE SCALING ---\n";
    printInfo(shapes, SHAPES_COUNT);

    double px = 0.0;
    double py = 0.0;
    double k = 0.0;
    std::cout << "Enter scale point (x y) and coefficient (k): ";
    if (!(std::cin >> px >> py >> k))
    {
      std::cerr << "Error: invalid input format\n";
      freeShapes(shapes, SHAPES_COUNT);
      return 1;
    }

    if (k <= 0.0)
    {
      std::cerr << "Error: coefficient must be positive\n";
      freeShapes(shapes, SHAPES_COUNT);
      return 1;
    }

    point_t scalePoint(px, py);
    for (unsigned int i = 0; i < SHAPES_COUNT; ++i)
    {
      scaleRelativeToPoint(shapes[i], scalePoint, k);
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
  point_t c = shape->getFrameRect().getPos();
  shape->move(p);
  shape->scale(k);
  point_t newPos(p.getX() + k * (c.getX() - p.getX()),
                 p.getY() + k * (c.getY() - p.getY()));
  shape->move(newPos);
}

void printInfo(Shape** shapes, unsigned int count)
{
  double totalArea = 0.0;
  double minX = std::numeric_limits<double>::max();
  double minY = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::lowest();
  double maxY = std::numeric_limits<double>::lowest();

  for (unsigned int i = 0; i < count; ++i)
  {
    double area = shapes[i]->getArea();
    totalArea += area;
    std::cout << "Shape " << i + 1 << " area: " << area << "\n";

    rectangle_t rect = shapes[i]->getFrameRect();
    std::cout << "Shape " << i + 1 << " frame rect: width=" << rect.getWidth()
              << ", height=" << rect.getHeight()
              << ", pos=(" << rect.getPos().getX()
              << ", " << rect.getPos().getY() << ")\n";

    double rMinX = rect.getPos().getX() - rect.getWidth() / 2.0;
    double rMinY = rect.getPos().getY() - rect.getHeight() / 2.0;
    double rMaxX = rect.getPos().getX() + rect.getWidth() / 2.0;
    double rMaxY = rect.getPos().getY() + rect.getHeight() / 2.0;

    if (rMinX < minX)
    {
      minX = rMinX;
    }
    if (rMinY < minY)
    {
      minY = rMinY;
    }
    if (rMaxX > maxX)
    {
      maxX = rMaxX;
    }
    if (rMaxY > maxY)
    {
      maxY = rMaxY;
    }
  }

  std::cout << "Total area: " << totalArea << "\n";
  std::cout << "Global frame rect: width=" << (maxX - minX)
            << ", height=" << (maxY - minY)
            << ", pos=(" << ((minX + maxX) / 2.0)
            << ", " << ((minY + maxY) / 2.0) << ")\n\n";
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
