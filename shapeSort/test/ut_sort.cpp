
#include <string>
#include<vector>
#include<iostream>
#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/sort.h"

using namespace std;

TEST(ShapeTest, Sort)
{ 
  vector<Shape*>test_array = {new Circle(0.5), new Circle(1.0), new Rectangle(5, 6), new Rectangle(0.5, 1.5)};
  Sort ting(&test_array);
  //sortArea
  //升area
  ting.sortArea([](Shape * a, Shape *b){return a->area() < b->area();});
  ASSERT_NEAR(0.75, test_array[0]->area(), 0.001);
  ASSERT_NEAR(0.25*3.1415, test_array[1]->area(), 0.001);
  ASSERT_NEAR(3.1415, test_array[2]->area(), 0.001);
  ASSERT_NEAR(30, test_array[3]->area(), 0.001);
  //cout<<"sortArea_a\n";
  //for(int i=0;i<test_array.size();i++)cout<<test_array[i]->area()<<endl;
  //降area
  ting.sortArea([](Shape * a, Shape *b){return a->area() > b->area();});
  ASSERT_NEAR(30, test_array[0]->area(), 0.001);
  ASSERT_NEAR(3.1415, test_array[1]->area(), 0.001);
  ASSERT_NEAR(0.25*3.1415, test_array[2]->area(), 0.001);
  ASSERT_NEAR(0.75, test_array[3]->area(), 0.001);
  //cout<<"sortArea_d\n";
  //for(int i=0;i<test_array.size();i++)cout<<test_array[i]->area()<<endl;

  //sortPerimeter0.5*3.1415*2  22 4
  //降
  ting.sortPerimeter(perimeterDescendingComparison);
  ASSERT_NEAR(22 ,test_array[0]->perimeter(), 0.001);
  ASSERT_NEAR(1*2*3.1415 ,test_array[1]->perimeter(), 0.001);
  ASSERT_NEAR(4 ,test_array[2]->perimeter(), 0.001);
  ASSERT_NEAR(0.5*2*3.1415 ,test_array[3]->perimeter(), 0.001);
  //cout<<"sortPerimeter_d\n";
  //for(int i=0;i<test_array.size();i++)cout<<test_array[i]->perimeter()<<endl;
  //升
  ting.sortPerimeter(perimeterAscendingComparison);
  ASSERT_NEAR(0.5*2*3.1415 ,test_array[0]->perimeter(), 0.001);
  ASSERT_NEAR(4 ,test_array[1]->perimeter(), 0.001);
  ASSERT_NEAR(1*2*3.1415 ,test_array[2]->perimeter(), 0.001);
  ASSERT_NEAR(22 ,test_array[3]->perimeter(), 0.001);
  //cout<<"sortPerimeter_a\n";
  //for(int i=0;i<test_array.size();i++)cout<<test_array[i]->perimeter()<<endl;
  
  //sortCompactness p*p/a 
  //升
  ting.sortCompactness(CompactnessAscendingComparison());
  ASSERT_NEAR(12.566 ,test_array[0]->compactness(), 0.001);
  ASSERT_NEAR(12.566 ,test_array[1]->compactness(), 0.001);
  ASSERT_NEAR(16.1333 ,test_array[2]->compactness(), 0.001);
  ASSERT_NEAR(21.3333 ,test_array[3]->compactness(), 0.001);
  //cout<<"sortCompact_a\n";
  //for(int i=0;i<test_array.size();i++)cout<<test_array[i]->compactness()<<endl;

  //降
  ting.sortCompactness(CompactnessDescendingComparison());
  ASSERT_NEAR(21.3333 ,test_array[0]->compactness(), 0.001);
  ASSERT_NEAR(16.1333 ,test_array[1]->compactness(), 0.001);
  ASSERT_NEAR(12.566 ,test_array[2]->compactness(), 0.001);
  ASSERT_NEAR(12.566 ,test_array[3]->compactness(), 0.001);
  //cout<<"sortCompact_d\n";
  //for(int i=0;i<test_array.size();i++)cout<<test_array[i]->compactness()<<endl;
}
