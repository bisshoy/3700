// main.cc
//
// Driver code to find relationship between two lines from four points 
//
// written 11 September 2023 by Bisshoy Anwar 
//

#include "fraction.h"
#include "point.h"

using namespace std;

int main() {
	Point p1, p2, q1, q2, r, s, v, i_point;  
	Fraction d, t, u;

	// Input coordinates of p1 and p2
	cout << "Enter point p1: ";
	cin >> p1;

	cout << "Enter point p2: ";
	cin >> p2;

	// Input coordinates of q1 and q2 
	cout << "Enter point q1: ";
	cin >> q1;

	cout << "Enter point q2: ";
	cin >> q2;
	cout << endl;

	r = p2 - p1;
	s = q2 - q1;

	v = q1 - p1;
	d = r * s;

	// if d = 0 then 
	if (d == 0) {
		// if v x s = 0 then 
		if ((v*s) == 0) {
			// segments are collinear 
			cout << "Segments are collinear" << endl;
			return 0; 
		}

		// else 
		else {
			// segments are parallel 
			cout << "Segments are parallel" << endl;
			return 0;
		}
	}

	// else 
	else {
		// t = (v x s) / d
		t = (v*s) / d;
		// u = (v x r) / d
		u = (v*r) / d;
	}

	// if 0 ≤ t ≤ 1and 0 ≤ u ≤ 1 then
	if ((t >= 0 && t <= 1) && (u >= 0 && u <= 1)) {
		// calculate intersection point from one point 
		Point adder = r * t;
		i_point = p1 + adder;

		cout << "Segments intersect at " << i_point << endl;
	}

	else {
		// else 
		cout << "Segments not parallel but do not intersect" << endl;
	}

    return 0;
}

