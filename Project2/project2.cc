#include "stack.h"
#include "fraction.h"
#include "dictionary.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Stack<operand> numStack;
Stack<char>  opStack;
Dictionary vars; 

bool hasPrecedence(char top, char input) {
	// input = s.peek();      A IS NEXT INPUT
	// top = opStack.peek() B IS TOP OF OPSTACK
	// TRUE means opStack has precedence over s[first]
	
	// Should be called like this:
	// hasPrecedence(opStack.peek(), s[string]);

	if ((top == '*' || top == '/') || 
	(((top == '+' || top == '-') && 
	 (input == '+' || input == '-' || input == '=')))) {
		return true;
	}

	else if ((top == '=' || top == '(' || top == '$') 
	|| ((top == '+' || top == '-') && (input == '*' || input == '/'))) {
		return false;
	}

	else {
		return false;
	}

}

void doOp() {
	operand lhs, rhs, ans;
	char op; 

	rhs = numStack.pop();
	lhs = numStack.pop();
	op = opStack.pop();

	if (!rhs.name.empty()) {
		rhs.val = vars.search(rhs.name);
	}

	if (op != '=' && !lhs.name.empty()) {
		lhs.val = vars.search(lhs.name);
	}

	switch (op) {
		case '+':
			ans.val = lhs.val + rhs.val;
			ans.name = "";
			numStack.push(ans);
			break;

		case '-': 
			ans.val = lhs.val - rhs.val;
			ans.name = "";
			numStack.push(ans);
			break;

		case '*':
			ans.val = lhs.val * rhs.val;
			ans.name = "";
			numStack.push(ans);
			break; 

		case '/':
			ans.val = lhs.val / rhs.val;
			ans.name = "";
			numStack.push(ans);
			break;
		
		case '=':
			if (!isalpha(lhs.name[0])) {
				std::invalid_argument("Left hand side must be alphabetical!");
			}

			lhs.val = rhs.val;
			vars.addToDict(lhs);
			numStack.push(rhs);
			break; 

		default: 
			cout << "Not an operator" << endl;
			break;
	}

}

void evaluate(string s) {
	string var;
	int first = 0;
	int dplace = 0;

	numStack.clear();
	opStack.clear();
	opStack.push('$');
	
	while(first < s.length()) {
		operand temp;

		// if s[first] is a digit 
		if (isdigit(s[first])) {
			Fraction num = 0;

			// Convert digit sequence to Fraction 
			while (s[first] != ' ' && s[first]) {
				num = num * 10 + s[first++] - '0';
			}

			// Store Fraction object in structure 
			// and push onto numStack 
			temp.val = num;
			numStack.push(temp);

			// Advance first to first character past digit sequence 
			first++;
		}

		// is s[first] is a letter 
		else if (isalpha(s[first])) {
			// Extract name into string
			string var = "";
			while (s[first] != ' ' && s[first]) {
				var += s[first];
			}

			// Store name in structure 
			temp.name = var;

			// Push onto numstack 
			numStack.push(temp);

			// Advance first to first character past name
			first++;
		}

		// if s[first] is (
		else if (s[first] == '(') {
			// Push ( onto opStack
			opStack.push(s[first]);
		
			// Increment first
			first++;
		}

		// if s[first] is )
		else if (s[first] == ')') {
			// While top of opstack is not ( 
			while (opStack.peek() != '(') {
				// Perform top operation 
				doOp();
			}

			// Pop ( from top of opStack 
			opStack.pop();

			// Increment first 
			first++;
		}

		// else if s[first] is an operator 
		else if (s[first] == '+' || s[first] == '-' 
		|| s[first] == '*' || s[first] == '/' || s[first] == '=') 
		{

			// while top of opStack has precedence over s[first]
			while (hasPrecedence(opStack.peek(), s[first])) {
				// Perform top operation 
				doOp();
			}

			// Push s[first] onto opStack 
			opStack.push(s[first]);

			// increment first 
			first++;
		}

		else {
			// Increment first 
			first++;
		}
	}

	// While top of opStack is not $ 
	while (opStack.peek() != '$') {
		// Perform top operation 
		doOp();
	}

	// output top of numStack 
	Fraction answer = numStack.peek().val;
	cout << answer << endl;
}

void debug (string s) {
	cout << "Debug left as an exercise to the reader." << endl;
}

int main(int argc, char *argv[]) {
	// Arguments: 
	// ./project2 
	// -t

	if (argv[1] == "-t") {
		// Do all the debugging stuff here 

	}

	string expr;

	cout << "Calc: ";
	getline(cin, expr);
	evaluate(expr);

	return 0;
}

