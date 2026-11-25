#pragma once
namespace romanov {
class point_t
{
private:
  double x_,y_;
public:
  point_t(double x = 0.0, double y = 0.0) : x_(x), y_(y) {}
  double getX() const
  {
    return x_;
  }
  double getY() const
  {
    return y_;
  }
  void setX(double x)
  {
    x_ = x;
  }
  void setY(double y)
  {
    y_ = y;
  }
};
class rectangle_t
{
private:
  double width_, height_;
  point_t pos_;
public:
  rectangle_t(double width, double height, const point_t& pos) :
    width_(width), height_(height), pos_(pos) {}
  double getWidth() const { return width_; }
  double getHeight() const { return height_; }
  point_t getPos() const { return pos_; }
};

}
