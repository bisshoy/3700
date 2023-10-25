// 
// calcFunctions.cc
//
// Contains actual functions for calculator functions,  
// including a parser to put parts of the input string into 
// the appropriate stack, a switch-case operation do'er,
// a precedence checker for PEMDAS, and a debugger mode  
// 
// written 21 October 2023 by Bisshoy Anwar 
//

#include <iostream>
#include "calcFunctions.h"
#include "dictionary.h"
#include "stack.h"

Stack<operand> numStack;
Stack<char> opStack;

// 
// bool hasPrecedence(char, char)
// 		Will return true if opStack has precedence 
// 		over the next operator in user input  
// 
// Parameters 
// 		top - a char meant to be opStack.peek() 
// 		input - a char meant to be s.peek()
// 
// Returns 
// 		Boolean value: if opStack has precedence 
// 
bool hasPrecedence(char top, char input) {
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

// 
// doOp()
//  	Will do appropriate operation based on what 
// 		is in opStack   
// 
// Parameters 
// 		None 
// 
void doOp() {
	static Dictionary vars; 

	operand lhs, rhs, ans;
	char op; 

	rhs = numStack.pop();
	lhs = numStack.pop();
	op = opStack.pop();
	
	// 
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
			lhs.val = rhs.val;
			vars.add(lhs.name,lhs.val);
			rhs.name = "";
			numStack.push(rhs);
			break; 

		default: 
			std::cout << "Not an operator!" << endl;
			break;
	}

}

// 
// void evaluate(string)
// 		Will parse through user input, placing numbers
// 		and variables in the numStack and operators in 
// 		the opStack. Will call doOp() when appropriate 
// 
// Parameters 
// 		s - The user's input string 
//  
void evaluate(string s) {
	string var;
	int32_t first = 0;
	operand temp;

	numStack.clear();
	opStack.clear();
	opStack.push('$');

	while(first < s.length()) {

		// if s[first] is a digit 
		if (isdigit(s[first])) {
			Fraction num = 0;

			// Convert digit sequence to Fraction 
			while (s[first] != ' ' && isdigit(s[first]) && s[first]) {
				num = num * 10 + s[first++] - '0';
			}

			// Store Fraction object in structure 
			// and push onto numStack 
			temp.val = num;
			temp.name = "";

			numStack.push(temp);

			// Advance first to first character past digit sequence 
			// already done above 
		}

		// is s[first] is a letter 
		else if (isalpha(s[first])) {
			// Extract name into string
			string var = "";

			while (s[first] != ' ' && isalpha(s[first]) && s[first]) {
				var += s[first++];
			}

			// Store name in structure 
			temp.name = var;

			// Push onto numstack 
			numStack.push(temp);

			// Advance first to first character past name
			// already done above 
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
	if (!numStack.peek().name.empty()) {
		temp.name = "";
		temp.val = Fraction();
		numStack.push(temp);
		opStack.push('+');
		doOp();
	}
	
	Fraction answer = numStack.peek().val;
	std::cout << answer << endl;
}

// 
// debug(string)
// 		Will print the input token-by-token on 
// 		newlines, putting numStack objects in 
// 		brackets 
// 
// Parameters 
// 		s - The user's input string 
// 
void debug (string s) {
	// Have debugStack take operands 
	string var;
	int32_t first = 0;
	Stack<operand> debugStack;
	Stack<operand> revDebugStack;

	// Clear debugStack
	debugStack.clear();

	while(first < s.length()) {
		operand temp;

		// if s[first] is a digit 
		if (isdigit(s[first])) {
			Fraction num = 0;

			// Convert digit sequence to Fraction 
			while (s[first] != ' ' && isdigit(s[first]) && s[first]) {
				num = num * 10 + s[first++] - '0';
			}

			// Store Fraction object in structure 
			// and push onto debugStack 
			temp.val = num;
			debugStack.push(temp);

			// Advance first to first character past digit sequence 
			// already done above in digit iteration 
		}

		// is s[first] is a letter 
		else if (isalpha(s[first])) {
			// Extract name into string
			string var = "";
 
			while (s[first] != ' ' && isalpha(s[first]) && s[first]) {
				var += s[first++];
			}

			// Store name in structure 
			temp.name = var;

			// Push onto numstack 
			debugStack.push(temp);

			// Advance first to first character past name
			// first++;
		}

		// if s[first] is (
		else if (s[first] == '(') {
			temp.name = "(";
			// Push ( onto opStack
			debugStack.push(temp);
		
			// Increment first
			first++;
		}

		// if s[first] is )
		else if (s[first] == ')') {
			temp.name = ")";

			// Pop ( from top of opStack 
			debugStack.push(temp);

			// Increment first 
			first++;
		}

		// else if s[first] is an operator 
		else if (s[first] == '+' || s[first] == '-' 
		|| s[first] == '*' || s[first] == '/' || s[first] == '=') 
		{

			temp.name = s[first];

			// Push s[first] onto opStack 
			debugStack.push(temp);

			// increment first 
			first++;
		}

		else {
			// Increment first 
			first++;
		}
	}

	// Reverse debugStack into the revDebugStack 
	while (!debugStack.isEmpty()) {
		revDebugStack.push(debugStack.pop());
	}

	// Print out tokens appropriately 
	while (!revDebugStack.isEmpty()) {
		operand temp2 = revDebugStack.pop();

		if (isalpha(temp2.name[0])) {
			std::cout << "[" << temp2.name << "]" << endl;
		}

		else if (temp2.name != "") {
			std::cout << temp2.name << endl;
		}

		else {
			std::cout << "[" << temp2.val << "]" << endl;
		}
	}
}

