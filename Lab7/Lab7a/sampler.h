#ifndef _SAMPLER_H
#define _SAMPLER_H

#include <stdexcept>
#include <cstdint>
#include <random>

class Sampler {
	private:
		uint32_t numElements, *elements;
		std::random_device *rd;
		std::mt19937 *mt;

	public: 
		Sampler(uint32_t n);
		~Sampler();

		uint32_t getSample();
};

#endif
