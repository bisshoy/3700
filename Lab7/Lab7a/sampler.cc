#include <stdexcept>
#include "sampler.h"

Sampler::Sampler(uint32_t n) {
	// initialize array 
	elements = new uint32_t[n];

	numElements = n;

	// fill array 
	for (int i = 0; i < n; i++) {
		elements[i] = i;
	}

	n = numElements;

	rd = new std::random_device;
	mt = new std::mt19937((*rd)());
}

Sampler::~Sampler() {
	delete[] elements;
	delete rd;
	delete mt;
}

uint32_t Sampler::getSample() {
	uint32_t i, e;
	std::uniform_int_distribution<> 
		dis(0, numElements-1);
	
	i = dis(*mt);

	// Check for elements 
	if (numElements == 0) {
		throw std::underflow_error("Sampler out of elements!");
	}

	// remember the selected item 
	e = elements[i];

	// decrement 
	numElements--;

	// move last item into selected position 
	elements[i] = elements[numElements];

	return e;

}
