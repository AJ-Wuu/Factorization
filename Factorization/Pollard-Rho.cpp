#include "Pollard-Rho.h"
#include "Modular-Power.h"
#include <iostream>
#include <numeric>

unsigned long long pollard_rho(unsigned long long n) {
	srand(time(NULL));

	if (n == 1) {
		return n;
	}

	if (n % 2 == 0) {
		return 2;
	}

	unsigned long long x = (rand() % (n - 2)) + 2;
	unsigned long long y = x;
	unsigned long long c = (rand() % (n - 1)) + 1;
	unsigned long long d = 1;

	while (d == 1) {
		x = (modular_pow(x, 2, n) + c + n) % n;
		y = (modular_pow(y, 2, n) + c + n) % n;
		y = (modular_pow(y, 2, n) + c + n) % n;

		long long temp = x - y;
		d = std::gcd(abs(temp), n);
		if (d == n) {
			return pollard_rho(n);
		}
	}

	return d;
}
