#ifndef RECTANGLE
#define RECTANGLE
#include "shape.h"
class Rectangle:public Shape{
public:
    Rectangle(double w,double l):_w(w),_l(l){

    }

    double area() {
        return _w*_l;
    }

    double perimeter(){
        return 2*(_w+_l);
    }

private:
    double _w,_l;
};
#endif