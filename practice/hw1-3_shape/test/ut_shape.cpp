#include <iostream>
#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
using namespace std;
TEST(ShapeTest,true){
    ASSERT_TRUE(true);
}

TEST(ShapeTest , Circle){
    Circle c(10.0);
    ASSERT_NEAR(314.159,c.area(),0.001);
    ASSERT_NEAR(62.831,c.perimeter(),0.001);
}

TEST(ShapeTest , Rectangle){
    Rectangle r(5.0,4.0);
    ASSERT_NEAR(20.0,r.area(),0.001);
    ASSERT_NEAR(18.0,r.perimeter(),0.001);
}

TEST(ShapeTest , Triangle){
    Triangle t(0.0 , 3.0 , 4.0 , 0.0 , 0.0 , 0.0);
    ASSERT_NEAR(6.0,t.area(),0.001);
    ASSERT_NEAR(12.0,t.perimeter(),0.001);
    ASSERT_EQ(t.isTriangle(),true);
}

TEST(ShapeTest, isTriangle){
    try{
        Triangle t(0.0 , 0.0 , 4.0 , 0.0 , 0.0 , 0.0);
    }catch(string err){
        ASSERT_EQ(err,"Not a triangle.");
    }
}