#include<vector>
#include<functional>
#include<algorithm>
#include"shape.h"
using namespace std;
class Sort{
public:
    Sort(vector<Shape*>*v):_v(v){}
    
    void sortArea(function<bool(Shape*, Shape*)>sA){
        sort(_v->begin(),_v->end(),sA);
    }

    void sortPerimeter(function<bool(Shape*,Shape*)>sP){
        sort(_v->begin(),_v->end(),sP);
    }

    void sortCompactness(function<bool(Shape*,Shape*)>sC){
        sort(_v->begin(),_v->end(),sC);
    }
private:
    vector<Shape*>*_v;
};

bool perimeterAscendingComparison(Shape *a, Shape *b){
    return a->perimeter() < b->perimeter();
}

bool perimeterDescendingComparison(Shape *a,Shape *b){
    return a->perimeter() > b->perimeter();
}

class CompactnessAscendingComparison{
public:
    bool operator()(Shape *a,Shape *b){
        return a->compactness() < b->compactness();//compactness
    }
};

class CompactnessDescendingComparison{
public:
    bool operator()(Shape *a,Shape *b){
        return a->compactness() > b->compactness();
    }
};
