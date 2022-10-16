#include "Modular-Power.h"

long long modular_pow(long long base, int exponent, long long modulus) {
	long long result = 1;

	while (exponent > 0) {
		if (exponent & 1) { // if y is odd, multiply base with result
			result = (result * base) % modulus;
		}
		exponent = exponent >> 1;
		base = (base * base) % modulus;
	}

	return result;
}