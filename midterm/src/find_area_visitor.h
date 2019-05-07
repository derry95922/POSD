#ifndef FIND_AREA_VISITOR_H
#define FIND_AREA_VISITOR_H
#include<vector>
class Shape;
class FindAreaVisitor {
public:
    FindAreaVisitor(double min, double max);

    void visit(Shape * s);
    std::vector<Shape*>findResult();
    void clear(){
        _result.clear();
    }

private:
    int _min,_max;
    std::vector<Shape*>_result;
};
#endif