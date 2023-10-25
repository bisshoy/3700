// 
// calcFucntions.h 
//
// header file for calculator functions, including 
// a parser to put parts of the input string into 
// the appropriate stack, a switch-case operation do'er,
// a precedence checker for PEMDAS, and a debugger mode 
//
// written 21 October 2023 by Bisshoy Anwar 
// 
// modification history
//   24 October 2023 - Bisshoy Anwar 
// 		Rewrote dictionary to use parallel arrays  
//

#include <iostream>
#include <stdexcept>
#include <cstdint>
#include "fraction.h"
#include "stack.h"

using namespace std;

#ifndef _CALCFUNCTIONS_H
#define _CALCFUNCTIONS_H

// struct that goes into numStack 
struct operand{
	string name;
	Fraction val;
};

bool hasPrecedence(char, char);
void doOp();
void evaluate(string);
void debug(string);

#endif
