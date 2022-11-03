#include "AKS.h"
#include "modulo.h"
#include <numeric>

using namespace std;

inline bool step1(const uint64_t& n) {
	// instead of looping through both a and b, we only go with b
	// so that n = a^b -> a = n^(1/b) -> check if a is in N
	double a = 1;
	const double tiny = 1E-10; // minimal difference that could happen with double
	for (double b = 2; b <= log2(n); ++b) {
		a = pow(n, 1/b);
		if (abs(floor(a) - a) < tiny) {
			return false;
		}
	}
	return true;
}

inline uint64_t step2(const uint64_t& n) {
	const double max_k = floor(pow(log2(n), 2));
	const double max_r = max(3.0, ceil(pow(log2(n), 5)));
	bool next_r = true;
	uint64_t r = 0;

	for (r = 2; next_r && r < max_r; ++r) {
		next_r = false;
		for (uint64_t k = 1; (!next_r) && k < max_k; ++k) {
			uint64_t mod = pow_mod(n, k, r);
			next_r = mod == 1 || mod == 0;
		}
	}
	--r;

	return r;
}

inline bool step3(const uint64_t& n, const uint64_t& r) {
	uint64_t gcd = 0;
	for (uint64_t a = 2; a <= r; ++a) {
		gcd = std::gcd(a, n); // Project Properties dialog: C/C++ -> Language -> C++ Language Standard -> C++17
		if (1 < gcd && gcd < n) {
			return false;
		}
	}
	return true;
}

inline bool step5(const uint64_t& n) {
	uint64_t curr = 1;
	for (int i = 1; i < n / 2 + 1; ++i) {
		curr = mul_mod(curr, n + 1 - i, n) / i;
		if (curr % n != 0) {
			return false;
		}
	}
	return true;
}

bool is_prime(uint64_t n) {
	// edge cases
	if (n == 0 || n == 1) {
		return false;
	}

	// step 1: if (n = a^b for a in N and b > 1), output COMPOSITE
	if (!step1(n)) {
		return false;
	}

	// step 2: find the smallest r such that o_r(n) > log^2(n)
	uint64_t r = step2(n);

	// step 3: if 1 < (a,n) < n for some a <= r, output COMPOSITE
	if (!step3(n, r)) {
		return false;
	}

	// step 4: if n <= r, output PRIME
	if (n <= r) {
		return true;
	}

	// step 5: for a = 1 to floor(sqrt(phi(r)) * logn), do
	//             if ((X+a)^n != X^n + a (mod X^r - 1, n)), output COMPOSITE
	if (!step5(n)) {
		return false;
	}

	// step 6: output PRIME
	return true;
}
