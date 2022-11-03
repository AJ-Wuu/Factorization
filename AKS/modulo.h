#ifndef modulo
#define modulo

#include <cmath>
#include <cstdint>

inline uint64_t pow_mod(uint64_t base, uint64_t exponent, uint64_t mod) {
	if (mod == 1) {
		return 0;
	}

	uint64_t remainder;
	uint64_t n = base;
	for (remainder = 1; exponent; exponent >>= 1) {
		if (exponent & 1)
			remainder = ((remainder % mod) * (n % mod)) % mod;
		n = ((n % mod) * (n % mod)) % mod;
	}

	return remainder;
}

inline uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t m) {
	long double x;
	uint64_t c;
	int64_t r;
	if (a >= m) {
		a %= m;
	}
	if (b >= m) {
		b %= m;
	}

	x = a;
	c = x * b / m;
	r = (int64_t)(a * b - c * m) % (int64_t)m;

	return r < 0 ? r + m : r;
}

#endif