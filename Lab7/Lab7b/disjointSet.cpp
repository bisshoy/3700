#include <iostream>
#include <cstdint>
#include "disjointSet.h"

using namespace std;

DisjointSet::DisjointSet(int32_t n) {
	// Initialize arrays
	elem = new int32_t[n];
	rank = new int32_t[n];

	numElements = n;

	for (int i = 0; i < n; i++) {
		elem[i] = i;
		rank[i] = i;
	}
}

DisjointSet::~DisjointSet() {
	delete[] elem; 
	delete[] rank; 
}

int32_t DisjointSet::find(int32_t a) {
	if (elem[a] != a) {
		elem[a] = find(elem[a]);
	}

	return elem[a];
}

void DisjointSet::join(int32_t a, int32_t b) {
	// Algorithm 2 
	a = find(a);
	b = find(b);

	if (a != b) {
		if (rank[a] < rank[b]) {
			elem[a] = b;
		}

		else {
			if (rank[a] == rank[b]) {
				rank[a] += 1;
			}

			elem[b] = a;
		}
	}
}
