#ifndef triangle_h
#define triangle_h
#include <math.h>
#include<string> 
#include<iostream>
using namespace std;
class Triangle{
public:
    // class TriangleFactory{
    // public:
    //     TriangleFactory(Triangle * t):_t(t){ }
    //     // Triangle * newCreate(){
    //     //     if(!_t->isTriangle())return nullptr;
    //     // }
    // private:
    //     Triangle * _t;
    // };
    Triangle(int a,int b,int c):_a(a),_b(b),_c(c){
        // Triangle T(_a,_b,_c);
        // T->create(_a,_b,_c);
        if(!isTriangle()){
            
            throw string("illegal triangle");
        }
    }
    bool isTriangle(){
        if(_a+_b>_c && _a+_c>_b && _b+_c>_a && _a>0 && _b>0 && _c>0)return true;
        else return false;
    }
    bool isFactory(){
        if(_a+_b>_c && _a+_c>_b && _b+_c>_a && _a>0 && _b>0 && _c>0)return true;
        else return false;
    }
    // TriangleFactory * create(int _a,int _b,int _c){  //factory method
    //     // if(isTriangle())return new Triangle(_a,_b,_c);
    //     // return nullptr;
    //     return new TriangleFactory(this);
    // }
    Triangle * create(){
        if(!isFactory())return nullptr;
        else throw string("correct");
    }
private:
    int _a,_b,_c;
};
#endif