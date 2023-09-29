// 
// point.cc
//
// actual functions for point class, including arithmetic, logical, and I/O 
// operators 
//
// written 11 September 2023 by Bisshoy Anwar 
//

#include "point.h"

// Constructors 

// 
// Point(Fraction x, Fraction y)
//   Constructor for a point with two parameters 
//
// Parameters 
//   x - Fraction object to represent point's x value 
//   y - Fraction object to represent point's y value 
// 
Point::Point(Fraction x, Fraction y) {
	x_val = x;
	y_val = y;
}

// Mutators 

// 
// void setXVal(Fraction x) 
//   changes x_val of point 
// 
// Parameter 
//   x - new x_val of point 
//
void Point::setXVal(Fraction x) {
	x_val = x;
}

// 
// void setYVal(Fraction y) 
//   changes y_val of point 
// 
// Parameter 
//   y - new y_val of point 
// 
void Point::setYVal(Fraction y) {
	y_val = y;
}

// Add/Subtract two points

// 
// Point operator+(const Point& p)
//   adds two points 
// 
// Parameter 
//   p - rhs point 
// 
// Returns 
//   new point with x value of the sum of constituents' x values, and 
//   y value of the sum of constituents' y values 
//
Point Point::operator+(const Point& p) {
	return Point(x_val + p.x_val, y_val + p.y_val);
}

// 
// Point operator-(const Point& p)
//   subtracts two points 
// 
// Parameter 
//   p - rhs point 
// 
// Returns 
//   new point with x value of the difference of constituents' x values, and 
//   y value of the difference of constituents' y values 
//
Point Point::operator-(const Point& p) {
	return Point(x_val - p.x_val, y_val - p.y_val);
}

// Scalar multiplication of point 
// 
// Point operator*(const Fraction& p)
//   multiplies point by scalar value 
// 
// Parameter 
//   f - fraction scalar multiplier 
// 
// Returns 
//   new point with x and y values both multiplied by scalar value 
//
Point Point::operator*(const Fraction& f) {
	return Point(x_val * f, y_val * f);
}

// Cross product of two points 
// 
// Fraction operator*(const Point& p) 
//   determines cross product of two points 
// 
// Parameter 
//   p - rhs point 
// 
// Returns 
//   fraction cross product of lhs and rhs points 
//
Fraction Point::operator*(const Point& p) {
	return (x_val * p.y_val) - (y_val * p.x_val);
}

// I/O Operators 

// 
// std::istream& operator>>(std::istream& is, Point& p)
//   takes point as input 
// 
// Parameters 
//   is - input stream 
//   p  - point to be input 
// 
// Returns 
//   input stream 
//  
std::istream& operator>>(std::istream& is, Point& p) {
	Fraction x, y;
	char par1, par2, comma;


	is >> par1 >> x >> comma >> y >> par2;

	p = Point(x, y);

	return is;
}

// 
// std::ostream& operator>>(std::ostream& os, Point& p) 
//   prints point as output  
// 
// Parameters 
//   os - output stream 
//   p  - point to be output 
// 
// Returns 
//   output stream 
// 
std::ostream& operator<<(std::ostream& os, Point p) {
	Fraction x = p.getXVal();
	Fraction y = p.getYVal();

	os << "(" << x << "," << y << ")";

	return os;
}
