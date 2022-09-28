#include "Modular-Power.h"

unsigned long long modular_pow(unsigned long long base, int exponent, unsigned long long modulus) {
	unsigned long long result = 1;

	while (exponent > 0) {
		if (exponent & 1) { // if y is odd, multiply base with result
			result = (result * base) % modulus;
		}
		exponent = exponent >> 1;
		base = (base * base) % modulus;
	}

	return result;
}