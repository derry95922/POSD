#include "math.h"
#ifndef TRIANGLE
#define TRIANGLE
#include "shape.h"
#include<string>
using namespace std;
class Triangle:public Shape{
public:
    Triangle(double x1,double y1,double x2,double y2,double x3,double y3):_x1(x1),_y1(y1),_x2(x2),_y2(y2),_x3(x3),_y3(y3){
        a = sqrt(pow(_x1-_x2,2.0) + pow(_y1-_y2,2.0));
        b = sqrt(pow(_x1-_x3,2.0) + pow(_y1-_y3,2.0));
        c = sqrt(pow(_x3-_x2,2.0) + pow(_y3-_y2,2.0));
        s = (a+b+c)/2;

        if(!isTriangle())throw string("Not a triangle.");
    }
    double area(){
        return sqrt(s*(s-a)*(s-b)*(s-c));
    }

    double perimeter(){
        return a+b+c;
    }

    bool isTriangle(){
        if(a+b>c&&a+c>b&&b+c>a)return true;
        else return false;
    }

private:
    double _x1,_x2,_x3,_y1,_y2,_y3,s,a,b,c;
};
#endif