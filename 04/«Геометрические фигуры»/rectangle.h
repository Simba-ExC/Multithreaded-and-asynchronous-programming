// homework_4_1.cpp : rectangle.h

#pragma once
#include "line.h"

class Rectangle : public Line {
public:
	Rectangle() {};
	Rectangle(Point p1, Point p2, Point p3);
	std::vector<double>& getSides();
	
	Point fourthVertex(Point p1, Point p2, Point p3);
	std::vector<double> rectangleSides(Point p1, Point p2, Point p3);
	double getSquare() override;
	void printInfo() override;

protected:
	std::vector<double> sides{};
};
