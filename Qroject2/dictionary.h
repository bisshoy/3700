// 
// dictionary.h 
//
// dictionary class header, with private variables consisting 
// of three parallel arrays for keys, values, and use status 
//
// written 21 October 2023 by Bisshoy Anwar 
// 
// modification history
//   23 October 2023 - Bisshoy Anwar 
// 		Rewrote dictionary to use parallel arrays  
//

#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "fraction.h"

using namespace std;

#ifndef _DICTIONARY_H
#define _DICTIONARY_H

// Dictionary statuses 
enum DictionaryStatus {
	UNUSED, IN_USE
};

const int32_t TABLE_SIZE = 100;

class Dictionary {
	private: 
		string           keys[TABLE_SIZE];
		Fraction         values[TABLE_SIZE];
		DictionaryStatus status[TABLE_SIZE];

		int32_t count = 0;

	public: 
		// Constructor/Destructor 
		Dictionary() { clear(); }
		~Dictionary() = default;

		// Basic container functions 
		bool isEmpty() { return count == 0; }
		int32_t size() { return count; }
		void clear();
		void add(const string& key, const Fraction val);
		Fraction search(const string& key);
};

#endif
