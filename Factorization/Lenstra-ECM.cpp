#include "Lenstra-ECM.h"
#include <time.h>
#include <cmath>
#include <cstdlib>

const unsigned int bound = 1000;

void assign_result(unsigned long long* result, unsigned long long a, unsigned long long b, unsigned long long c) {
	*result = a;
	*(result + 1) = b;
	*(result + 2) = c;
}

unsigned long long extended_GCD(unsigned long long* gcd, unsigned long long a, unsigned long long b) {
	if (a == 0) {
		assign_result(gcd, b, 0, 1);
	}
	else {
		extended_GCD(gcd, b % a, a);
		unsigned long long g = *gcd;
		unsigned long long y = *(gcd + 1);
		unsigned long long x = *(gcd + 2);
		assign_result(gcd, g, x - floor(b / a) * y, y);
	}
	return;
}

void get_inverse(unsigned long long* inverse, unsigned long long m, unsigned long long n) {
	unsigned long long* gcd = new unsigned long long[3];
	extended_GCD(gcd, m, n);
	unsigned long long g = *gcd;
	unsigned long long x = *(gcd + 1);
	unsigned long long y = *(gcd + 2);
	if (g != 1) { // gcd(m, n)
		*inverse = 0;
		*(inverse + 1) = g;
	}
	else { // the inverse of m (mod n) when gcd(m, n) == 1
		*inverse = 1;
		*(inverse + 1) = x % n;
	}
	return;
}

// *result == INFINITY -- O
// *result == 0 -- factors
// *result == 1 -- points
void curve_calculation(unsigned long long* result, unsigned long long b, unsigned long long c, unsigned long long n, unsigned long long x1, unsigned long long y1, unsigned long long x2, unsigned long long y2) {
	if (x1 == INFINITY) {
		assign_result(result, INFINITY, x2, y2);
		return;
	}
	if (x2 == INFINITY) {
		assign_result(result, INFINITY, x1, y1);
		return;
	}

	unsigned long long u, v; // Montgomery
	if (x1 == x2 && y1 == y2) { // doubling
		u = 3 * pow(x1, 2) + b;
		v = 2 * y1;
	}
	else { // addition
		u = y1 - y2;
		v = x1 - x2;
	}
	v = (v + n) % n; // ensure v to be non-negative
	if (v == 0) {
		assign_result(result, INFINITY, INFINITY, INFINITY);
		return;
	}

	unsigned long long* inverse = new unsigned long long[2];
	get_inverse(inverse,v,n);
	if (*inverse == 0) {
		unsigned long long factor1 = *(inverse + 1);
		unsigned long long factor2 = n / factor1;
		assign_result(result, 0, factor1, factor2);
		return;
	}

	unsigned long long m = (*(inverse + 1) * u) % n;
	unsigned long long x3 = (-x1 - x2 + (unsigned long long)pow(m, 2)) % n;
	unsigned long long y3 = (-y1 + m * (x1 - x3)) % n;
	assign_result(result, 1, x3, y3);
	return;
}

void lenstra(unsigned long long n, unsigned long long* result) {
	srand(time(NULL));
	while (true) {
		unsigned long long p1 = (n-1) * rand() + 1;
		unsigned long long p2 = (n-1) * rand() + 1;
		unsigned long long b = (n-1) * rand() + 1;
		unsigned long long c = ((unsigned long long)(pow(p2, 2) - pow(p1, 3) - b * p1) + n ) % n;

		unsigned long long q1, q2;
		q1 = p1;
		q2 = p2;
		unsigned int i = 0;
		while (i < bound) {
			curve_calculation(result, b, c, n, p1, p2, q1, q2);
			if (*result == 0) {
				assign_result(result, 0, q1, q2);
				return;
			}
			else if (*result == INFINITY) {
				break;
			}
		}
	}
}

unsigned long long ecm(unsigned long long n) {
	unsigned long long* lenstra_result = new unsigned long long[3];
	lenstra(n, lenstra_result);
	
	unsigned long long a = *(lenstra_result+1);
	unsigned long long b = *(lenstra_result+2);
	
	if (a != 2 && a % 2 == 0) {
		return 2;
	}
	return a;
}