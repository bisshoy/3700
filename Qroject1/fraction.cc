// 
// fraction.cc
//
// Contains actual functions for fraction class, including arithmetic, logical,
// and I/O operators 
// 
// written 11 September 2023 by Bisshoy Anwar 
//
// modification history
//   14 September 2023 - Bisshoy Anwar  
//     Built simplification into constructor 
//     Changed GCD function from recursive to while loop
//

#include "fraction.h"
#include "point.h"

// Constructors 

// 
// Fraction(int32_t n) 
//   constructor for fraction with only one parameter 
// 
// Parameter
//   n - 32 bit integer 
//
Fraction::Fraction(int32_t n) {
	num = n;
	den = 1;
}

// 
// Fraction(int32_t n, int32_t d)
//   constructor for fraction with two parameters 
//
// Parameters 
//   n - 32 bit integer 
//   d - 32 bit integer 
// 
Fraction::Fraction(int32_t n, int32_t d) {
	int32_t div;

	if (d < 0) {
		n *= -1;
		d *= -1;
	}

	div = gcd(n, d);

	num = n / div;
	den = d / div;
}

// 
// int32_t gcd(int32_t a, int32_t b)
//
// Parameters 
//   a - 32 bit integer 
//   b - 32 bit integer 
// 
// Returns
//   32 bit integer greatest common divisor of parameters 
int32_t Fraction::gcd(int32_t a, int32_t b) {
	int32_t r;

	a = (a >= 0) ? a : -a;
	b = (b >= 0) ? b : -b;

	while (b != 0) {
		r = a % b;
		a = b;
		b = r;
	}

	return a;
}

// Arithmetic Operators 

// 
// Fraction operator+(const Fraction& f) 
//   adds two fractions 
//
// Parameter 
//   f - the rhs fraction object 
// 
// Returns 
//   resulting sum fraction 
//   
Fraction Fraction::operator+(const Fraction& f) {
	int32_t s, t;

	s = (num * f.den) + (f.num * den);
	t = den * f.den;
		
	return Fraction(s, t);
}

// 
// Fraction operator-(const Fraction& f) 
//   subtracts rhs fraction from lhs fraction 
//
// Parameter 
//   f - the rhs fraction object 
// 
// Returns 
//   resulting difference fraction 
//   
Fraction Fraction::operator-(const Fraction& f) {
	int32_t s, t;

	s = (num * f.den) - (f.num * den);
	t = den * f.den;

	return Fraction(s ,t);
}

// 
// Fraction operator*(const Fraction& f) 
//   multiplies two fractions 
// 
// Parameter 
//   f - the rhs fraction object 
// 
// Returns 
//   resulting product fraction 
//   
Fraction Fraction::operator*(const Fraction& f) {
	return Fraction(num * f.num, den * f.den);
}

// 
// Fraction operator/(const Fraction& f) 
//   divides two fractions 
// 
// Parameter 
//   f - the rhs fraction object 
// 
// Returns 
//   resulting quotient fraction 
//   
Fraction Fraction::operator/(const Fraction& f) {
	return Fraction(num * f.den, den * f.num);
}

// Boolean Operators 

// 
// bool operator==(const Fraction& f)
//   checks for equality of two fractions 
// 
// Parameter 
//   f - rhs fraction object 
// 
// Returns 
//   true iff fractions are equal to each other 
//
bool Fraction::operator==(const Fraction& f) {
	return ((num == f.num) && (den == f.den));
}

// 
// bool operator!=(const Fraction& f)
//   checks for inequality of two fractions 
// 
// Parameter 
//   f - rhs fraction object 
// 
// Returns 
//   true iff fractions are not equal to each other 
//
bool Fraction::operator!=(const Fraction& f) {
	return !((num == f.num) && (den == f.den));
}

// 
// bool operator<(const Fraction& f)
//   checks if lhs is less than rhs 
// 
// Parameter 
//   f - rhs fraction object 
// 
// Returns 
//   true iff lhs is less than to rhs  
//
bool Fraction::operator<(const Fraction& f) {
	return ((num * f.den) < (den * f.num));
}

// 
// bool operator>(const Fraction& f)
//   checks if lhs is greater than rhs 
// 
// Parameter 
//   f - rhs fraction object 
// 
// Returns 
//   true iff lhs is greater than rhs 
//
bool Fraction::operator>(const Fraction& f) {
	return ((num * f.den) > (den * f.num));
}

// 
// bool operator<=(const Fraction& f)
//   checks if lhs is less than or equal to rhs 
// 
// Parameter 
//   f - rhs fraction object 
// 
// Returns 
//   true iff lhs is less than or equal to rhs  
//
bool Fraction::operator<=(const Fraction& f) {
	return ((num * f.den) <= (den * f.num));
}

// 
// bool operator>=(const Fraction& f)
//   checks if lhs is greater than or equal to rhs 
// Parameter 
//   f - rhs fraction object 
// 
// Returns 
//   true iff lhs is greater than or equal to rhs  
//
bool Fraction::operator>=(const Fraction& f) {
	return ((num * f.den) >= (den * f.num));
}

// I/O Operators 

// 
// std::istream& operator>>(std::istream& is, Fraction& f)
//   takes fraction as input 
// 
// Parameters
//   is - input stream 
//   f  - rhs fraction object 
// 
// Returns 
//   input stream 
//
std::istream& operator>>(std::istream& is, Fraction& f) {
	int32_t n, d;
	char slash;

	is >> n >> slash >> d;

	f = Fraction(n, d);

	return is;
}

//
// std::ostream& operator<<(std::ostream& os, Fraction& f)
//   prints fraction as output 
// 
// Parameters 
//   os - output stream 
//   f  - rhs fraction object 
// 
// Returns 
//   output stream 
//
std::ostream& operator<<(std::ostream& os, Fraction& f) {
	os << f.getNum() << " / " << f.getDen();
	return os;
}