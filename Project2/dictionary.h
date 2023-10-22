#include <cstdint>
#include <iostream>
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
			for (int i = 0; i < 100; i++) {
				dict[i].name = "";
				dict[i].val = 0;
			}
		}

		bool alreadyHere(string key) {
			for (int i = 0; i < 100; i++) {
				if (dict[i].name == key) {
					return true;
				}

				else {
					return false;
				}
			}
		}

		Fraction search(string key) {
			for (int i = 0; i < 100; i++) {
				if (dict[i].name == key) {
					return dict[i].val;
				}

				else {
					return -1; 
				}
			}
		} 

		void addToDict(operand op) {
			if (alreadyHere(op.name)) {
				cout << "Error: Variable name already used" << endl;
				return; 
			}

			dict[count] = op;
			count++;
		} 
};

#endif
