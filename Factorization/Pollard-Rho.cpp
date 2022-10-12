#include "Pollard-Rho.h"
#include "Modular-Power.h"
#include <iostream>
#include <numeric>

long long pollard_rho(long long n) {
	srand(time(NULL));

	if (n == 1) {
		return n;
	}

	if (n % 2 == 0) {
		return 2;
	}

	long long x = (rand() % (n - 2)) + 2;
	long long y = x;
	long long c = (rand() % (n - 1)) + 1;
	long long d = 1;

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
