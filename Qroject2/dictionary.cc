// 
// dictionary.cc
//
// Contains actual functions for dictionary class, including 
// basic searching and adding/updating  
// 
// written 21 October 2023 by Bisshoy Anwar 
//
// modification history
//   23 October 2023 - Bisshoy Anwar  
//     Rewrote dictionary to be implemented differently, 
//	   using three parallel arrays instead of being an 
//	   array of operands 
//

#include "dictionary.h"

// 
// clear()
// 		it just sets all entries to "UNUSED" and resets count
// 
// Parameters 
//  	None   
// 
void Dictionary::clear() {
	for (int32_t i = 0; i < TABLE_SIZE; i++) {
		status[i] = UNUSED;
	}

	count = 0;
}

// 
// add(const string&, const Fraction)
// 		will either add a new entry to the array, 
//		or update an existing entry if the key is
//		already in use 
// 
// Parameters 
// 		key - a const string passed by reference 
// 		val - a const Fraction 
// 
void Dictionary::add(const string& key, const Fraction val) {
	int32_t i = 0; 

	while (status[i] != UNUSED) {
				
		// In case of repeat, it updates 
		if (status[i] == IN_USE && keys[i] == key) {
			values[i] = val;
			return;
		}

		i++;
	}

	if (count == TABLE_SIZE) {
		throw std::overflow_error("Dictionary full.");
	}

	keys[i] = key;
	values[i] = val;
	status[i] = IN_USE;
	count++;

}

// 
// add(const string&)
// 		will return the value of a key, or throw 
//		an exception if the key is not in use  
// 
// Parameters 
// 		key - a const string passed by reference 
// 
// Returns 
// 		The value associated with the search key 
// 
Fraction Dictionary::search(const string& key) {
	int32_t i = 0;

	while (status[i] != UNUSED) {
		if (keys[i] == key) {
			return values[i];
		}

		i++;
	}

	throw std::domain_error("Key not found.");
}

