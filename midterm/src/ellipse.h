#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "math.h"
class Ellipse:public Shape{
public:
    Ellipse(double a, double b):_a(a),_b(b){

    }
    double area() const{
        return M_PI*_a*_b;
    }
    double perimeter() const{
        return 2*M_PI*sqrt( ((_a*_a)+(_b*_b)) /2  );
    }
private:
    double _a,_b;
};

#endif