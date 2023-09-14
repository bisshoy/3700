// 
// fraction.h 
//
// fraction class header, with appropriate overloaded arithemetic, logical, and 
// I/O operators 
//
// written 11 September 2023 by Bisshoy Anwar 
// 
// modification history
//   14 September 2023 - Bisshoy Anwar 
//     Built simplification into constructor 
//     Changed GCD function from recursive to while loop 
//

#include <cstdint>
#include <iostream>

#ifndef _FRACTION_H
#define _FRACTION_H

class Fraction {
	private: 
		int32_t num;
		int32_t den;
	public:
		// Constructors/Destructor 
		Fraction() { num = 0; den = 1; }
		Fraction(int32_t);
		Fraction(int32_t, int32_t);
		~Fraction() = default;

		// Accessors, simplifiers, GCD finder 
		const int32_t getNum() { return num; }
		const int32_t getDen() { return den; }
		int32_t gcd(int32_t, int32_t); // Is my use of recursion okay here? 

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