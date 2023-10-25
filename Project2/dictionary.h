#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "fraction.h"

using namespace std;

#ifndef _DICTIONARY_H
#define _DICTIONARY_H

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
		Dictionary() { clear(); }
		~Dictionary() = default;

		bool isEmpty() { return count == 0; }
		int32_t size() { return count; }

		void clear() {
			for (int32_t i = 0; i < TABLE_SIZE; i++) {
				status[i] = UNUSED;
			}

			count = 0;
		}

		void add(const string& key, const Fraction val) {
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

		Fraction search(const string& key) {
			int32_t i = 0;

			while (status[i] != UNUSED) {
				if (keys[i] == key) {
					return values[i];
				}

				i++;
			}

			throw std::domain_error("Key not found. Search 72.");
		}
};

#endif