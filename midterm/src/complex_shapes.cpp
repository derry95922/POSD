#include "complex_shapes.h"
#include<vector>

double ComplexShapes::area() const{
    double sum =0;
    for(int i=0;i<_shapes->size();i++){
        sum+=_shapes->at(i)->area();
    }
    return sum;    
}

double ComplexShapes::perimeter() const{
    double sum =0;
    for(int i=0;i<(*_shapes).size();i++){
        sum+=(*_shapes)[i]->perimeter();
    }
    return sum;
}
