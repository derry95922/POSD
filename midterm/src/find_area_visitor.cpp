#include "find_area_visitor.h"
#include "shape.h"
FindAreaVisitor::FindAreaVisitor(double min, double max):_min(min),_max(max){}

void FindAreaVisitor::visit(Shape * s){
    for(int i=0;i<s->numberOfChild();i++){
        if(_min<=s->getChild(i)->area() && s->getChild(i)->area()<=_max)_result.push_back(s);       
        s->getChild(i)->acceptJump(this);
    }   
}

vector<Shape*> FindAreaVisitor::findResult(){
    return _result;
}
