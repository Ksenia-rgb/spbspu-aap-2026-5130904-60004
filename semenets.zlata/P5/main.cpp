#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "ellipse.hpp"
#include "triangle.hpp"

using namespace semenets;
void printAll(Shape** arr, size_t n);
void scaleOne(Shape* s, const point_t& p, double k);
void scaleAll(Shape** arr, size_t n, const point_t& p, double k);
void printFrame(rectangle_t rec);

int main()
{
  const size_t size = 3;
  Shape* array[size] = {nullptr, nullptr, nullptr};
  try {
    const double rw = 5.0;
    const double rh = 3.0;
    const point_t rp = {1.0, 1.0};
    const point_t ep = {2.0, 2.0};
    const double erx = 5.0;
    const double ery = 2.0;
    const point_t tr_a = {-4.0, -3.0};
    const point_t tr_b = {-1.0, -3.0};
    const point_t tr_c = {-4.0, 1.0};
    array[0] = new Rectangle(rw, rh, rp);
    array[1] = new Ellipse(ep, erx, ery);
    array[2] = new Triangle(tr_a, tr_b, tr_c);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  point_t p = {0.0, 0.0};
  double k = 0;
  std::cout << "Enter x,y and k:\n";
  if (!(std::cin >> p.x >> p.y >> k)) {
    std::cerr << "Invalid input\n";
    for (size_t i = 0; i < size; i++) {
      delete array[i];
    }
    return 1;
  }
  if (k <= 0.0) {
    std::cerr << "The coefficient k must be positive\n";
    for (size_t i = 0; i < size; i++) {
      delete array[i];
    }
    return 1;
  }
  std::cout << "Before: \n";
  printAll(array, size);
  scaleAll(array, size, p, k);
  std::cout << "After: \n";
  printAll(array, size);
  for (size_t i = 0; i < size; i++) {
    delete array[i];
  }
  return 0;
}
void printAll(Shape** arr, size_t n)
{
  double total_area = 0.0;
  double min_x = 0.0;
  double max_x = 0.0;
  double min_y = 0.0;
  double max_y = 0.0;
  for (size_t i = 0; i < n; i++) {
    const double area = arr[i]->getArea();
    const rectangle_t rec = arr[i]->getFrameRect();
    std::cout << "Shape " << i + 1 << ": area: " << area << "\n";
    printFrame(rec);
    total_area += area;
    const double l = rec.pos.x - rec.width / 2;
    const double r = rec.pos.x + rec.width / 2;
    const double sn = rec.pos.y - rec.height / 2;
    const double sv = rec.pos.y + rec.height / 2;
    if (i == 0) {
      min_x = l;
      max_x = r;
      min_y = sn;
      max_y = sv;
    } else {
      min_x = std::min(min_x, l);
      max_x = std::max(max_x, r);
      min_y = std::min(min_y, sn);
      max_y = std::max(max_y, sv);
    }
  }
  std::cout << "Total area: " << total_area << "\n";
  printFrame({max_x - min_x, max_y - min_y, {(max_x + min_x) / 2.0, (max_y + min_y) / 2}});
}

void scaleOne(Shape* s, const point_t& p, double k)
{
  const point_t old_p = s->getFrameRect().pos;
  s->move(p);
  const point_t new_p = s->getFrameRect().pos;
  s->scale(k);
  s->move((old_p.x - new_p.x) * k, (old_p.y - new_p.y) * k);
}

void scaleAll(Shape** arr, size_t n, const point_t& p, double k)
{
  for (size_t i = 0; i < n; i++) {
    scaleOne(arr[i], p, k);
  }
}

void printFrame(rectangle_t rec)
{
  std::cout << "Frame: width = " << rec.width << ", height = " << rec.height << ", pos(" << rec.pos.x << ";"
            << rec.pos.y << ")\n";
}
