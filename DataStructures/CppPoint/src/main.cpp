#include <iostream>
#include "xipoint.h"

int main(int argc, char **argv)
{
    using namespace xi;

    Point p1(1, 1);
    Point pointar[] = {p1};
    PointArray arr = PointArray(pointar, 1);
    p1.setX(2);
    std::cout << arr.get(0)->getX();

}
