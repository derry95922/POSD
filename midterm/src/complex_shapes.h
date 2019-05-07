#ifndef COMPLEX_SHAPES_H
#define COMPLEX_SHAPES_H
#include <vector>
#include "shape.h"
using namespace std;
class ComplexShapes:public Shape
{
public:
    ComplexShapes(vector<Shape*>*shapes):_shapes(shapes){}
    
    double area() const;
    double perimeter() const;

    int numberOfChild(){
        return _shapes->size();
    }

    void add(Shape * s){
        _shapes->push_back(s);
    }

    Shape * getChild(int index){
        return (*_shapes)[index];
    }

    void accept(FindAreaVisitor * fav){
        fav->clear();
        fav->visit(this);
    }

    void acceptJump(FindAreaVisitor * fav){
        fav->visit(this);
    }
        
private:
    vector<Shape*>*_shapes;
};


#endif