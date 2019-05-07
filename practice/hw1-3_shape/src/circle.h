#ifndef CIRCLE
#define CIRCLE
#include "shape.h"
#include "math.h"
class Circle:public Shape{
public:
    Circle(double r):_r(r){

    }

    double area() {
        return _r*_r*M_PI;
    }

    double perimeter() {
        return 2*_r*M_PI;
    }

private:
    double _r;
};
#endif