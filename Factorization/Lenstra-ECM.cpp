#include "Lenstra-ECM.h"
#include "BigInteger/BigIntegerLibrary.hh"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <string>

const BigInteger INF = stringToBigInteger("1000000000000000000000000000000");
const int bound = 1000;

BigInteger modulo(BigInteger number, BigInteger base) {
	if (number >= 0) {
		return number % base;
	}
	else {
		return (number % base + base) % base;
	}
}

void assign_result(BigInteger* result, BigInteger a, BigInteger b, BigInteger c) {
	*result = a;
	*(result + 1) = b;
	*(result + 2) = c;
}

void extended_GCD(BigInteger* gcd, BigInteger a, BigInteger b) {
	if (a == 0) {
		assign_result(gcd, b, 0, 1);
	}
	else {
		extended_GCD(gcd, modulo(b, a), a);
		BigInteger g = *gcd;
		BigInteger y = *(gcd + 1);
		BigInteger x = *(gcd + 2);
		assign_result(gcd, g, x - (b / a) * y, y);
	}
	return;
}

void get_inverse(BigInteger* inverse, BigInteger m, BigInteger n) {
	BigInteger* gcd = new BigInteger[3];
	extended_GCD(gcd, m, n);
	BigInteger g = *gcd;
	BigInteger x = *(gcd + 1);
	BigInteger y = *(gcd + 2);
	if (g != 1) { // gcd(m, n)
		*inverse = 0;
		*(inverse + 1) = g;
	}
	else { // the inverse of m (mod n) when gcd(m, n) == 1
		*inverse = 1;
		*(inverse + 1) = modulo(x, n);
	}
	return;
}

// *result == INF -- O
// *result == 0 -- factors
// *result == 1 -- points
void curve_calculation(BigInteger* result, BigInteger b, BigInteger c, BigInteger n, BigInteger x1, BigInteger y1, BigInteger x2, BigInteger y2) {
	if (x1 == INF) {
		assign_result(result, INF, x2, y2);
		return;
	}
	if (x2 == INF) {
		assign_result(result, INF, x1, y1);
		return;
	}

	// Montgomery
	BigInteger u, v;
	if (x1 == x2 && y1 == y2) { // doubling
		u = BigInteger(3) * x1 * x1 + b;
		v = BigInteger(2) * y1;
	}
	else { // addition
		u = y1 - y2;
		v = x1 - x2;
	}
	v = modulo(v, n); // ensure v to be non-negative
	if (v == 0) {
		assign_result(result, INF, INF, INF);
		return;
	}

	BigInteger* inverse = new BigInteger[2];
	get_inverse(inverse,v,n);
	if (*inverse == 0) {
		BigInteger factor1 = *(inverse + 1);
		BigInteger factor2 = n / factor1;
		assign_result(result, 0, factor1, factor2);
		return;
	}

	BigInteger m = modulo((modulo(*(inverse + 1), n) * modulo(u, n)), n);
	BigInteger x3 = modulo((m * m - x1 - x2), n);
	BigInteger y3 = modulo((m * (x1 - x3) - y1), n);
	assign_result(result, 1, x3, y3);
	return;
}

void lenstra(BigInteger n, BigInteger* result) {
	srand(time(NULL));
	while (true) {
		BigInteger p1 = (n-1) * rand() + 1; // within (1,n)
		BigInteger p2 = (n-1) * rand() + 1;
		BigInteger b = (n-1) * rand() + 1;
		BigInteger c = modulo(((BigInteger)(p2 * p2 - p1 * p1 * p1 - b * p1) + n ), n);

		BigInteger q1, q2;
		q1 = p1;
		q2 = p2;
		int times = 0;
		while (times < bound) {
			curve_calculation(result, b, c, n, p1, p2, q1, q2);
			q1 = *(result + 1);
			q2 = *(result + 2);
			if (*result == 0) {
				assign_result(result, 0, q1, q2);
				return;
			}
			else if (*result == INF) {
				break;
			}
			times++;
		}
	}
}

long long ecm(long long n) {
	BigInteger* lenstra_result = new BigInteger[3];
	std::string n_string = std::to_string(n);
	BigInteger n_biginteger = stringToBigInteger(n_string);
	lenstra(n_biginteger, lenstra_result);
	BigInteger result_biginteger = *(lenstra_result+1);
	std::string result_string = bigIntegerToString(result_biginteger);
	long long result = std::stoll(result_string);
	return result;
}