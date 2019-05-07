#ifndef shape_h
#define shape_h
#include<string>
#include<iostream>
using namespace std;
class Shape {
//...
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual double compactness(){
        double p=perimeter(), a=area();
        try{
            if(a==0){
                throw 0;
            }else{
                return (p*p)/a;
            }
        }catch(int err){
            throw string("Division by zero");
        }
    }
//...
};
#endif