#include <iostream>
#include <cstdint>

using namespace std;

#ifndef _DISJOINTSET_H
#define _DISJOINTSET_H

class DisjointSet {
	private: 
		int32_t numElements;
		int32_t *elem;
		int32_t *rank;

	public: 
		DisjointSet(int32_t n);
		~DisjointSet(); 

		int32_t find(int32_t a);
		void join(int32_t a, int32_t b);
};

#endif