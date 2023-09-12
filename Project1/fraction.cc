#include "fraction.h"
#include "point.h"

#include <iostream>

Fraction::Fraction() {
	num = 0;
	den = 1;
}

Fraction::Fraction(int32_t n) {
	num = n;
	den = 1;
}

Fraction::Fraction(int32_t n, int32_t d) {
	num = n;
	den = d;
}

const int32_t Fraction::getNum() {
	return num;
}

const int32_t Fraction::getDen() {
	return den;
}

int32_t Fraction::gcd(int32_t a, int32_t b) {
	int32_t tmp;

	while (b != 0) {
		tmp = b;
		b = a % b;
		a = tmp;

		gcd(a, b);
	}

	return a;
}

void Fraction::simplify() {
	int32_t divisor;

	if ((gcd(num, den)) != 1) {
		divisor = gcd(num, den);

		num /= divisor;
		den /= divisor;
	}

	if (den < 0) {
		num *= -1;
		den *= -1;
	}
}

void Fraction::simplify(Fraction& a) {
	int32_t divisor;

	if ((gcd(a.num, a.den)) != 1) {
		divisor = gcd(a.num, a.den);

		a.num   /= divisor;
		a.den /= divisor;
	}

	if (a.den < 0) {
		a.num *= -1;
		a.den *= -1;
	}
}

// Arithmetic Operators 
Fraction Fraction::operator+(const Fraction& f) {
	Fraction result;

	result.num = (num * f.den) + (f.num * den);
	result.den = den * f.den;
		
	simplify(result);
	return result;
}

Fraction Fraction::operator-(const Fraction& f) {
	Fraction result;

	result.num = (num * f.den) - (f.num * den);
	result.den = den * f.den;

	simplify(result);
	return result;
}

Fraction Fraction::operator*(const Fraction& f) {
	Fraction result;

	result.num = num * f.num;
	result.den = den * f.den;

	simplify(result);
	return result;
}

Fraction Fraction::operator/(const Fraction& f) {
	Fraction result, d;
	int32_t tmp;

	d.num = f.num;
	d.den = f.den;

	tmp = d.num;
	d.num = d.den;
	d.den = tmp;

	result.num = num * d.num;
	result.den = den * d.den;

	simplify(result);
	return result;
}

// Boolean Operators 
bool Fraction::operator==(const Fraction& f) {
	return ((static_cast<float>(num) / den)
	== (static_cast<float>(f.num) / f.den));
}

bool Fraction::operator!=(const Fraction& f) {
	return ((static_cast<float>(num) / den)
	!= (static_cast<float>(f.num) / f.den));
}

bool Fraction::operator>(const Fraction& f) {
	return ((static_cast<float>(num) / den)
	> (static_cast<float>(f.num) / f.den));
}

bool Fraction::operator>=(const Fraction& f) {
	return ((static_cast<float>(num) / den)
	>= (static_cast<float>(f.num) / f.den));
}

bool Fraction::operator<(const Fraction& f) {
	return ((static_cast<float>(num) / den)
	< (static_cast<float>(f.num) / f.den));
}

bool Fraction::operator<=(const Fraction& f) {
	return ((static_cast<float>(num) / den)
	<= (static_cast<float>(f.num) / f.den)); 
}

// I/O Operators 
std::istream& operator>>(std::istream& is, Fraction& f) {
	int32_t n, d;
	char slash;

	is >> n >> slash >> d;

	f = Fraction(n, d);
	f.simplify();

	return is;
}

std::ostream& operator<<(std::ostream& os, Fraction& f) {
	os << f.getNum() << " / " << f.getDen();
	return os;
}

