#ifndef circle_h
#define circle_h
#include<math.h>
#include"shape.h"

class Circle: public Shape
{
public:
  Circle(double r):_r(r){

  }

  double area() const{
    return M_PI * _r * _r;
  }

  double perimeter() const{
    return 2 * M_PI * _r;
  }

private:
  double _r;
};
#endif