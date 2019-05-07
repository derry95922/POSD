#ifndef sort_h
#define sort_h
#include<functional>    //
#include<algorithm>
using namespace std;
class Sort{
    public:
      Sort(std::vector<Shape*>* v): _v(v){}
      //v是一個指標，指到一個向量，向量裡面存著很多指到shape型態的指標。
      // The argument ** Accept comparison ** can accept lambda, function, and object    //std::function<bool(Shape* ,Shape*)>sA
      void sortArea(std::function<bool(Shape* ,Shape*)>sA){
        sort(_v->begin(),_v->end(),sA);
      }

      void sortPerimeter(std::function<bool(Shape* ,Shape*)>sP ){
        sort(_v->begin(), _v->end(), sP);
      }

      void sortCompactness(std::function<bool(Shape* ,Shape*)>sC){
        sort(_v->begin(),_v->end(), sC);
      }

    private:
      std::vector<Shape*>* _v;
};

// //You should use those functions as parameter for Sort::sortPerimeter()
bool perimeterDescendingComparison(Shape *a, Shape *b){
  return a->perimeter() > b->perimeter();
}

bool perimeterAscendingComparison(Shape *a, Shape *b){
  return a->perimeter() < b->perimeter();
}
// //You should use those objects as parameter for Sort::sortCompactness()
class CompactnessAscendingComparison{
public:
  bool operator() (Shape *a, Shape *b) {
    return a->compactness() < b->compactness();
  }
};

class CompactnessDescendingComparison{
public:
  bool operator() (Shape *a, Shape *b) {
    return a->compactness() > b->compactness();
  }
};
#endif