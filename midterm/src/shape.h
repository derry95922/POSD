#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include<iostream>
#include"find_area_visitor.h"
using namespace std;
class Shape
{
public:
  virtual double area() const = 0;
  virtual double perimeter() const = 0;
  virtual int numberOfChild(){
    return 0;
  };
  virtual Shape * getChild(int index){
    return nullptr;
  } 

  virtual void accept(FindAreaVisitor * fav){}
  virtual void acceptJump(FindAreaVisitor * fav){}
};
#endif