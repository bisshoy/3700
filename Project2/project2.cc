#include "stack.h"
#include "fraction.h"
#include "dictionary.h"
#include <iostream>

using namespace std;

Stack<operand> numStack;
Stack<char>  opStack;
Dictionary vars; 

bool hasPrecedence(char a, char b) {
	// a = s.peek();      A IS NEXT INPUT
	// b = opStack.peek() B IS TOP OF OPSTACK

	if ((b == '*' || b == '/') || 
	(((b == '+' || b == '-') && (a == '+' || a == '-' || a == '=')))) {
		return true;
	}

	else if ((b == '=' || b == '(' || b == '$') 
	|| ((b == '+' || b == '-') && (a == '*' || a == '/'))) {
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

		default: 
			cout << "Not an operator" << endl;
			break;
	}

}

Fraction evaluate(string s) {
	string var;
	int first = 0;
	int dplace = 0;

	numStack.clear();
	opStack.clear();
	opStack.push('$');
	while(first < s.length()) {
		operand temp;

		if (isdigit(s[first])) {
			// operand digit;
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

		else if (isalpha(s[first])) {
			// Extract name into string
			// operand varname;
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

		else if (s[first] == '(') {
			

		}

		else if (s[first] == ')') {

		}

		else if (s[first] == '+' || s[first] == '-' 
		|| s[first] == '*' || s[first] == '/') {
			
		}

		else {
			first++;
		}
	}

	while (opStack.peek() != '$') {

	}

	return numStack.pop().val;
}

int main() {

	string expr;

	while (expr != "#") {
		cout << "Calc: ";
		evaluate((cin, expr));
		cout << endl;
	}

	return 0;
}

