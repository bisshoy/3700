// main.cc
//
// Driver code to run stack-based calculator  
//
// written 24 October 2023 by Bisshoy Anwar 
//

#include <iostream>
#include <stdexcept>
#include "stack.h"
#include "fraction.h"
#include "dictionary.h"
#include "calcFunctions.h"

using namespace std;

int main(int argc, char *argv[]) {
	string expr;

	// Debug mode flag catcher 
	if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 't') {
		if (argv[1][2]) {
			std::cout << "Too many arguments" << endl;
			return 0;
		}

		while (true) {
			std::cout << "Calc: ";
			getline(cin, expr);
			if (expr == "#") {
				std::cout << endl;
				return 0;
			}

			else {
				debug(expr);
			}
		}

		return 0;
	}

	// Main calculator loop 
	while (true) {
		std::cout << "Calc: ";
		getline(cin, expr);
		if (expr == "#") {
			std::cout << endl;
			return 0;
		}

		else {
			evaluate(expr);
		}
	}

	return 0;
}


