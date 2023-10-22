#include <cstdint>
#include <iostream>
#include <stdexcept>
#include "fraction.h"

using namespace std;

#ifndef _DICTIONARY_H
#define _DICTIONARY_H

struct operand{
	string name;
	Fraction val;
};

class Dictionary {
	private: 
		operand dict[100];
		int count = 0;
	public:
		Dictionary() {
			// Set all names to empty string 
			// Set all values to -1 
			for (int i = 0; i < 100; i++) {
				dict[i].name = "";
				dict[i].val = -1;
			}
		}

		bool alreadyHere(string key) {
			for (int i = 0; i < 100; i++) {
				if (dict[i].name == key) {
					return true;
				}
			}

			return false;
		}

		int search(string key) {
			for (int i = 0; i < 100; i++) {
				if (dict[i].name == key) {
					return i;
				}
			}

			return -1;
		} 

		void addToDict(operand op) {
			// In case dictionary is full 
			if (count == 100) {
				throw std::domain_error("Dictionary full.");
			}

			// If variable name is already in use 
			if (alreadyHere(op.name)) {
				dict[(search(op.name))].val = op.val;
				return; 
			}

			dict[count] = op;
			count++;
		} 
};

#endif
