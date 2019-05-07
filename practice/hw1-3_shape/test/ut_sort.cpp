#include<vector>
#include"../src/shape.h"
#include"../src/circle.h"
#include"../src/rectangle.h"
#include"../src/triangle.h"
#include"../src/sort.h"
TEST(ShapeTest,Sort){
    vector<Shape*>test_array = {new Circle(0.5), new Circle(1.0), new Rectangle(5, 6), new Rectangle(0.5, 1.5)};
    Sort ting(&test_array);
    //升
    ting.sortArea([](Shape * a, Shape *b){return a->area() < b->area();});
    // ting.sortArea([](Shape *a,Shape *b){return a->area()<b->area();});
    ASSERT_NEAR(0.75, test_array[0]->area(), 0.001);
    ASSERT_NEAR(0.25*3.1415, test_array[1]->area(), 0.001);
    ASSERT_NEAR(3.1415, test_array[2]->area(), 0.001);
    ASSERT_NEAR(30, test_array[3]->area(), 0.001);
    //降
    ting.sortArea([](Shape *a,Shape *b){return a->area()>b->area();});
    ASSERT_NEAR(0.75, test_array[3]->area(), 0.001);
    ASSERT_NEAR(0.25*3.1415, test_array[2]->area(), 0.001);
    ASSERT_NEAR(3.1415, test_array[1]->area(), 0.001);
    ASSERT_NEAR(30, test_array[0]->area(), 0.001);
    //升
    ting.sortPerimeter(perimeterAscendingComparison);
    ASSERT_NEAR(0.5*2*3.1415 ,test_array[0]->perimeter(), 0.001);
    ASSERT_NEAR(4 ,test_array[1]->perimeter(), 0.001);
    ASSERT_NEAR(1*2*3.1415 ,test_array[2]->perimeter(), 0.001);
    ASSERT_NEAR(22 ,test_array[3]->perimeter(), 0.001);
    //降
    ting.sortPerimeter(perimeterDescendingComparison);
    ASSERT_NEAR(0.5*2*3.1415 ,test_array[3]->perimeter(), 0.001);
    ASSERT_NEAR(4 ,test_array[2]->perimeter(), 0.001);
    ASSERT_NEAR(1*2*3.1415 ,test_array[1]->perimeter(), 0.001);
    ASSERT_NEAR(22 ,test_array[0]->perimeter(), 0.001);
    //升
    ting.sortCompactness(CompactnessAscendingComparison());
    ASSERT_NEAR(12.566 ,test_array[0]->compactness(), 0.001);
    ASSERT_NEAR(12.566 ,test_array[1]->compactness(), 0.001);
    ASSERT_NEAR(16.1333 ,test_array[2]->compactness(), 0.001);
    ASSERT_NEAR(21.3333 ,test_array[3]->compactness(), 0.001);
    //降
    ting.sortCompactness(CompactnessDescendingComparison());
    ASSERT_NEAR(12.566 ,test_array[3]->compactness(), 0.001);
    ASSERT_NEAR(12.566 ,test_array[2]->compactness(), 0.001);
    ASSERT_NEAR(16.1333 ,test_array[1]->compactness(), 0.001);
    ASSERT_NEAR(21.3333 ,test_array[0]->compactness(), 0.001);
}