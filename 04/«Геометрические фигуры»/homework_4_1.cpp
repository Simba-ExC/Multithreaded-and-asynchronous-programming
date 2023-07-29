//«Рефакторинг»

#include <iostream>
#include "shape.h"
#include "line.h"
#include "rectangle.h"
#include "parallelepiped.h"
#include "circle.h"
#include "cylinder.h"
#include "transform.hpp"


int main(int argc, char** argv) {
    Point p1{ 1, 2, 3 };
    Point p2{ 6, 2, 3 };
    Point p3{ 1, 6, 3 };
    Point p4{ 1, 2, 5 };

    Line l{ p1, p2 };
    Transform<Line> trLine(l);
    l = trLine.scaleX(2);
    l.printInfo();
    std::cout << std::endl;

    Rectangle r{ p1, p2, p3 };
    Transform<Rectangle> trRectangle(r);
    r = trRectangle.shift(1, 1, 1);
    r.printInfo();
    std::cout << std::endl;

    Parallelepiped p{ p1, p2, p3, p4 };
    Transform<Parallelepiped> trPar(p);
    p = trPar.shift(1, 1, 1);
    p.printInfo();
    std::cout << std::endl;

    Circle c(p1, 3);
    Transform<Circle> trCircle(c);
    c = trCircle.shift(1, 1, 1);
    c.printInfo();
    std::cout << std::endl;

    Cylinder cyl(p1, 3, 5);
    Transform<Cylinder> trCylinder(cyl);
    cyl = trCylinder.scaleX(2);
    cyl.printInfo();
    std::cout << std::endl;

}