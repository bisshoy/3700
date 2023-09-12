#include "fraction.h"

#ifndef _POINT_H
#define _POINT_H

class Point {
	private:
		Fraction x_val;
		Fraction y_val;
	public:
		// Constructors 
		Point();
		Point(Fraction, Fraction); 

		// Accessors 
		Fraction getXVal();
		Fraction getYVal();

		// Mutators 
		void setXVal(Fraction);
		void setYVal(Fraction);

		// Add/Subtract two points 
		Point operator+(const Point&);
		Point operator-(const Point&);

		//Scalar multiplication of point 
		Point operator*(const Fraction&);

		// Cross product of two points 
		Fraction operator*(const Point&);
};

// I/O Operators 
std::istream& operator>>(std::istream&, Point&);
std::ostream& operator<<(std::ostream&, Point&);

#endif