#include "point.h"
#include <iostream>

// Constructors 
Point::Point() {
	x_val = 0;
	y_val = 0;
}

Point::Point(Fraction x, Fraction y) {
	x_val = x;
	y_val = y;
}

// Accessors 
Fraction Point::getXVal() {
	return x_val;
}

Fraction Point::getYVal() {
	return y_val;
}

// Mutators 
void Point::setXVal(Fraction x) {
	x_val = x;
}

void Point::setYVal(Fraction y) {
	y_val = y;
}

// Add/Subtract two points 
Point Point::operator+(const Point& p) {
	Point result;

	result.x_val = x_val + p.x_val;
	result.y_val = y_val + p.y_val;

	return result;
}

Point Point::operator-(const Point& p) {
	Point result;

	result.x_val = x_val - p.x_val;
	result.y_val = y_val - p.y_val;

	return result;
}

//Scalar multiplication of point 
Point Point::operator*(const Fraction& f) {
	Point result;

    result.x_val = x_val * f;
	result.y_val = y_val * f;

	return result;
}

// Cross product of two points 
Fraction Point::operator*(const Point& p) {
	Fraction result; 

	result = (x_val * p.y_val) - (y_val * p.x_val);
			
	return result;
}

// I/O Operators 
std::istream& operator>>(std::istream& is, Point& p) {
	Fraction x, y;
	char par1, par2, comma;


	is >> par1 >> x >> comma >> y >> par2;

	p = Point(x, y);

	return is;
}

std::ostream& operator<<(std::ostream& os, Point& p) {
	Fraction x = p.getXVal();
	Fraction y = p.getYVal();

	os << "(" << x << "," << y << ")";

	return os;
}

