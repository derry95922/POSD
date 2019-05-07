#ifndef SHAPE
#define SHAPE
#include<string>
using namespace std;
class Shape{
public://忘記加
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual double compactness(){
        double p=perimeter(),a=area();
        try{
            if(a==0)throw 0;
            else return p*p/a;
        }catch(int err){
            throw string("Division by zero");
        }
    }
}; 
#endif