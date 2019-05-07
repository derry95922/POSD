#include <iostream>
#include "../src/triangle.h"
// TEST(ShapeTest,true){
//     ASSERT_TRUE(true);
// }

TEST(ShapeTest , Triangle){
    Triangle t(3,4,5);
    ASSERT_EQ(t.isTriangle(),true);
}
TEST(ShapeTest , notATriangle){
    try{
        Triangle t_false(0,1,1);
    }catch(string err){
        ASSERT_EQ(err,"illegal triangle");
    }
}
TEST(Triangle,Factory){
    // ASSERT_EQ("correct",t.create();
    try{
        Triangle t(3,4,5);
    }catch(string err){
        ASSERT_EQ(err,"correct");
    }
}
// TEST(Triangle,abFactory){
//     Triangle t(0,1,1);
//     ASSERT_EQ(nullptr,t.create());
// }