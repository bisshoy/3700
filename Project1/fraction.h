#include <cstdint>
#include <iostream>

#ifndef _FRACTION_H
#define _FRACTION_H

class Fraction {
	private: 
		int32_t num;
		int32_t den;
	public:
		// Constructors;
		Fraction();
		Fraction(int32_t);
		Fraction(int32_t, int32_t);

		// Accessors, simplifiers, GCD finder 
		const int32_t getNum(); 
		const int32_t getDen(); 
		int32_t gcd(int32_t, int32_t);
		void simplify();
		void simplify(Fraction&);

		// Arithemetic Operators
		Fraction operator+(const Fraction&);
		Fraction operator-(const Fraction&);
		Fraction operator*(const Fraction&);
		Fraction operator/(const Fraction&);

		// Boolean Operators
		bool operator==(const Fraction&);
		bool operator!=(const Fraction&);
		bool operator>(const Fraction&);
		bool operator>=(const Fraction&);
		bool operator<(const Fraction&);
		bool operator<=(const Fraction&);
};

// I/O Operators 
std::istream& operator>>(std::istream&, Fraction&);
std::ostream& operator<<(std::ostream&, Fraction&);

#endif

